/*
 * processes.c:  Process handles
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#include <config.h>
#include <glib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "./wapi.h"
#include "./wapi-private.h"
#include "./handles-private.h"
#include "./misc-private.h"
#include "./mono-mutex.h"
#include "./process-private.h"
#include "./threads.h"
#include "strenc.h"
#include "./timefuncs-private.h"

/* The process' environment strings */
extern char **environ;

#undef __DEBUG__

static guint32 process_wait (gpointer handle, guint32 timeout);

struct _WapiHandleOps _wapi_process_ops = {
	NULL,				/* close_shared */
	NULL,				/* signal */
	NULL,				/* own */
	NULL,				/* is_owned */
	process_wait			/* special_wait */
};

static mono_once_t process_current_once=MONO_ONCE_INIT;
static gpointer current_process=NULL;

static mono_once_t process_ops_once=MONO_ONCE_INIT;

static void process_ops_init (void)
{
	_wapi_handle_register_capabilities (WAPI_HANDLE_PROCESS,
					    WAPI_HANDLE_CAP_WAIT |
					    WAPI_HANDLE_CAP_SPECIAL_WAIT);
}

static gboolean process_set_termination_details (gpointer handle, int status)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	int thr_ret;
	
	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
				  (gpointer *)&process_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up process handle %p",
			   __func__, handle);
		return(FALSE);
	}
	
	thr_ret = _wapi_handle_lock_shared_handles ();
	g_assert (thr_ret == 0);

	if (WIFSIGNALED(status)) {
		process_handle->exitstatus = 128 + WTERMSIG(status);
	} else {
		process_handle->exitstatus = WEXITSTATUS(status);
	}
	_wapi_shared_handle_set_signal_state (handle, TRUE);

	_wapi_handle_unlock_shared_handles ();

	return (ok);
}

/* See if any child processes have terminated and wait() for them,
 * updating process handle info.  This function is called from the
 * collection thread every few seconds.
 */
static gboolean waitfor_pid (gpointer test, gpointer user_data G_GNUC_UNUSED)
{
	struct _WapiHandle_process *process;
	gboolean ok;
	int status;
	pid_t ret;
	
	if (_wapi_handle_issignalled (test)) {
		/* We've already done this one */
		return (FALSE);
	}
	
	ok = _wapi_lookup_handle (test, WAPI_HANDLE_PROCESS,
				  (gpointer *)&process);
	if (ok == FALSE) {
		/* The handle must have been too old and was reaped */
		return (FALSE);
	}
	
	do {
		ret = waitpid (process->id, &status, WNOHANG);
	} while (errno == EINTR);
	
	if (ret <= 0) {
		/* Process not ready for wait */
#ifdef __DEBUG__
		g_message ("%s: Process %d not ready for waiting for: %s",
			   __func__, process->id, g_strerror (errno));
#endif

		return (FALSE);
	}
	
#ifdef __DEBUG__
	g_message ("%s: Process %d finished", __func__, ret);
#endif

	process_set_termination_details (test, status);
	
	/* return FALSE to keep searching */
	return (FALSE);
}

void _wapi_process_reap (void)
{
#ifdef __DEBUG__
	g_message ("%s: Reaping child processes", __func__);
#endif

	_wapi_search_handle (WAPI_HANDLE_PROCESS, waitfor_pid, NULL, NULL);
}

/* Limitations: This can only wait for processes that are our own
 * children.  Fixing this means resurrecting a daemon helper to manage
 * processes.
 */
static guint32 process_wait (gpointer handle, guint32 timeout)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	pid_t pid, ret;
	int status;
	
#ifdef __DEBUG__
	g_message ("%s: Waiting for process %p", __func__, handle);
#endif

	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
				  (gpointer *)&process_handle);
	if (ok == FALSE) {
		g_warning ("%s: error looking up process handle %p", __func__,
			   handle);
		return(WAIT_FAILED);
	}
	
	pid = process_handle->id;
	
#ifdef __DEBUG__
	g_message ("%s: PID is %d", __func__, pid);
#endif

	if (timeout == INFINITE) {
		while ((ret = waitpid (pid, &status, 0)) != pid) {
			if (ret == (pid_t)-1 && errno != EINTR) {
				return(WAIT_FAILED);
			}
		}
	} else if (timeout == 0) {
		/* Just poll */
		ret = waitpid (pid, &status, WNOHANG);
		if (ret != pid) {
			return (WAIT_TIMEOUT);
		}
	} else {
		/* Poll in a loop */
		do {
			ret = waitpid (pid, &status, WNOHANG);
			if (ret == pid) {
				break;
			} else if (ret == (pid_t)-1 && errno != EINTR) {
				return(WAIT_FAILED);
			}

			_wapi_handle_spin (100);
			timeout -= 100;
		} while (timeout > 0);

		if (timeout <= 0) {
			return(WAIT_TIMEOUT);
		}
	}

	/* Process must have exited */
