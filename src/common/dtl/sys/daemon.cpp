/***************************************************************************************************
daemon.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	后台服务类

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"
#include "../lang/string.h"

#include "daemon.h"

static char                **g_main_Argv = NULL;			/* pointer to argument vector */
static char                *g_main_LastArgv = NULL;        /* end of argv */

void prename_setproctitle_init(int argc, char **argv, char **envp);
void prename_setproctitle(const char *fmt, ...);


/* 父进程信号处理 */
static void kill_signal_master(const int sig) {
	
	// 删除PID文件 
	//remove(settings_pidfile);
	//
    // 给进程组发送SIGTERM信号，结束子进程
    //
	kill(0, SIGTERM);
	
    exit(0);
}


// public 
void 
Daemon::init (const String& processName, int argc, char *argv[], char *envp[], fun_ptr workerHandler)
{
	pid_t pid;

	if ((pid = fork()) != 0) {
		exit(0);
	}

	setsid();

	if ((pid = fork()) != 0) {
		exit(0);
	}

	int prename_num = 1;
	char exe_path_file[1024] = { 0 }; // exe_path_file 为 httpsqs 程序的绝对路径

	readlink("/proc/self/exe", exe_path_file, sizeof(exe_path_file));

	String prename_str;
	prename_str.append (exe_path_file);

	for (prename_num = 1; prename_num < argc; prename_num++) {
		String tmp;
		tmp.format (" %s", argv[prename_num]);
		prename_str.append (tmp);
	}

    /* 重命名httpsqs主进程，便于ps -ef命令查看 */
    prename_setproctitle_init(argc, argv, envp);
    prename_setproctitle("[%s: master] %s", processName.getCStr (), prename_str.getCStr ());

    pid_t worker_pid_wait;
    pid_t worker_pid = fork();

	 /* 如果派生进程失败，则退出程序 */
    if (worker_pid < 0)
    {
        fprintf(stderr, "Error: %s:%d\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
    }
    /* httpsqs父进程内容 */
	if (worker_pid > 0)
	{
		/* 处理父进程接收到的kill信号 */
		
		/* 忽略Broken Pipe信号 */
		signal(SIGPIPE, SIG_IGN);
	
		/* 处理kill信号 */
		signal (SIGINT, kill_signal_master);
		signal (SIGKILL, kill_signal_master);
		signal (SIGQUIT, kill_signal_master);
		signal (SIGTERM, kill_signal_master);
		signal (SIGHUP, kill_signal_master);
	
		/* 处理段错误信号 */
		signal(SIGSEGV, kill_signal_master);

        /* 如果子进程终止，则重新派生新的子进程 */
        while (1)
        {
            worker_pid_wait = wait(NULL);
            if (worker_pid_wait < 0)
            {
                continue;
            }
			usleep(100000);
            worker_pid = fork();
            if (worker_pid == 0)
            {
                break;
            }
		}
	}
	
	/* ---------------以下为httpsqs子进程内容------------------- */
	
	/* 忽略Broken Pipe信号 */
	signal(SIGPIPE, SIG_IGN);
	
	/* 处理kill信号 */
	signal (SIGINT, workerHandler);
	signal (SIGKILL, workerHandler);
	signal (SIGQUIT, workerHandler);
	signal (SIGTERM, workerHandler);
	signal (SIGHUP, workerHandler);
	
    /* 处理段错误信号 */
    signal(SIGSEGV, workerHandler);	
	

    /* 重命名httpsqs子进程，便于ps -ef命令查看 */
    prename_setproctitle_init(argc, argv, envp);
    prename_setproctitle("[%s: worker] %s", processName.getCStr (), prename_str.getCStr ());	
	
}



/*
用于进程重命名，主进程、子进程使用不同的命令，便于命令ps -ef查看。
*/

#include <stdarg.h>
#include <string.h>

# define MAXLINE 2048

#ifdef Linux
  #include <sys/prctl.h>
#endif

void prename_setproctitle_init(int argc, char **argv, char **envp)
{
    int i;
	for (i = 0; envp[i] != NULL; i++)
        continue;

	g_main_Argv = argv;
    if (i > 0)
      g_main_LastArgv = envp[i - 1] + strlen(envp[i - 1]);
    else
      g_main_LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);

}

void prename_setproctitle(const char *fmt, ...)
{
	char *p;
	int i;
	char buf[MAXLINE];

	extern char **g_main_Argv;
	extern char *g_main_LastArgv;
	va_list ap;
	p = buf;

	va_start(ap, fmt);
    vsprintf(p, fmt, ap);
    va_end(ap);


    i = strlen(buf);

	if (i > g_main_LastArgv - g_main_Argv[0] - 2)
	{
		i = g_main_LastArgv - g_main_Argv[0] - 2;
		buf[i] = '\0';
	}

    (void) strcpy(g_main_Argv[0], buf);
    p = &g_main_Argv[0][i];
	while (p < g_main_LastArgv)
		*p++ = '\0';//SPT_PADCHAR;
    
	g_main_Argv[1] = NULL;
}