#ifdef __DEBUG__
	g_message ("%s: Wait done", __func__);
#endif

	ok = process_set_termination_details (handle, status);
	if (ok == FALSE) {
		SetLastError (ENOMEM);
		return (WAIT_FAILED);
	}

	return(WAIT_OBJECT_0);
}
	
/* Implemented as just a wrapper around CreateProcess () */
gboolean ShellExecuteEx (WapiShellExecuteInfo *sei)
{
	gboolean ret;
	WapiProcessInformation process_info;
	gchar *u8file, *u8params, *u8args;
	
	if (sei == NULL) {
		/* w2k just segfaults here, but we can do better than
		 * that
		 */
		SetLastError (EINVAL);
		return (FALSE);
	}
	
	/* Put both executable and parameters into the second argument
	 * to CreateProcess (), so it searches $PATH.  The conversion
	 * into and back out of utf8.
	 */
	u8file = g_strdup (sei->lpFile);
	if (u8file == NULL) {
		SetLastError (EINVAL);
		return (FALSE);
	}
	
	u8params = g_strdup (sei->lpParameters);
	if (u8params == NULL) {
		SetLastError (EINVAL);
		g_free (u8file);
		return (FALSE);
	}
	
	u8args = g_strdup_printf ("%s %s", u8file, u8params);
	if (u8args == NULL) {
		SetLastError (EINVAL);
		g_free (u8params);
		g_free (u8file);
		return (FALSE);
	}
	
	g_free (u8file);
	g_free (u8params);

	ret = CreateProcess (NULL, u8args, NULL, NULL, TRUE,
			     CREATE_UNICODE_ENVIRONMENT, NULL,
			     sei->lpDirectory, NULL, &process_info);
	g_free (u8args);
	
	if (!ret) {
		return (FALSE);
	}
	
	if (sei->fMask & SEE_MASK_NOCLOSEPROCESS) {
		sei->hProcess = process_info.hProcess;
	} else {
		CloseHandle (process_info.hProcess);
	}
	
	return (ret);
}

gboolean CreateProcess (const gchar *appname, const gchar *cmdline,
			WapiSecurityAttributes *process_attrs G_GNUC_UNUSED,
			WapiSecurityAttributes *thread_attrs G_GNUC_UNUSED,
			gboolean inherit_handles, guint32 create_flags,
			gpointer new_environ, const gchar *cwd,
			WapiStartupInfo *startup,
			WapiProcessInformation *process_info)
{
	gchar *cmd=NULL, *args = NULL, *dir = NULL, *prog = NULL;
	guint32 i;
	gboolean ret = FALSE;
	gpointer handle;
	struct _WapiHandle_process process_handle = {0}, *process_handle_data;
	int in_fd, out_fd, err_fd;
	pid_t pid;
	int thr_ret;
	
	mono_once (&process_ops_once, process_ops_init);
	
	/* appname and cmdline specify the executable and its args:
	 *
	 * If appname is not NULL, it is the name of the executable.
	 * Otherwise the executable is the first token in cmdline.
	 *
	 * Executable searching:
	 *
	 * If appname is not NULL, it can specify the full path and
	 * file name, or else a partial name and the current directory
	 * will be used.  There is no additional searching.
	 *
	 * If appname is NULL, the first whitespace-delimited token in
	 * cmdline is used.  If the name does not contain a full
	 * directory path, the search sequence is:
	 *
	 * 1) The directory containing the current process
	 * 2) The current working directory
	 * 3) The windows system directory  (Ignored)
	 * 4) The windows directory (Ignored)
	 * 5) $PATH
	 *
	 * Just to make things more interesting, tokens can contain
	 * white space if they are surrounded by quotation marks.  I'm
	 * beginning to understand just why windows apps are generally
	 * so crap, with an API like this :-(
	 */
	if (appname != NULL) {
		cmd = g_strdup (appname);
		/* Turn all the slashes round the right way */
		for (i = 0; i < strlen (cmd); i++) {
			if (cmd[i] == '\\') {
				cmd[i] = '/';
			}
		}
	}
	
	if (cmdline != NULL) {
		args = g_strdup (cmdline);
	}

	if (cwd != NULL) {
		dir = g_strdup (cwd);

		/* Turn all the slashes round the right way */
		for (i = 0; i < strlen (dir); i++) {
			if (dir[i] == '\\') {
				dir[i] = '/';
			}
		}
	} else {
		dir = g_get_current_dir ();
	}
	

	/* We can't put off locating the executable any longer :-( */
	if (cmd != NULL) {
		gchar *unquoted;
		if (g_ascii_isalpha (cmd[0]) && (cmd[1] == ':')) {
			/* Strip off the drive letter.  I can't
			 * believe that CP/M holdover is still
			 * visible...
			 */
			g_memmove (cmd, cmd+2, strlen (cmd)-2);
			cmd[strlen (cmd)-2] = '\0';
		}

		unquoted = g_shell_unquote (cmd, NULL);
		if (unquoted[0] == '/') {
			/* Assume full path given */
			prog = g_strdup (unquoted);

			/* Executable existing ? */
			if (access (prog, X_OK) != 0) {
#ifdef __DEBUG__
				g_message ("%s: Couldn't find executable %s",
					   __func__, prog);
#endif
				g_free (prog);
				g_free (unquoted);
				SetLastError (ENOENT);
				goto cleanup;
			}
		} else {
			/* Search for file named by cmd in the current
			 * directory
			 */
			char *curdir = g_get_current_dir ();

			prog = g_strdup_printf ("%s/%s", curdir, unquoted);
			g_free (unquoted);
			g_free (curdir);

			/* And make sure it's executable */
			if (access (prog, X_OK) != 0) {
#ifdef __DEBUG__
				g_message ("%s: Couldn't find executable %s",
					   __func__, prog);
#endif
				g_free (prog);
				SetLastError (ENOENT);
				goto cleanup;
			}
		}
	} else {
		gchar *token = NULL;
		char quote;
		
		/* Dig out the first token from args, taking quotation
		 * marks into account
		 */

		/* First, strip off all leading whitespace */
		args = g_strchug (args);
		
		/* Assume the opening quote will always be the first
		 * character
		 */
		if (args[0] == '\"' || args [0] == '\'') {
			quote = args [0];
			for (i = 1; args[i] != '\0' && args[i] != quote; i++);
			if (g_ascii_isspace (args[i+1])) {
				/* We found the first token */
				token = g_strndup (args+1, i-1);
			} else {
				/* Quotation mark appeared in the
				 * middle of the token.  Just give the
				 * whole first token, quotes and all,
				 * to exec.
				 */
			}
		}
		
		if (token == NULL) {
			/* No quote mark, or malformed */
			for (i = 0; args[i] != '\0'; i++) {
				if (g_ascii_isspace (args[i])) {
					token = g_strndup (args, i);
					break;
				}
			}
		}

		if (token == NULL && args[0] != '\0') {
			/* Must be just one token in the string */
			token = g_strdup (args);
		}
		
		if (token == NULL) {
			/* Give up */
#ifdef __DEBUG__
			g_message ("%s: Couldn't find what to exec", __func__);
#endif

			SetLastError (ENOTDIR);
			goto cleanup;
		}
		
		/* Turn all the slashes round the right way. Only for
		 * the prg. name
		 */
		for (i = 0; i < strlen (token); i++) {
			if (token[i] == '\\') {
				token[i] = '/';
			}
		}

		if (g_ascii_isalpha (token[0]) && (token[1] == ':')) {
			/* Strip off the drive letter.  I can't
			 * believe that CP/M holdover is still
			 * visible...
			 */
			g_memmove (token, token+2, strlen (token)-2);
			token[strlen (token)-2] = '\0';
		}

		if (token[0] == '/') {
			/* Assume full path given */
			prog = g_strdup (token);
			
			/* Executable existing ? */
			if (access (prog, X_OK) != 0) {
				g_free (prog);
#ifdef __DEBUG__
				g_message ("%s: Couldn't find executable %s",
					   __func__, token);
#endif
				g_free (token);
				SetLastError (ENOENT);
				goto cleanup;
			}

		} else {
			char *curdir = g_get_current_dir ();

			/* FIXME: Need to record the directory
			 * containing the current process, and check
			 * that for the new executable as the first
			 * place to look
			 */

			prog = g_strdup_printf ("%s/%s", curdir, token);
			g_free (curdir);

			/* I assume X_OK is the criterion to use,
			 * rather than F_OK
			 */
			if (access (prog, X_OK) != 0) {
				g_free (prog);
				prog = g_find_program_in_path (token);
				if (prog == NULL) {
#ifdef __DEBUG__
					g_message ("%s: Couldn't find executable %s", __func__, token);
#endif

					g_free (token);
					SetLastError (ENOENT);
					goto cleanup;
				}
			}
		}

		g_free (token);
	}

	if (startup != NULL && startup->dwFlags & STARTF_USESTDHANDLES) {
		in_fd = GPOINTER_TO_UINT (startup->hStdInput);
		out_fd = GPOINTER_TO_UINT (startup->hStdOutput);
		err_fd = GPOINTER_TO_UINT (startup->hStdError);
	} else {
		in_fd = GPOINTER_TO_UINT (GetStdHandle (STD_INPUT_HANDLE));
		out_fd = GPOINTER_TO_UINT (GetStdHandle (STD_OUTPUT_HANDLE));
		err_fd = GPOINTER_TO_UINT (GetStdHandle (STD_ERROR_HANDLE));
	}
	
	g_strlcpy (process_handle.proc_name, prog,
		   _WAPI_PROC_NAME_MAX_LEN - 1);

	handle = _wapi_handle_new (WAPI_HANDLE_PROCESS, &process_handle);
	if (handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating process handle", __func__);

		SetLastError (ENOTDIR);
		goto cleanup;
	}
	
	thr_ret = _wapi_handle_lock_shared_handles ();
	g_assert (thr_ret == 0);
	
	pid = fork ();
	if (pid == -1) {
		/* Error */
		SetLastError (ENOMEM);
		_wapi_handle_unref (handle);
		goto cleanup;
	} else if (pid == 0) {
		/* Child */
		
		/* Wait for the parent to finish setting up the
		 * handle.  The semaphore lock is safe because the
		 * sem_undo structures of a semaphore aren't inherited
		 * across a fork ()
		 */
		thr_ret = _wapi_handle_lock_shared_handles ();
		g_assert (thr_ret == 0);
	
		_wapi_handle_unlock_shared_handles ();
		
		/* should we detach from the process group? */

		/* Connect stdin, stdout and stderr */
		dup2 (in_fd, 0);
		dup2 (out_fd, 1);
		dup2 (err_fd, 2);

		if (inherit_handles != TRUE) {
			/* FIXME: do something here */
		}
		
		/* Close all file descriptors */
		for (i = getdtablesize () - 1; i > 2; i--) {
			close (i);
		}

		/* set cwd */
		if (chdir (dir) == -1) {
			/* set error */
			exit (-1);
		}

		// TODO: environment.		
		int exit_code = system (args);

		/* exec */
		//execve (argv[0], argv, env_strings);
		
		/* set error */
		exit (exit_code);
	}
	/* parent */
	
	ret = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
				   (gpointer *)&process_handle_data);
	if (ret == FALSE) {
		g_warning ("%s: error looking up process handle %p", __func__,
			   handle);
		_wapi_handle_unref (handle);
		goto cleanup;
	}
	
	process_handle_data->id = pid;
	
	if (process_info != NULL) {
		process_info->hProcess = handle;
		process_info->dwProcessId = pid;

		/* FIXME: we might need to handle the thread info some
		 * day
		 */
		process_info->hThread = NULL;
		process_info->dwThreadId = 0;
	}

cleanup:
	_wapi_handle_unlock_shared_handles ();

	if (cmd != NULL) {
		g_free (cmd);
	}
	if (args != NULL) {
		g_free (args);
	}
	if (dir != NULL) {
		g_free (dir);
	}
	
	return(ret);
}
		
static void process_set_name (struct _WapiHandle_process *process_handle)
{
	gchar *progname, *slash;
	
	progname=g_get_prgname ();

#ifdef __DEBUG__
	g_message ("%s: using [%s] as prog name", __func__, progname);
#endif

	if(progname!=NULL) {
		slash=strrchr (progname, '/');
		if(slash!=NULL) {
			g_strlcpy (process_handle->proc_name, slash+1,
				   _WAPI_PROC_NAME_MAX_LEN - 1);
		} else {
			g_strlcpy (process_handle->proc_name, progname,
				   _WAPI_PROC_NAME_MAX_LEN - 1);
		}

		g_free (progname);
	}
}

extern void _wapi_time_t_to_filetime (time_t timeval, WapiFileTime *filetime);

static void process_set_current (void)
{
	pid_t pid = _wapi_getpid ();
	char *handle_env;
	struct _WapiHandle_process process_handle = {0};
	
	handle_env = getenv ("_WAPI_PROCESS_HANDLE_OFFSET");
	if (handle_env != NULL) {
		struct _WapiHandle_process *process_handlep;
		guchar *procname = NULL;
		gboolean ok;
		
		current_process = _wapi_handle_new_from_offset (WAPI_HANDLE_PROCESS, atoi (handle_env), TRUE);
		
#ifdef __DEBUG__
		g_message ("%s: Found my process handle: %p (offset %d)",
			   __func__, current_process, atoi (handle_env));
#endif

		ok = _wapi_lookup_handle (current_process, WAPI_HANDLE_PROCESS,
					  (gpointer *)&process_handlep);
		if (ok == FALSE) {
			g_warning ("%s: error looking up process handle %p",
				   __func__, current_process);
			return;
		}

		/* This test will probably break on linuxthreads, but
		 * that should be ancient history on all distros we
		 * care about by now
		 */
		if (process_handlep->id == pid) {
			procname = process_handlep->proc_name;
			if (!strcmp (procname, "mono")) {
				/* Set a better process name */
#ifdef __DEBUG__
				g_message ("%s: Setting better process name",
					   __func__);
#endif

				process_set_name (process_handlep);
			} else {
#ifdef __DEBUG__
				g_message ("%s: Leaving process name: %s",
					   __func__, procname);
#endif
			}

			return;
		}

		/* Wrong pid, so drop this handle and fall through to
		 * create a new one
		 */
		_wapi_handle_unref (current_process);
	}

#ifdef __DEBUG__
	g_message ("%s: Need to create my own process handle", __func__);
#endif

	process_handle.id = pid;

	process_set_name (&process_handle);

	current_process = _wapi_handle_new (WAPI_HANDLE_PROCESS,
					    &process_handle);
	if (current_process == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating process handle", __func__);
		return;
	}
		
	/* Make sure the new handle has a reference so it wont go away
	 * until this process exits
	 */
	_wapi_handle_ref (current_process);
}

/* Returns a pseudo handle that doesn't need to be closed afterwards */
gpointer GetCurrentProcess (void)
{
	mono_once (&process_current_once, process_set_current);
		
	return((gpointer)-1);
}

guint32 GetProcessId (gpointer handle)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	
	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
				  (gpointer *)&process_handle);
	if (ok == FALSE) {
		SetLastError (EBADF);
		return (0);
	}
	
	return (process_handle->id);
}

guint32 GetCurrentProcessId (void)
{
	mono_once (&process_current_once, process_set_current);
		
	return (GetProcessId (current_process));
}

/* Returns the process id as a convenience to the functions that call this */
static pid_t signal_process_if_gone (gpointer handle)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	
	/* Make sure the process is signalled if it has exited - if
	 * the parent process didn't wait for it then it won't be
	 */
	ok = _wapi_lookup_handle (handle, WAPI_HANDLE_PROCESS,
				  (gpointer *)&process_handle);
	if (ok == FALSE) {
		/* It's possible that the handle has vanished during
		 * the _wapi_search_handle before it gets here, so
		 * don't spam the console with warnings.
		 */
/*		g_warning ("%s: error looking up process handle %p",
  __func__, handle);*/
		
		return (0);
	}
	
#ifdef __DEBUG__
	g_message ("%s: looking at process %d", __func__, process_handle->id);
#endif

	if (kill (process_handle->id, 0) == -1 &&
	    (errno == ESRCH ||
	     errno == EPERM)) {
		/* The process is dead, (EPERM tells us a new process
		 * has that ID, but as it's owned by someone else it
		 * can't be the one listed in our shared memory file)
		 */
		_wapi_shared_handle_set_signal_state (handle, TRUE);
	}

	return (process_handle->id);
}

static gboolean process_enum (gpointer handle, gpointer user_data)
{
	GArray *processes=user_data;
	pid_t pid = signal_process_if_gone (handle);
	int i;
	
	if (pid == 0) {
		return (FALSE);
	}
	
	/* Ignore processes that have already exited (ie they are signalled) */
	if (_wapi_handle_issignalled (handle) == FALSE) {
#ifdef __DEBUG__
		g_message ("%s: process %d added to array", __func__, pid);
#endif

		/* This ensures that duplicates aren't returned (see
		 * the comment above _wapi_search_handle () for why
		 * it's needed
		 */
		for (i = 0; i < processes->len; i++) {
			if (g_array_index (processes, pid_t, i) == pid) {
				/* We've already got this one, return
				 * FALSE to keep searching
				 */
				return (FALSE);
			}
		}
		
		g_array_append_val (processes, pid);
	}
	
	/* Return false to keep searching */
	return(FALSE);
}

static gboolean process_open_compare (gpointer handle, gpointer user_data)
{
	pid_t wanted_pid;
	pid_t checking_pid = signal_process_if_gone (handle);

	if (checking_pid == 0) {
		return(FALSE);
	}
	
	wanted_pid = GPOINTER_TO_UINT (user_data);

	/* It's possible to have more than one process handle with the
	 * same pid, but only the one running process can be
	 * unsignalled
	 */
	if (checking_pid == wanted_pid &&
	    _wapi_handle_issignalled (handle) == FALSE) {
		/* If the handle is blown away in the window between
		 * returning TRUE here and _wapi_search_handle pinging
		 * the timestamp, the search will continue
		 */
		return(TRUE);
	} else {
		return(FALSE);
	}
}

gboolean GetExitCodeProcess (gpointer process, guint32 *code)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	
	mono_once (&process_current_once, process_set_current);

	if(code==NULL) {
		return(FALSE);
	}
	
	ok=_wapi_lookup_handle (process, WAPI_HANDLE_PROCESS,
				(gpointer *)&process_handle);
	if(ok==FALSE) {
#ifdef __DEBUG__
		g_message ("%s: Can't find process %p", __func__, process);
#endif
		
		return(FALSE);
	}
	
	/* A process handle is only signalled if the process has exited
	 * and has been waited for */
	if (_wapi_handle_issignalled (process) == TRUE ||
	    process_wait (process, 0) == WAIT_OBJECT_0) {
		*code = process_handle->exitstatus;
	} else {
		*code = STILL_ACTIVE;
	}
	
	return(TRUE);
}

guint32 GetModuleBaseName (gpointer process, gpointer module,
			   gchar *basename, guint32 size)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	
	mono_once (&process_current_once, process_set_current);

#ifdef __DEBUG__
	g_message ("%s: Getting module base name, process handle %p module %p",
		   __func__, process, module);
#endif

	if(basename==NULL || size==0) {
		return(FALSE);
	}
	
	ok=_wapi_lookup_handle (process, WAPI_HANDLE_PROCESS,
				(gpointer *)&process_handle);
	if(ok==FALSE) {
#ifdef __DEBUG__
		g_message ("%s: Can't find process %p", __func__, process);
#endif
		
		return(FALSE);
	}

	if(module==NULL) {
		/* Shorthand for the main module, which has the
		 * process name recorded in the handle data
		 */
		pid_t pid;
		gchar *procname_utf8 = NULL;
		glong len;
		
#ifdef __DEBUG__
		g_message ("%s: Returning main module name", __func__);
#endif

		pid=process_handle->id;
		procname_utf8 = g_strdup (process_handle->proc_name);
	
#ifdef __DEBUG__
		g_message ("%s: Process name is [%s]", __func__,
			   procname_utf8);
#endif

		len = strlen (procname_utf8);

		if (procname_utf8 == NULL) {
			/* bugger */
			return(0);
		}

		/* Add the terminator, and convert chars to bytes */
		
		if (size < len + 1) {
#ifdef __DEBUG__
			g_message ("%s: Size %d smaller than needed (%ld); truncating", __func__, size, len + 1);
#endif

			memcpy (basename, procname_utf8, size);
		} else {
#ifdef __DEBUG__
			g_message ("%s: Size %d larger than needed (%ld)",
				   __func__, size, bytes);
#endif

			memcpy (basename, procname_utf8, len + 1);
		}
		
		g_free (procname_utf8);

		return(len);
	} else {
		/* Look up the address in /proc/<pid>/maps */
	}
	
	return(0);
}

gboolean
TerminateProcess (gpointer process, gint32 exitCode)
{
	struct _WapiHandle_process *process_handle;
	gboolean ok;
	int signo;
	int ret;

	ok = _wapi_lookup_handle (process, WAPI_HANDLE_PROCESS,
				  (gpointer *) &process_handle);

	if (ok == FALSE) {
#ifdef __DEBUG__
		g_message ("%s: Can't find process %p", __func__, process);
#endif
		SetLastError (EBADF);
		return FALSE;
	}

	signo = (exitCode == -1) ? SIGKILL : SIGTERM;
	ret = kill (process_handle->id, signo);
	if (ret == -1) {
		SetLastError (errno);		
	}
	
	return (ret == 0);
}

