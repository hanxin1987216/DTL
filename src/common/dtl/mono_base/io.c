/*
 * io.c:  File, console and find handles
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
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <utime.h>
#include <unistd.h>

#include "wapi.h"
#include "wapi-private.h"
#include "handles-private.h"
#include "io-private.h"
#include "timefuncs-private.h"
#include "timefuncs.h"
#include "thread-private.h"
#include "strenc.h"

#undef _DEBUG

static void file_close (gpointer handle, gpointer data);
static WapiFileType file_getfiletype(void);
static gboolean file_read(gpointer handle, gpointer buffer,
			  guint32 numbytes, guint32 *bytesread,
			  WapiOverlapped *overlapped);
static gboolean file_write(gpointer handle, gconstpointer buffer,
			   guint32 numbytes, guint32 *byteswritten,
			   WapiOverlapped *overlapped);
static gboolean file_flush(gpointer handle);
static guint32 file_seek(gpointer handle, gint32 movedistance,
			 gint32 *highmovedistance, WapiSeekMethod method);
static gboolean file_setendoffile(gpointer handle);
static guint32 file_getfilesize(gpointer handle, guint32 *highsize);
static gboolean file_getfiletime(gpointer handle, WapiFileTime *create_time,
				 WapiFileTime *last_access,
				 WapiFileTime *last_write);
static gboolean file_setfiletime(gpointer handle,
				 const WapiFileTime *create_time,
				 const WapiFileTime *last_access,
				 const WapiFileTime *last_write);

/* File handle is only signalled for overlapped IO */
struct _WapiHandleOps _wapi_file_ops = {
	file_close,		/* close */
	NULL,			/* signal */
	NULL,			/* own */
	NULL,			/* is_owned */
};

void _wapi_file_details (gpointer handle_info)
{
	struct _WapiHandle_file *file = (struct _WapiHandle_file *)handle_info;
	
	g_print ("[%20s] acc: %c%c%c, shr: %c%c%c, attrs: %5u",
		 file->filename,
		 file->fileaccess&GENERIC_READ?'R':'.',
		 file->fileaccess&GENERIC_WRITE?'W':'.',
		 file->fileaccess&GENERIC_EXECUTE?'X':'.',
		 file->sharemode&FILE_SHARE_READ?'R':'.',
		 file->sharemode&FILE_SHARE_WRITE?'W':'.',
		 file->sharemode&FILE_SHARE_DELETE?'D':'.',
		 file->attrs);
}

static void console_close (gpointer handle, gpointer data);
static WapiFileType console_getfiletype(void);
static gboolean console_read(gpointer handle, gpointer buffer,
			     guint32 numbytes, guint32 *bytesread,
			     WapiOverlapped *overlapped);
static gboolean console_write(gpointer handle, gconstpointer buffer,
			      guint32 numbytes, guint32 *byteswritten,
			      WapiOverlapped *overlapped);

/* Console is mostly the same as file, except it can block waiting for
 * input or output
 */
struct _WapiHandleOps _wapi_console_ops = {
	console_close,		/* close */
	NULL,			/* signal */
	NULL,			/* own */
	NULL,			/* is_owned */
};

void _wapi_console_details (gpointer handle_info)
{
	_wapi_file_details (handle_info);
}

/* Find handle has no ops.
 */
struct _WapiHandleOps _wapi_find_ops = {
	NULL,			/* close */
	NULL,			/* signal */
	NULL,			/* own */
	NULL,			/* is_owned */
};

static void pipe_close (gpointer handle, gpointer data);
static WapiFileType pipe_getfiletype (void);
static gboolean pipe_read (gpointer handle, gpointer buffer, guint32 numbytes,
			   guint32 *bytesread, WapiOverlapped *overlapped);
static gboolean pipe_write (gpointer handle, gconstpointer buffer,
			    guint32 numbytes, guint32 *byteswritten,
			    WapiOverlapped *overlapped);

/* Pipe handles
 */
struct _WapiHandleOps _wapi_pipe_ops = {
	pipe_close,		/* close */
	NULL,			/* signal */
	NULL,			/* own */
	NULL,			/* is_owned */
};

void _wapi_pipe_details (gpointer handle_info)
{
	_wapi_file_details (handle_info);
}

static const struct {
	/* File, console and pipe handles */
	WapiFileType (*getfiletype)(void);
	
	/* File, console and pipe handles */
	gboolean (*readfile)(gpointer handle, gpointer buffer,
			     guint32 numbytes, guint32 *bytesread,
			     WapiOverlapped *overlapped);
	gboolean (*writefile)(gpointer handle, gconstpointer buffer,
			      guint32 numbytes, guint32 *byteswritten,
			      WapiOverlapped *overlapped);
	gboolean (*flushfile)(gpointer handle);
	
	/* File handles */
	guint32 (*seek)(gpointer handle, gint32 movedistance,
			gint32 *highmovedistance, WapiSeekMethod method);
	gboolean (*setendoffile)(gpointer handle);
	guint32 (*getfilesize)(gpointer handle, guint32 *highsize);
	gboolean (*getfiletime)(gpointer handle, WapiFileTime *create_time,
				WapiFileTime *last_access,
				WapiFileTime *last_write);
	gboolean (*setfiletime)(gpointer handle,
				const WapiFileTime *create_time,
				const WapiFileTime *last_access,
				const WapiFileTime *last_write);
} io_ops[WAPI_HANDLE_COUNT]={
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* file */
	{file_getfiletype,
	 file_read, file_write,
	 file_flush, file_seek,
	 file_setendoffile,
	 file_getfilesize,
	 file_getfiletime,
	 file_setfiletime},
	/* console */
	{console_getfiletype,
	 console_read,
	 console_write,
	 NULL, NULL, NULL, NULL, NULL, NULL},
	/* thread */
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* mutex */
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* event */
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* find */
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* process */
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	/* pipe */
	{pipe_getfiletype,
	 pipe_read,
	 pipe_write,
	 NULL, NULL, NULL, NULL, NULL, NULL},
};

/* Some utility functions.
 */

static guint32 _wapi_stat_to_file_attributes (struct stat *buf)
{
	guint32 attrs = 0;

	/* FIXME: this could definitely be better */

	/* Sockets (0140000) != Directory (040000) + Regular file (0100000) */
	//if (S_ISSOCK (buf->st_mode))
	//	buf->st_mode &= ~S_IFSOCK; /* don't consider socket protection */

	if (S_ISDIR (buf->st_mode))
		attrs |= FILE_ATTRIBUTE_DIRECTORY;
	else
		attrs |= FILE_ATTRIBUTE_ARCHIVE;
	
	if (!(buf->st_mode & S_IWUSR))
		attrs |= FILE_ATTRIBUTE_READONLY;
	
	if(S_ISLNK (buf->st_mode)) 
		attrs |= FILE_ATTRIBUTE_SYMBOLIC_LINK;

	if (S_ISCHR(buf->st_mode))
		attrs |= FILE_ATTRIBUTE_CHAR;
	
	if (S_ISBLK(buf->st_mode))
		attrs |= FILE_ATTRIBUTE_BLOCK;

	if (S_ISFIFO(buf->st_mode))
		attrs |= FILE_ATTRIBUTE_FIFO;
	
	if (S_ISSOCK(buf->st_mode))
		attrs |= FILE_ATTRIBUTE_SOCK;

	return attrs;
}

static void
_wapi_set_last_error_from_errno (void)
{
	SetLastError (_wapi_get_win32_file_error (errno));
}

/* Handle ops.
 */
static void file_close (gpointer handle, gpointer data)
{
	struct _WapiHandle_file *file_handle = (struct _WapiHandle_file *)data;
	
#ifdef _DEBUG
	g_message("%s: closing file handle %p [%s]", __func__, handle,
		  file_handle->filename);
#endif

	g_free (file_handle->filename);
	
	_wapi_handle_share_release (file_handle->share_info);
	
	close (GPOINTER_TO_UINT(handle));
}

static WapiFileType file_getfiletype(void)
{
	return(FILE_TYPE_DISK);
}

static gboolean file_read(gpointer handle, gpointer buffer,
			  guint32 numbytes, guint32 *bytesread,
			  WapiOverlapped *overlapped)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	int fd = GPOINTER_TO_UINT(handle);
	int ret;
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	if(bytesread!=NULL) {
		*bytesread=0;
	}
	
	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_READ access: %u",
			  __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}

	do {
		ret = read (fd, buffer, numbytes);
	} while (ret == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());
			
	if(ret==-1) {
		gint err = errno;

#ifdef _DEBUG
		g_message("%s: read of handle %p error: %s", __func__,
			  handle, strerror(err));
#endif
		SetLastError (_wapi_get_win32_file_error (err));
		return(FALSE);
	}
		
	if (bytesread != NULL) {
		*bytesread = ret;
	}
		
	return(TRUE);
}

static gboolean file_write(gpointer handle, gconstpointer buffer,
			   guint32 numbytes, guint32 *byteswritten,
			   WapiOverlapped *overlapped G_GNUC_UNUSED)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	int ret;
	off_t current_pos;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(byteswritten!=NULL) {
		*byteswritten=0;
	}
	
	if(!(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
		
	do {
		ret = write (fd, buffer, numbytes);
	} while (ret == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());
	
	if (ret == -1) {
		if (errno == EINTR) {
			ret = 0;
		} else {
			_wapi_set_last_error_from_errno ();
				
#ifdef _DEBUG
			g_message("%s: write of handle %p error: %s",
				  __func__, handle, strerror(errno));
#endif

			return(FALSE);
		}
	}
	if (byteswritten != NULL) {
		*byteswritten = ret;
	}
	return(TRUE);
}

static gboolean file_flush(gpointer handle)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	if(!(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}

	ret=fsync(fd);
	if (ret==-1) {
#ifdef _DEBUG
		g_message("%s: fsync of handle %p error: %s", __func__, handle,
			  strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
	
	return(TRUE);
}

static guint32 file_seek(gpointer handle, gint32 movedistance,
			 gint32 *highmovedistance, WapiSeekMethod method)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	off_t offset, newpos;
	int whence;
	guint32 ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(INVALID_SET_FILE_POINTER);
	}
	
	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message ("%s: handle %p doesn't have GENERIC_READ or GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(INVALID_SET_FILE_POINTER);
	}

	switch(method) {
	case FILE_BEGIN:
		whence=SEEK_SET;
		break;
	case FILE_CURRENT:
		whence=SEEK_CUR;
		break;
	case FILE_END:
		whence=SEEK_END;
		break;
	default:
#ifdef _DEBUG
		g_message("%s: invalid seek type %d", __func__, method);
#endif

		SetLastError (EINVAL);
		return(INVALID_SET_FILE_POINTER);
	}

#ifdef HAVE_LARGE_FILE_SUPPORT
	if(highmovedistance==NULL) {
		offset=movedistance;
#ifdef _DEBUG
		g_message("%s: setting offset to %lld (low %d)", __func__,
			  offset, movedistance);
#endif
	} else {
		offset=((gint64) *highmovedistance << 32) | (guint32)movedistance;
		
#ifdef _DEBUG
		g_message("%s: setting offset to %lld 0x%llx (high %d 0x%x, low %d 0x%x)", __func__, offset, offset, *highmovedistance, *highmovedistance, movedistance, movedistance);
#endif
	}
#else
	offset=movedistance;
#endif

#ifdef _DEBUG
#ifdef HAVE_LARGE_FILE_SUPPORT
	g_message("%s: moving handle %p by %lld bytes from %d", __func__,
		  handle, offset, whence);
#else
	g_message("%s: moving handle %p fd %d by %ld bytes from %d", __func__,
		  handle, offset, whence);
#endif
#endif

	newpos=lseek(fd, offset, whence);
	if(newpos==-1) {
#ifdef _DEBUG
		g_message("%s: lseek on handle %p returned error %s",
			  __func__, handle, strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(INVALID_SET_FILE_POINTER);
	}

#ifdef _DEBUG
#ifdef HAVE_LARGE_FILE_SUPPORT
	g_message("%s: lseek returns %lld", __func__, newpos);
#else
	g_message ("%s: lseek returns %ld", __func__, newpos);
#endif
#endif

#ifdef HAVE_LARGE_FILE_SUPPORT
	ret=newpos & 0xFFFFFFFF;
	if(highmovedistance!=NULL) {
		*highmovedistance=newpos>>32;
	}
#else
	ret=newpos;
	if(highmovedistance!=NULL) {
		/* Accurate, but potentially dodgy :-) */
		*highmovedistance=0;
	}
#endif

#ifdef _DEBUG
	g_message ("%s: move of handle %p returning %d/%d", __func__,
		   handle, ret, highmovedistance==NULL?0:*highmovedistance);
#endif

	return(ret);
}

static gboolean file_setendoffile(gpointer handle)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	struct stat statbuf;
	off_t size, pos;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(!(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}

	/* Find the current file position, and the file length.  If
	 * the file position is greater than the length, write to
	 * extend the file with a hole.  If the file position is less
	 * than the length, truncate the file.
	 */
	
	ret=fstat(fd, &statbuf);
	if(ret==-1) {
#ifdef _DEBUG
		g_message ("%s: handle %p fstat failed: %s", __func__,
			   handle, strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
	size=statbuf.st_size;

	pos=lseek(fd, (off_t)0, SEEK_CUR);
	if(pos==-1) {
#ifdef _DEBUG
		g_message("%s: handle %p lseek failed: %s", __func__,
			  handle, strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
	
	if(pos>size) {
		/* Extend the file.  Use write() here, because some
		 * manuals say that ftruncate() behaviour is undefined
		 * when the file needs extending.  The POSIX spec says
		 * that on XSI-conformant systems it extends, so if
		 * every system we care about conforms, then we can
		 * drop this write.
		 */
		do {
			ret = write (fd, "", 1);
		} while (ret == -1 && errno == EINTR &&
			 !_wapi_thread_cur_apc_pending());

		if(ret==-1) {
#ifdef _DEBUG
			g_message("%s: handle %p extend write failed: %s", __func__, handle, strerror(errno));
#endif

			_wapi_set_last_error_from_errno ();
			return(FALSE);
		}
	}

	/* always truncate, because the extend write() adds an extra
	 * byte to the end of the file
	 */
	do {
		ret=ftruncate(fd, pos);
	}
	while (ret==-1 && errno==EINTR && !_wapi_thread_cur_apc_pending()); 
	if(ret==-1) {
#ifdef _DEBUG
		g_message("%s: handle %p ftruncate failed: %s", __func__,
			  handle, strerror(errno));
#endif
		
		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
		
	return(TRUE);
}

static guint32 file_getfilesize(gpointer handle, guint32 *highsize)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	struct stat statbuf;
	guint32 size;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(INVALID_FILE_SIZE);
	}
	
	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_READ or GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(INVALID_FILE_SIZE);
	}

	/* If the file has a size with the low bits 0xFFFFFFFF the
	 * caller can't tell if this is an error, so clear the error
	 * value
	 */
	SetLastError (ERROR_SUCCESS);
	
	ret = fstat(fd, &statbuf);
	if (ret == -1) {
#ifdef _DEBUG
		g_message ("%s: handle %p fstat failed: %s", __func__,
			   handle, strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(INVALID_FILE_SIZE);
	}
	
#ifdef HAVE_LARGE_FILE_SUPPORT
	size = statbuf.st_size & 0xFFFFFFFF;
	if (highsize != NULL) {
		*highsize = statbuf.st_size>>32;
	}
#else
	if (highsize != NULL) {
		/* Accurate, but potentially dodgy :-) */
		*highsize = 0;
	}
	size = statbuf.st_size;
#endif

#ifdef _DEBUG
	g_message ("%s: Returning size %d/%d", __func__, size, *highsize);
#endif
	
	return(size);
}

static gboolean file_getfiletime(gpointer handle, WapiFileTime *create_time,
				 WapiFileTime *last_access,
				 WapiFileTime *last_write)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	struct stat statbuf;
	guint64 create_ticks, access_ticks, write_ticks;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_READ access: %u",
			  __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
	ret=fstat(fd, &statbuf);
	if(ret==-1) {
#ifdef _DEBUG
		g_message("%s: handle %p fstat failed: %s", __func__, handle,
			  strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}

#ifdef _DEBUG
	g_message("%s: atime: %ld ctime: %ld mtime: %ld", __func__,
		  statbuf.st_atime, statbuf.st_ctime,
		  statbuf.st_mtime);
#endif

	/* Try and guess a meaningful create time by using the older
	 * of atime or ctime
	 */
	/* The magic constant comes from msdn documentation
	 * "Converting a time_t Value to a File Time"
	 */
	if(statbuf.st_atime < statbuf.st_ctime) {
		create_ticks=((guint64)statbuf.st_atime*10000000)
			+ 116444736000000000ULL;
	} else {
		create_ticks=((guint64)statbuf.st_ctime*10000000)
			+ 116444736000000000ULL;
	}
	
	access_ticks=((guint64)statbuf.st_atime*10000000)+116444736000000000ULL;
	write_ticks=((guint64)statbuf.st_mtime*10000000)+116444736000000000ULL;
	
#ifdef _DEBUG
	g_message("%s: aticks: %llu cticks: %llu wticks: %llu", __func__,
		  access_ticks, create_ticks, write_ticks);
#endif

	if(create_time!=NULL) {
		create_time->dwLowDateTime = create_ticks & 0xFFFFFFFF;
		create_time->dwHighDateTime = create_ticks >> 32;
	}
	
	if(last_access!=NULL) {
		last_access->dwLowDateTime = access_ticks & 0xFFFFFFFF;
		last_access->dwHighDateTime = access_ticks >> 32;
	}
	
	if(last_write!=NULL) {
		last_write->dwLowDateTime = write_ticks & 0xFFFFFFFF;
		last_write->dwHighDateTime = write_ticks >> 32;
	}

	return(TRUE);
}

static gboolean file_setfiletime(gpointer handle,
				 const WapiFileTime *create_time G_GNUC_UNUSED,
				 const WapiFileTime *last_access,
				 const WapiFileTime *last_write)
{
	struct _WapiHandle_file *file_handle;
	gboolean ok;
	struct utimbuf utbuf;
	struct stat statbuf;
	guint64 access_ticks, write_ticks;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(!(file_handle->fileaccess & GENERIC_WRITE) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}

	if(file_handle->filename == NULL) {
#ifdef _DEBUG
		g_message("%s: handle %p unknown filename", __func__, handle);
#endif

		SetLastError (EBADF);
		return(FALSE);
	}
	
	/* Get the current times, so we can put the same times back in
	 * the event that one of the FileTime structs is NULL
	 */
	ret=fstat (fd, &statbuf);
	if(ret==-1) {
#ifdef _DEBUG
		g_message("%s: handle %p fstat failed: %s", __func__, handle,
			  strerror(errno));
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	if(last_access!=NULL) {
		access_ticks=((guint64)last_access->dwHighDateTime << 32) +
			last_access->dwLowDateTime;
		/* This is (time_t)0.  We can actually go to INT_MIN,
		 * but this will do for now.
		 */
		if (access_ticks < 116444736000000000ULL) {
#ifdef _DEBUG
			g_message ("%s: attempt to set access time too early",
				   __func__);
#endif
			SetLastError (EINVAL);
			return(FALSE);
		}
		
		utbuf.actime=(access_ticks - 116444736000000000ULL) / 10000000;
	} else {
		utbuf.actime=statbuf.st_atime;
	}

	if(last_write!=NULL) {
		write_ticks=((guint64)last_write->dwHighDateTime << 32) +
			last_write->dwLowDateTime;
		/* This is (time_t)0.  We can actually go to INT_MIN,
		 * but this will do for now.
		 */
		if (write_ticks < 116444736000000000ULL) {
#ifdef _DEBUG
			g_message ("%s: attempt to set write time too early",
				   __func__);
#endif
			SetLastError (EINVAL);
			return(FALSE);
		}
		
		utbuf.modtime=(write_ticks - 116444736000000000ULL) / 10000000;
	} else {
		utbuf.modtime=statbuf.st_mtime;
	}

#ifdef _DEBUG
	g_message("%s: setting handle %p access %ld write %ld", __func__,
		  handle, utbuf.actime, utbuf.modtime);
#endif

	ret=utime(file_handle->filename, &utbuf);
	if(ret==-1) {
#ifdef _DEBUG
		g_message("%s: handle %p [%s] utime failed: %s", __func__,
			  handle, file_handle->filename, strerror(errno));

#endif
		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
	
	return(TRUE);
}

static void console_close (gpointer handle, gpointer data)
{
	struct _WapiHandle_file *console_handle = (struct _WapiHandle_file *)data;
	
#ifdef _DEBUG
	g_message("%s: closing console handle %p", __func__, handle);
#endif

	g_free (console_handle->filename);
	
	close (GPOINTER_TO_UINT(handle));
}

static WapiFileType console_getfiletype(void)
{
	return(FILE_TYPE_CHAR);
}

static gboolean console_read(gpointer handle, gpointer buffer,
			     guint32 numbytes, guint32 *bytesread,
			     WapiOverlapped *overlapped G_GNUC_UNUSED)
{
	struct _WapiHandle_file *console_handle;
	gboolean ok;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_CONSOLE,
				(gpointer *)&console_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up console handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(bytesread!=NULL) {
		*bytesread=0;
	}
	
	if(!(console_handle->fileaccess & GENERIC_READ) &&
	   !(console_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message ("%s: handle %p doesn't have GENERIC_READ access: %u",
			   __func__, handle, console_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
	do {
		ret=read(fd, buffer, numbytes);
	} while (ret==-1 && errno==EINTR && !_wapi_thread_cur_apc_pending());

	if(ret==-1) {
#ifdef _DEBUG
		g_message("%s: read of handle %p error: %s", __func__, handle,
			  strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}
	
	if(bytesread!=NULL) {
		*bytesread=ret;
	}
	
	return(TRUE);
}

static gboolean console_write(gpointer handle, gconstpointer buffer,
			      guint32 numbytes, guint32 *byteswritten,
			      WapiOverlapped *overlapped G_GNUC_UNUSED)
{
	struct _WapiHandle_file *console_handle;
	gboolean ok;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_CONSOLE,
				(gpointer *)&console_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up console handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(byteswritten!=NULL) {
		*byteswritten=0;
	}
	
	if(!(console_handle->fileaccess & GENERIC_WRITE) &&
	   !(console_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, console_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
	do {
		ret = write(fd, buffer, numbytes);
	} while (ret == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());

	if (ret == -1) {
		if (errno == EINTR) {
			ret = 0;
		} else {
			_wapi_set_last_error_from_errno ();
			
#ifdef _DEBUG
			g_message ("%s: write of handle %p error: %s",
				   __func__, handle, strerror(errno));
#endif

			return(FALSE);
		}
	}
	if(byteswritten!=NULL) {
		*byteswritten=ret;
	}
	
	return(TRUE);
}

static void pipe_close (gpointer handle, gpointer data G_GNUC_UNUSED)
{
#ifdef _DEBUG
	g_message("%s: closing pipe handle %p", __func__, handle);
#endif

	/* No filename with pipe handles */

	close(GPOINTER_TO_UINT(handle));
}

static WapiFileType pipe_getfiletype(void)
{
	return(FILE_TYPE_PIPE);
}

static gboolean pipe_read (gpointer handle, gpointer buffer,
			   guint32 numbytes, guint32 *bytesread,
			   WapiOverlapped *overlapped G_GNUC_UNUSED)
{
	struct _WapiHandle_file *pipe_handle;
	gboolean ok;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_PIPE,
				(gpointer *)&pipe_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up pipe handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	if(bytesread!=NULL) {
		*bytesread=0;
	}
	
	if(!(pipe_handle->fileaccess & GENERIC_READ) &&
	   !(pipe_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_READ access: %u",
			  __func__, handle, pipe_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
#ifdef _DEBUG
	g_message ("%s: reading up to %d bytes from pipe %p", __func__,
		   numbytes, handle);
#endif

	do {
		ret=read(fd, buffer, numbytes);
	} while (ret==-1 && errno==EINTR && !_wapi_thread_cur_apc_pending());
		
	if (ret == -1) {
		if (errno == EINTR) {
			ret = 0;
		} else {
			_wapi_set_last_error_from_errno ();
			
#ifdef _DEBUG
			g_message("%s: read of handle %p error: %s", __func__,
				  handle, strerror(errno));
#endif

			return(FALSE);
		}
	}
	
#ifdef _DEBUG
	g_message ("%s: read %d bytes from pipe", __func__, ret);
#endif

	if(bytesread!=NULL) {
		*bytesread=ret;
	}
	
	return(TRUE);
}

static gboolean pipe_write(gpointer handle, gconstpointer buffer,
			   guint32 numbytes, guint32 *byteswritten,
			   WapiOverlapped *overlapped G_GNUC_UNUSED)
{
	struct _WapiHandle_file *pipe_handle;
	gboolean ok;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_PIPE,
				(gpointer *)&pipe_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up pipe handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}
	
	if(byteswritten!=NULL) {
		*byteswritten=0;
	}
	
	if(!(pipe_handle->fileaccess & GENERIC_WRITE) &&
	   !(pipe_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_WRITE access: %u", __func__, handle, pipe_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
#ifdef _DEBUG
	g_message ("%s: writing up to %d bytes to pipe %p", __func__, numbytes,
		   handle);
#endif

	do {
		ret = write (fd, buffer, numbytes);
	} while (ret == -1 && errno == EINTR &&
		 !_wapi_thread_cur_apc_pending());

	if (ret == -1) {
		if (errno == EINTR) {
			ret = 0;
		} else {
			_wapi_set_last_error_from_errno ();
			
#ifdef _DEBUG
			g_message("%s: write of handle %p error: %s", __func__,
				  handle, strerror(errno));
#endif

			return(FALSE);
		}
	}
	if(byteswritten!=NULL) {
		*byteswritten=ret;
	}
	
	return(TRUE);
}

static int convert_flags(guint32 fileaccess, guint32 createmode)
{
	int flags=0;
	
	switch(fileaccess) {
	case GENERIC_READ:
		flags=O_RDONLY;
		break;
	case GENERIC_WRITE:
		flags=O_WRONLY;
		break;
	case GENERIC_READ|GENERIC_WRITE:
		flags=O_RDWR;
		break;
	default:
#ifdef _DEBUG
		g_message("%s: Unknown access type 0x%x", __func__,
			  fileaccess);
#endif
		break;
	}

	switch(createmode) {
	case CREATE_NEW:
		flags|=O_CREAT|O_EXCL;
		break;
	case CREATE_ALWAYS:
		flags|=O_CREAT|O_TRUNC;
		break;
	case OPEN_EXISTING:
		break;
	case OPEN_ALWAYS:
		flags|=O_CREAT;
		break;
	case TRUNCATE_EXISTING:
		flags|=O_TRUNC;
		break;
	default:
#ifdef _DEBUG
		g_message("%s: Unknown create mode 0x%x", __func__,
			  createmode);
#endif
		break;
	}
	
	return(flags);
}

static guint32 convert_from_flags(int flags)
{
	guint32 fileaccess=0;
	
#ifndef O_ACCMODE
#define O_ACCMODE (O_RDONLY|O_WRONLY|O_RDWR)
#endif

	if((flags & O_ACCMODE) == O_RDONLY) {
		fileaccess=GENERIC_READ;
	} else if ((flags & O_ACCMODE) == O_WRONLY) {
		fileaccess=GENERIC_WRITE;
	} else if ((flags & O_ACCMODE) == O_RDWR) {
		fileaccess=GENERIC_READ|GENERIC_WRITE;
	} else {
#ifdef _DEBUG
		g_message("%s: Can't figure out flags 0x%x", __func__, flags);
#endif
	}

	/* Maybe sort out create mode too */

	return(fileaccess);
}

#if 0 /* unused */
static mode_t convert_perms(guint32 sharemode)
{
	mode_t perms=0600;
	
	if(sharemode&FILE_SHARE_READ) {
		perms|=044;
	}
	if(sharemode&FILE_SHARE_WRITE) {
		perms|=022;
	}

	return(perms);
}
#endif

static gboolean share_allows_open (struct stat *statbuf, guint32 sharemode,
				   guint32 fileaccess,
				   struct _WapiFileShare **share_info)
{
	gboolean file_already_shared;
	guint32 file_existing_share, file_existing_access;

	file_already_shared = _wapi_handle_get_or_set_share (statbuf->st_dev, statbuf->st_ino, sharemode, fileaccess, &file_existing_share, &file_existing_access, share_info);
	
	if (file_already_shared) {
		/* The reference to this share info was incremented
		 * when we looked it up, so be careful to put it back
		 * if we conclude we can't use this file.
		 */
		if (file_existing_share == 0) {
			/* Quick and easy, no possibility to share */
#ifdef _DEBUG
			g_message ("%s: Share mode prevents open: requested access: 0x%x, file has sharing = NONE", __func__, fileaccess);
#endif

			_wapi_handle_share_release (*share_info);
			
			return(FALSE);
		}

		if (((file_existing_share == FILE_SHARE_READ) &&
		     (fileaccess != GENERIC_READ)) ||
		    ((file_existing_share == FILE_SHARE_WRITE) &&
		     (fileaccess != GENERIC_WRITE))) {
			/* New access mode doesn't match up */
#ifdef _DEBUG
			g_message ("%s: Share mode prevents open: requested access: 0x%x, file has sharing: 0x%x", __func__, fileaccess, file_existing_share);
#endif

			_wapi_handle_share_release (*share_info);
		
			return(FALSE);
		}

		if (((file_existing_access & GENERIC_READ) &&
		     !(sharemode & FILE_SHARE_READ)) ||
		    ((file_existing_access & GENERIC_WRITE) &&
		     !(sharemode & FILE_SHARE_WRITE))) {
			/* New share mode doesn't match up */
#ifdef _DEBUG
			g_message ("%s: Access mode prevents open: requested share: 0x%x, file has access: 0x%x", __func__, sharemode, file_existing_access);
#endif

			_wapi_handle_share_release (*share_info);
		
			return(FALSE);
		}
	} else {
#ifdef _DEBUG
		g_message ("%s: New file!", __func__);
#endif
	}

	return(TRUE);
}

static gboolean share_check (struct stat *statbuf, guint32 sharemode,
			     guint32 fileaccess,
			     struct _WapiFileShare **share_info, int fd)
{
	if (share_allows_open (statbuf, sharemode, fileaccess,
			       share_info) == TRUE) {
		return (TRUE);
	}
	
	/* Got a share violation.  Double check that the file is still
	 * open by someone, in case a process crashed while still
	 * holding a file handle.  This will also cope with someone
	 * using Mono.Posix to close the file.  This is cheaper and
	 * less intrusive to other processes than initiating a handle
	 * collection.
	 */

	_wapi_handle_check_share (*share_info, fd);
	if (share_allows_open (statbuf, sharemode, fileaccess,
			       share_info) == TRUE) {
		return (TRUE);
	}
	
	/* Still violating.  It's possible that a process crashed
	 * while still holding a file handle, and that a non-mono
	 * process has the file open.  (For example, C-c mcs while
	 * editing a source file.)  As a last resort, run a handle
	 * collection, which will remove stale share entries.
	 */
	_wapi_handle_collect ();

	return(share_allows_open (statbuf, sharemode, fileaccess, share_info));
}

/**
 * CreateFile:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the file or other object to create.
 * @fileaccess: specifies the file access mode
 * @sharemode: whether the file should be shared.  This parameter is
 * currently ignored.
 * @security: Ignored for now.
 * @createmode: specifies whether to create a new file, whether to
 * overwrite an existing file, whether to truncate the file, etc.
 * @attrs: specifies file attributes and flags.  On win32 attributes
 * are characteristics of the file, not the handle, and are ignored
 * when an existing file is opened.  Flags give the library hints on
 * how to process a file to optimise performance.
 * @template: the handle of an open %GENERIC_READ file that specifies
 * attributes to apply to a newly created file, ignoring @attrs.
 * Normally this parameter is NULL.  This parameter is ignored when an
 * existing file is opened.
 *
 * Creates a new file handle.  This only applies to normal files:
 * pipes are handled by CreatePipe(), and console handles are created
 * with GetStdHandle().
 *
 * Return value: the new handle, or %INVALID_HANDLE_VALUE on error.
 */
gpointer CreateFile(const gchar *name, guint32 fileaccess,
		    guint32 sharemode, WapiSecurityAttributes *security,
		    guint32 createmode, guint32 attrs,
		    gpointer template G_GNUC_UNUSED)
{
	struct _WapiHandle_file file_handle = {0};
	gpointer handle;
	int flags=convert_flags(fileaccess, createmode);
	/*mode_t perms=convert_perms(sharemode);*/
	/* we don't use sharemode, because that relates to sharing of
	 * the file when the file is open and is already handled by
	 * other code, perms instead are the on-disk permissions and
	 * this is a sane default.
	 */
	mode_t perms=0644;
	int fd, ret;
	int handle_type;
	struct stat statbuf;

	if (name == NULL) {
#ifdef _DEBUG
		g_message ("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(INVALID_HANDLE_VALUE);
	}
	
#ifdef _DEBUG
	g_message ("%s: Opening %s with share 0x%x and access 0x%x", __func__,
		   name, sharemode, fileaccess);
#endif
	
	fd = open(name, flags, perms);
    
	/* If we were trying to open a directory with write permissions
	 * (e.g. O_WRONLY or O_RDWR), this call will fail with
	 * EISDIR. However, this is a bit bogus because calls to
	 * manipulate the directory (e.g. SetFileTime) will still work on
	 * the directory because they use other API calls
	 * (e.g. utime()). Hence, if we failed with the EISDIR error, try
	 * to open the directory again without write permission.
	 */
	if (fd == -1 && errno == EISDIR)
	{
		/* Try again but don't try to make it writable */
		fd = open(name, flags  & ~(O_RDWR|O_WRONLY), perms);
	}
	
	if (fd == -1) {
#ifdef _DEBUG
		g_message("%s: Error opening file %s: %s", __func__, name,
			  strerror(errno));
#endif
		_wapi_set_last_error_from_errno ();

		return(INVALID_HANDLE_VALUE);
	}

	if (fd >= _wapi_fd_reserve) {
		if (_wapi_fd_reserve == 0)
			g_message ("%s: _wapi_fd_reserve == 0, check the _wapi_init_handles has init.", __func__);

#ifdef _DEBUG
		g_message ("%s: File descriptor is too big", __func__);
#endif

		SetLastError (EMFILE);
		
		close (fd);
		
		return(INVALID_HANDLE_VALUE);
	}

	ret = fstat (fd, &statbuf);
	if (ret == -1) {
#ifdef _DEBUG
		g_message ("%s: fstat error of file %s: %s", __func__,
			   name, strerror (errno));
#endif
		_wapi_set_last_error_from_errno ();
		close (fd);
		
		return(INVALID_HANDLE_VALUE);
	}

	if (share_check (&statbuf, sharemode, fileaccess,
			 &file_handle.share_info, fd) == FALSE) {
		SetLastError (EBUSY);
		close (fd);
		
		return (INVALID_HANDLE_VALUE);
	}
	if (file_handle.share_info == NULL) {
		/* No space, so no more files can be opened */
#ifdef _DEBUG
		g_message ("%s: No space in the share table", __func__);
#endif

		SetLastError (EMFILE);
		close (fd);
		
		return(INVALID_HANDLE_VALUE);
	}
	
	file_handle.filename = g_strdup (name);

	if(security!=NULL) {
		//file_handle->security_attributes=_wapi_handle_scratch_store (
		//security, sizeof(WapiSecurityAttributes));
	}
	
	file_handle.fileaccess=fileaccess;
	file_handle.sharemode=sharemode;
	file_handle.attrs=attrs;

#ifndef S_ISFIFO
#define S_ISFIFO(m) ((m & S_IFIFO) != 0)
#endif
	handle_type = (S_ISFIFO (statbuf.st_mode)) ? WAPI_HANDLE_PIPE : WAPI_HANDLE_FILE;
	handle = _wapi_handle_new_fd ((WapiHandleType)handle_type, fd, &file_handle);
	if (handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating file handle", __func__);
		close (fd);
		
		SetLastError (ENOMEM);
		return(INVALID_HANDLE_VALUE);
	}
	
#ifdef _DEBUG
	g_message("%s: returning handle %p", __func__, handle);
#endif
	
	return(handle);
}

/**
 * DeleteFile:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the file to be deleted.
 *
 * Deletes file @name.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean DeleteFile(const gchar *name)
{
	int ret;
	
	if(name==NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	ret=unlink(name);
	
	if(ret==0) {
		return(TRUE);
	}

	_wapi_set_last_error_from_errno ();
	return(FALSE);
}

/**
 * MoveFile:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the file to be moved.
 * @dest_name: a pointer to a NULL-terminated unicode string, that is the
 * new name for the file.
 *
 * Renames file @name to @dest_name.
 * MoveFile sets EEXIST if the destination exists, except
 * when it is the same file as the source.  In that case it silently succeeds.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean MoveFile (const gchar *name, const gchar *dest_name)
{
	int result;
	struct stat stat_src, stat_dest;
	
	if(name==NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	if(dest_name==NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	/*
	 * In C# land we check for the existence of src, but not for dest.
	 * We check it here and return the failure if dest exists and is not
	 * the same file as src.
	 */
	if (!stat (dest_name, &stat_dest) && !stat (name, &stat_src)) {
		if (stat_dest.st_dev != stat_src.st_dev || stat_dest.st_ino != stat_src.st_ino) {
			SetLastError (EEXIST);
			return FALSE;
		}	
	}

	result = rename (name, dest_name);

	if (result != 0 && errno == EXDEV) {
		/* Try a copy to the new location, and delete the source */
		if (CopyFile (name, dest_name, TRUE)==FALSE) {
			/* CopyFile will set the error */
			return(FALSE);
		}
		
		return(DeleteFile (name));
	}

	if (result == 0) {
		return TRUE;
	}
	
	switch (errno) {
	case EEXIST:
		SetLastError (EEXIST);
		break;
	
	default:
		_wapi_set_last_error_from_errno ();
		break;
	}

	return FALSE;
}

/**
 * CopyFile:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the file to be copied.
 * @dest_name: a pointer to a NULL-terminated unicode string, that is the
 * new name for the file.
 * @fail_if_exists: if TRUE and dest_name exists, the copy will fail.
 *
 * Copies file @name to @dest_name
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean CopyFile (const gchar *name, const gchar *dest_name,
		   gboolean fail_if_exists)
{
	int src_fd, dest_fd;
	int buf_size;
	char *buf;
	int remain, n;
	struct stat st;
	
	if(name==NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}
	
	if(dest_name==NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}
	
	src_fd = open (name, O_RDONLY);
	if (src_fd < 0) {
		_wapi_set_last_error_from_errno ();

		return(FALSE);
	}

	if (fstat (src_fd, &st) < 0) {
		_wapi_set_last_error_from_errno ();

		close (src_fd);
		
		return(FALSE);
	}
	
	if (fail_if_exists) {
		dest_fd = open (dest_name, O_WRONLY | O_CREAT, st.st_mode);
	} else {
		dest_fd = open (dest_name, O_WRONLY | O_TRUNC, st.st_mode);
		if (dest_fd < 0) {
			/* O_TRUNC might cause a fail if the file
			 * doesn't exist
			 */
			dest_fd = open (dest_name, O_WRONLY | O_CREAT,
					st.st_mode);
		}
	}
	if (dest_fd < 0) {
		_wapi_set_last_error_from_errno ();

		close (src_fd);
		
		return(FALSE);
	}
	
	buf_size = st.st_blksize;
	buf = (char *) alloca (buf_size);
	
	for (;;) {
		remain = read (src_fd, buf, buf_size);
		
		if (remain < 0) {
			if (errno == EINTR && !_wapi_thread_cur_apc_pending()) {
				continue;
			}
			
			_wapi_set_last_error_from_errno ();

			close (src_fd);
			close (dest_fd);
			
			return(FALSE);
		}
		
		if (remain == 0) {
			break;
		}

		while (remain > 0) {
			if ((n = write (dest_fd, buf, remain)) < 0) {
				if (errno == EINTR && !_wapi_thread_cur_apc_pending())
					continue;

				_wapi_set_last_error_from_errno ();
#ifdef _DEBUG
				g_message ("%s: write failed.", __func__);
#endif

				close (src_fd);
				close (dest_fd);

				return (FALSE);
			}

			remain -= n;
		}
	}

	close (src_fd);
	close (dest_fd);

	return(TRUE);
}

static mono_once_t stdhandle_once=MONO_ONCE_INIT;
static gpointer stdin_handle=INVALID_HANDLE_VALUE;
static gpointer stdout_handle=INVALID_HANDLE_VALUE;
static gpointer stderr_handle=INVALID_HANDLE_VALUE;

static gpointer stdhandle_create (int fd, const guchar *name)
{
	struct _WapiHandle_file file_handle = {0};
	gpointer handle;
	int flags;
	
#ifdef _DEBUG
	g_message("%s: creating standard handle type %s, fd %d", __func__,
		  name, fd);
#endif
	
	/* Check if fd is valid */
	do {
		flags=fcntl(fd, F_GETFL);
	} while (flags == -1 && errno == EINTR);

	if(flags==-1) {
		/* Invalid fd.  Not really much point checking for EBADF
		 * specifically
		 */
#ifdef _DEBUG
		g_message("%s: fcntl error on fd %d: %s", __func__, fd,
			  strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(INVALID_HANDLE_VALUE);
	}

	file_handle.filename = g_strdup(name);
	/* some default security attributes might be needed */
	file_handle.security_attributes=0;
	file_handle.fileaccess=convert_from_flags(flags);
	file_handle.sharemode=0;
	file_handle.attrs=0;

	handle = _wapi_handle_new_fd (WAPI_HANDLE_CONSOLE, fd, &file_handle);
	if (handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating file handle", __func__);
		SetLastError (ENOMEM);
		return(INVALID_HANDLE_VALUE);
	}
	
#ifdef _DEBUG
	g_message("%s: returning handle %p", __func__, handle);
#endif

	return(handle);
}

static void stdhandle_init (void)
{
	//
	// fix: hanxin 警告： 给指针时目标与指针有/无符号不一致
	stdin_handle=stdhandle_create (0, (const guchar *)"<stdin>");
	stdout_handle=stdhandle_create (1, (const guchar *)"<stdout>");
	stderr_handle=stdhandle_create (2, (const guchar *)"<stderr>");
}

/**
 * GetStdHandle:
 * @stdhandle: specifies the file descriptor
 *
 * Returns a handle for stdin, stdout, or stderr.  Always returns the
 * same handle for the same @stdhandle.
 *
 * Return value: the handle, or %INVALID_HANDLE_VALUE on error
 */

gpointer GetStdHandle(WapiStdHandle stdhandle)
{
	gpointer handle;
	
	mono_once (&stdhandle_once, stdhandle_init);
	
	switch(stdhandle) {
	case STD_INPUT_HANDLE:
		handle=stdin_handle;
		break;

	case STD_OUTPUT_HANDLE:
		handle=stdout_handle;
		break;

	case STD_ERROR_HANDLE:
		handle=stderr_handle;
		break;

	default:
#ifdef _DEBUG
		g_message("%s: unknown standard handle type", __func__);
#endif

		SetLastError (EINVAL);
		return(INVALID_HANDLE_VALUE);
	}

	if (handle == INVALID_HANDLE_VALUE) {
		SetLastError (ENFILE);
		return(INVALID_HANDLE_VALUE);
	}
	
	/* Add a reference to this handle */
	_wapi_handle_ref (handle);
	
	return(handle);
}

/**
 * ReadFile:
 * @handle: The file handle to read from.  The handle must have
 * %GENERIC_READ access.
 * @buffer: The buffer to store read data in
 * @numbytes: The maximum number of bytes to read
 * @bytesread: The actual number of bytes read is stored here.  This
 * value can be zero if the handle is positioned at the end of the
 * file.
 * @overlapped: points to a required %WapiOverlapped structure if
 * @handle has the %FILE_FLAG_OVERLAPPED option set, should be NULL
 * otherwise.
 *
 * If @handle does not have the %FILE_FLAG_OVERLAPPED option set, this
 * function reads up to @numbytes bytes from the file from the current
 * file position, and stores them in @buffer.  If there are not enough
 * bytes left in the file, just the amount available will be read.
 * The actual number of bytes read is stored in @bytesread.

 * If @handle has the %FILE_FLAG_OVERLAPPED option set, the current
 * file position is ignored and the read position is taken from data
 * in the @overlapped structure.
 *
 * Return value: %TRUE if the read succeeds (even if no bytes were
 * read due to an attempt to read past the end of the file), %FALSE on
 * error.
 */
gboolean ReadFile(gpointer handle, gpointer buffer, guint32 numbytes,
		  guint32 *bytesread, WapiOverlapped *overlapped)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if(io_ops[type].readfile==NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].readfile (handle, buffer, numbytes, bytesread,
				      overlapped));
}

/**
 * WriteFile:
 * @handle: The file handle to write to.  The handle must have
 * %GENERIC_WRITE access.
 * @buffer: The buffer to read data from.
 * @numbytes: The maximum number of bytes to write.
 * @byteswritten: The actual number of bytes written is stored here.
 * If the handle is positioned at the file end, the length of the file
 * is extended.  This parameter may be %NULL.
 * @overlapped: points to a required %WapiOverlapped structure if
 * @handle has the %FILE_FLAG_OVERLAPPED option set, should be NULL
 * otherwise.
 *
 * If @handle does not have the %FILE_FLAG_OVERLAPPED option set, this
 * function writes up to @numbytes bytes from @buffer to the file at
 * the current file position.  If @handle is positioned at the end of
 * the file, the file is extended.  The actual number of bytes written
 * is stored in @byteswritten.
 *
 * If @handle has the %FILE_FLAG_OVERLAPPED option set, the current
 * file position is ignored and the write position is taken from data
 * in the @overlapped structure.
 *
 * Return value: %TRUE if the write succeeds, %FALSE on error.
 */
gboolean WriteFile(gpointer handle, gconstpointer buffer, guint32 numbytes,
		   guint32 *byteswritten, WapiOverlapped *overlapped)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if(io_ops[type].writefile==NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].writefile (handle, buffer, numbytes, byteswritten,
				       overlapped));
}

/**
 * FlushFileBuffers:
 * @handle: Handle to open file.  The handle must have
 * %GENERIC_WRITE access.
 *
 * Flushes buffers of the file and causes all unwritten data to
 * be written.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean FlushFileBuffers(gpointer handle)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if(io_ops[type].flushfile==NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].flushfile (handle));
}

/**
 * SetEndOfFile:
 * @handle: The file handle to set.  The handle must have
 * %GENERIC_WRITE access.
 *
 * Moves the end-of-file position to the current position of the file
 * pointer.  This function is used to truncate or extend a file.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean SetEndOfFile(gpointer handle)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].setendoffile == NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].setendoffile (handle));
}

/**
 * SetFilePointer:
 * @handle: The file handle to set.  The handle must have
 * %GENERIC_READ or %GENERIC_WRITE access.
 * @movedistance: Low 32 bits of a signed value that specifies the
 * number of bytes to move the file pointer.
 * @highmovedistance: Pointer to the high 32 bits of a signed value
 * that specifies the number of bytes to move the file pointer, or
 * %NULL.
 * @method: The starting point for the file pointer move.
 *
 * Sets the file pointer of an open file.
 *
 * The distance to move the file pointer is calculated from
 * @movedistance and @highmovedistance: If @highmovedistance is %NULL,
 * @movedistance is the 32-bit signed value; otherwise, @movedistance
 * is the low 32 bits and @highmovedistance a pointer to the high 32
 * bits of a 64 bit signed value.  A positive distance moves the file
 * pointer forward from the position specified by @method; a negative
 * distance moves the file pointer backward.
 *
 * If the library is compiled without large file support,
 * @highmovedistance is ignored and its value is set to zero on a
 * successful return.
 *
 * Return value: On success, the low 32 bits of the new file pointer.
 * If @highmovedistance is not %NULL, the high 32 bits of the new file
 * pointer are stored there.  On failure, %INVALID_SET_FILE_POINTER.
 */
guint32 SetFilePointer(gpointer handle, gint32 movedistance,
		       gint32 *highmovedistance, WapiSeekMethod method)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].seek == NULL) {
		SetLastError (EBADF);
		return(INVALID_SET_FILE_POINTER);
	}
	
	return(io_ops[type].seek (handle, movedistance, highmovedistance,
				  method));
}

/**
 * GetFileType:
 * @handle: The file handle to test.
 *
 * Finds the type of file @handle.
 *
 * Return value: %FILE_TYPE_UNKNOWN - the type of the file @handle is
 * unknown.  %FILE_TYPE_DISK - @handle is a disk file.
 * %FILE_TYPE_CHAR - @handle is a character device, such as a console.
 * %FILE_TYPE_PIPE - @handle is a named or anonymous pipe.
 */
WapiFileType GetFileType(gpointer handle)
{
	WapiHandleType type;

	if (!_WAPI_PRIVATE_HAVE_SLOT (handle)) {
		SetLastError (EBADF);
		return(FILE_TYPE_UNKNOWN);
	}

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].getfiletype == NULL) {
		SetLastError (EBADF);
		return(FILE_TYPE_UNKNOWN);
	}
	
	return(io_ops[type].getfiletype ());
}

/**
 * GetFileSize:
 * @handle: The file handle to query.  The handle must have
 * %GENERIC_READ or %GENERIC_WRITE access.
 * @highsize: If non-%NULL, the high 32 bits of the file size are
 * stored here.
 *
 * Retrieves the size of the file @handle.
 *
 * If the library is compiled without large file support, @highsize
 * has its value set to zero on a successful return.
 *
 * Return value: On success, the low 32 bits of the file size.  If
 * @highsize is non-%NULL then the high 32 bits of the file size are
 * stored here.  On failure %INVALID_FILE_SIZE is returned.
 */
guint32 GetFileSize(gpointer handle, guint32 *highsize)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].getfilesize == NULL) {
		SetLastError (EBADF);
		return(INVALID_FILE_SIZE);
	}
	
	return(io_ops[type].getfilesize (handle, highsize));
}

/**
 * GetFileTime:
 * @handle: The file handle to query.  The handle must have
 * %GENERIC_READ access.
 * @create_time: Points to a %WapiFileTime structure to receive the
 * number of ticks since the epoch that file was created.  May be
 * %NULL.
 * @last_access: Points to a %WapiFileTime structure to receive the
 * number of ticks since the epoch when file was last accessed.  May be
 * %NULL.
 * @last_write: Points to a %WapiFileTime structure to receive the
 * number of ticks since the epoch when file was last written to.  May
 * be %NULL.
 *
 * Finds the number of ticks since the epoch that the file referenced
 * by @handle was created, last accessed and last modified.  A tick is
 * a 100 nanosecond interval.  The epoch is Midnight, January 1 1601
 * GMT.
 *
 * Create time isn't recorded on POSIX file systems or reported by
 * stat(2), so that time is guessed by returning the oldest of the
 * other times.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean GetFileTime(gpointer handle, WapiFileTime *create_time,
		     WapiFileTime *last_access, WapiFileTime *last_write)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].getfiletime == NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].getfiletime (handle, create_time, last_access,
					 last_write));
}

/**
 * SetFileTime:
 * @handle: The file handle to set.  The handle must have
 * %GENERIC_WRITE access.
 * @create_time: Points to a %WapiFileTime structure that contains the
 * number of ticks since the epoch that the file was created.  May be
 * %NULL.
 * @last_access: Points to a %WapiFileTime structure that contains the
 * number of ticks since the epoch when the file was last accessed.
 * May be %NULL.
 * @last_write: Points to a %WapiFileTime structure that contains the
 * number of ticks since the epoch when the file was last written to.
 * May be %NULL.
 *
 * Sets the number of ticks since the epoch that the file referenced
 * by @handle was created, last accessed or last modified.  A tick is
 * a 100 nanosecond interval.  The epoch is Midnight, January 1 1601
 * GMT.
 *
 * Create time isn't recorded on POSIX file systems, and is ignored.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean SetFileTime(gpointer handle, const WapiFileTime *create_time,
		     const WapiFileTime *last_access,
		     const WapiFileTime *last_write)
{
	WapiHandleType type;

	type = _wapi_handle_type (handle);
	
	if (io_ops[type].setfiletime == NULL) {
		SetLastError (EBADF);
		return(FALSE);
	}
	
	return(io_ops[type].setfiletime (handle, create_time, last_access,
					 last_write));
}

/* A tick is a 100-nanosecond interval.  File time epoch is Midnight,
 * January 1 1601 GMT
 */

#define TICKS_PER_MILLISECOND 10000L
#define TICKS_PER_SECOND 10000000L
#define TICKS_PER_MINUTE 600000000L
#define TICKS_PER_HOUR 36000000000LL
#define TICKS_PER_DAY 864000000000LL

#define isleap(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))

static const guint16 mon_yday[2][13]={
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
	{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366},
};

/**
 * FileTimeToSystemTime:
 * @file_time: Points to a %WapiFileTime structure that contains the
 * number of ticks to convert.
 * @system_time: Points to a %WapiSystemTime structure to receive the
 * broken-out time.
 *
 * Converts a tick count into broken-out time values.
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean FileTimeToSystemTime(const WapiFileTime *file_time,
			      WapiSystemTime *system_time)
{
	gint64 file_ticks, totaldays, rem, y;
	const guint16 *ip;
	
	if(system_time==NULL) {
#ifdef _DEBUG
		g_message("%s: system_time NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}
	
	file_ticks=((gint64)file_time->dwHighDateTime << 32) +
		file_time->dwLowDateTime;
	
	/* Really compares if file_ticks>=0x8000000000000000
	 * (LLONG_MAX+1) but we're working with a signed value for the
	 * year and day calculation to work later
	 */
	if(file_ticks<0) {
#ifdef _DEBUG
		g_message("%s: file_time too big", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	totaldays=(file_ticks / TICKS_PER_DAY);
	rem = file_ticks % TICKS_PER_DAY;
#ifdef _DEBUG
	g_message("%s: totaldays: %lld rem: %lld", __func__, totaldays, rem);
#endif

	system_time->wHour=rem/TICKS_PER_HOUR;
	rem %= TICKS_PER_HOUR;
#ifdef _DEBUG
	g_message("%s: Hour: %d rem: %lld", __func__, system_time->wHour, rem);
#endif
	
	system_time->wMinute = rem / TICKS_PER_MINUTE;
	rem %= TICKS_PER_MINUTE;
#ifdef _DEBUG
	g_message("%s: Minute: %d rem: %lld", __func__, system_time->wMinute,
		  rem);
#endif
	
	system_time->wSecond = rem / TICKS_PER_SECOND;
	rem %= TICKS_PER_SECOND;
#ifdef _DEBUG
	g_message("%s: Second: %d rem: %lld", __func__, system_time->wSecond,
		  rem);
#endif
	
	system_time->wMilliseconds = rem / TICKS_PER_MILLISECOND;
#ifdef _DEBUG
	g_message("%s: Milliseconds: %d", __func__,
		  system_time->wMilliseconds);
#endif

	/* January 1, 1601 was a Monday, according to Emacs calendar */
	system_time->wDayOfWeek = ((1 + totaldays) % 7);
#ifdef _DEBUG
	g_message("%s: Day of week: %d", __func__, system_time->wDayOfWeek);
#endif
	
	/* This algorithm to find year and month given days from epoch
	 * from glibc
	 */
	y=1601;
	
#define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) (DIV(y, 4) - DIV (y, 100) + DIV (y, 400))

	while(totaldays < 0 || totaldays >= (isleap(y)?366:365)) {
		/* Guess a corrected year, assuming 365 days per year */
		gint64 yg = y + totaldays / 365 - (totaldays % 365 < 0);
#ifdef _DEBUG
		g_message("%s: totaldays: %lld yg: %lld y: %lld", __func__,
			  totaldays, yg,
			  y);
		g_message("%s: LEAPS(yg): %lld LEAPS(y): %lld", __func__,
			  LEAPS_THRU_END_OF(yg-1), LEAPS_THRU_END_OF(y-1));
#endif
		
		/* Adjust days and y to match the guessed year. */
		totaldays -= ((yg - y) * 365
			      + LEAPS_THRU_END_OF (yg - 1)
			      - LEAPS_THRU_END_OF (y - 1));
#ifdef _DEBUG
		g_message("%s: totaldays: %lld", __func__, totaldays);
#endif
		y = yg;
#ifdef _DEBUG
		g_message("%s: y: %lld", __func__, y);
#endif
	}
	
	system_time->wYear = y;
#ifdef _DEBUG
	g_message("%s: Year: %d", __func__, system_time->wYear);
#endif

	ip = mon_yday[isleap(y)];
	
	for(y=11; totaldays < ip[y]; --y) {
		continue;
	}
	totaldays-=ip[y];
#ifdef _DEBUG
	g_message("%s: totaldays: %lld", __func__, totaldays);
#endif
	
	system_time->wMonth = y + 1;
#ifdef _DEBUG
	g_message("%s: Month: %d", __func__, system_time->wMonth);
#endif

	system_time->wDay = totaldays + 1;
#ifdef _DEBUG
	g_message("%s: Day: %d", __func__, system_time->wDay);
#endif
	
	return(TRUE);
}

static gint
file_compare (gconstpointer a, gconstpointer b)
{
	gchar *astr = *(gchar **) a;
	gchar *bstr = *(gchar **) b;

	return strcmp (astr, bstr);
}

static gint
get_errno_from_g_file_error (gint error)
{
	switch (error) {
#ifdef EACCESS
	case G_FILE_ERROR_ACCES:
		error = EACCES;
		break;
#endif
#ifdef ENAMETOOLONG
	case G_FILE_ERROR_NAMETOOLONG:
		error = ENAMETOOLONG;
		break;
#endif
#ifdef ENOENT
	case G_FILE_ERROR_NOENT:
		error = ENOENT;
		break;
#endif
#ifdef ENOTDIR
	case G_FILE_ERROR_NOTDIR:
		error = ENOTDIR;
		break;
#endif
#ifdef ENXIO
	case G_FILE_ERROR_NXIO:
		error = ENXIO;
		break;
#endif
#ifdef ENODEV
	case G_FILE_ERROR_NODEV:
		error = ENODEV;
		break;
#endif
#ifdef EROFS
	case G_FILE_ERROR_ROFS:
		error = EROFS;
		break;
#endif
#ifdef ETXTBSY
	case G_FILE_ERROR_TXTBSY:
		error = ETXTBSY;
		break;
#endif
#ifdef EFAULT
	case G_FILE_ERROR_FAULT:
		error = EFAULT;
		break;
#endif
#ifdef ELOOP
	case G_FILE_ERROR_LOOP:
		error = ELOOP;
		break;
#endif
#ifdef ENOSPC
	case G_FILE_ERROR_NOSPC:
		error = ENOSPC;
		break;
#endif
#ifdef ENOMEM
	case G_FILE_ERROR_NOMEM:
		error = ENOMEM;
		break;
#endif
#ifdef EMFILE
	case G_FILE_ERROR_MFILE:
		error = EMFILE;
		break;
#endif
#ifdef ENFILE
	case G_FILE_ERROR_NFILE:
		error = ENFILE;
		break;
#endif
#ifdef EBADF
	case G_FILE_ERROR_BADF:
		error = EBADF;
		break;
#endif
#ifdef EINVAL
	case G_FILE_ERROR_INVAL:
		error = EINVAL;
		break;
#endif
#ifdef EPIPE
	case G_FILE_ERROR_PIPE:
		error = EPIPE;
		break;
#endif
#ifdef EAGAIN
	case G_FILE_ERROR_AGAIN:
		error = EAGAIN;
		break;
#endif
#ifdef EINTR
	case G_FILE_ERROR_INTR:
		error = EINTR;
		break;
#endif
#ifdef EWIO
	case G_FILE_ERROR_IO:
		error = EIO;
		break;
#endif
#ifdef EPERM
	case G_FILE_ERROR_PERM:
		error = EPERM;
		break;
#endif
	case G_FILE_ERROR_FAILED:
		error = EINVAL;
		break;
	}

	return error;
}

/* scandir using glib */
static gint
mono_io_scandir (const gchar *dirname, const gchar *pattern, gchar ***namelist)
{
	GError *error = NULL;
	GDir *dir;
	GPtrArray *names;
	const gchar *name;
	gint result;
	GPatternSpec *patspec;

	dir = g_dir_open (dirname, 0, &error);
	if (dir == NULL) {
		/* g_dir_open returns ENOENT on directories on which we don't
		 * have read/x permission */
		gint errnum = get_errno_from_g_file_error (error->code);
		g_error_free (error);
		if (errnum == ENOENT && g_file_test (dirname, G_FILE_TEST_IS_DIR))
			errnum = EACCES;

		errno = errnum;
		return -1;
	}

	patspec = g_pattern_spec_new (pattern);
	names = g_ptr_array_new ();
	while ((name = g_dir_read_name (dir)) != NULL) {
		if (g_pattern_match_string (patspec, name))
			g_ptr_array_add (names, g_strdup (name));
	}
	
	g_pattern_spec_free (patspec);
	g_dir_close (dir);
	result = names->len;
	if (result > 0) {
		g_ptr_array_sort (names, file_compare);
		g_ptr_array_set_size (names, result + 1);

		*namelist = (gchar **) g_ptr_array_free (names, FALSE);
	} else {
		g_ptr_array_free (names, TRUE);
	}

	return result;
}

gpointer FindFirstFile (const gchar *pattern, WapiFindData *find_data)
{
	struct _WapiHandle_find find_handle = {0};
	gpointer handle;
	gchar *dir_part, *entry_part;
	int result;
	
	if (pattern == NULL) {
#ifdef _DEBUG
		g_message ("%s: pattern is NULL", __func__);
#endif

		SetLastError (ENOTDIR);
		return(INVALID_HANDLE_VALUE);
	}

#ifdef _DEBUG
	g_message ("%s: looking for [%s]", __func__, pattern);
#endif
	
	/* Figure out which bit of the pattern is the directory */
	dir_part = g_path_get_dirname (pattern);
	entry_part = g_path_get_basename (pattern);

#if 0
	/* Don't do this check for now, it breaks if directories
	 * really do have metachars in their names (see bug 58116).
	 * FIXME: Figure out a better solution to keep some checks...
	 */
	if (strchr (dir_part, '*') || strchr (dir_part, '?')) {
		SetLastError (EINVAL);
		g_free (dir_part);
		g_free (entry_part);
		return(INVALID_HANDLE_VALUE);
	}
#endif

	/* The pattern can specify a directory or a set of files.
	 *
	 * The pattern can have wildcard characters ? and *, but only
	 * in the section after the last directory delimiter.  (Return
	 * EINVAL if there are wildcards in earlier path
	 * sections.)  "*" has the usual 0-or-more chars meaning.  "?" 
	 * means "match one character", "??" seems to mean "match one
	 * or two characters", "???" seems to mean "match one, two or
	 * three characters", etc.  Windows will also try and match
	 * the mangled "short name" of files, so 8 character patterns
	 * with wildcards will show some surprising results.
	 *
	 * All the written documentation I can find says that '?' 
	 * should only match one character, and doesn't mention '??',
	 * '???' etc.  I'm going to assume that the strict behaviour
	 * (ie '???' means three and only three characters) is the
	 * correct one, because that lets me use fnmatch(3) rather
	 * than mess around with regexes.
	 */

	find_handle.namelist = NULL;
	result = mono_io_scandir (dir_part, entry_part, &find_handle.namelist);
	
	if (result < 0) {
#ifdef _DEBUG
		gint errnum = errno;
#endif
		_wapi_set_last_error_from_errno ();
#ifdef _DEBUG
		g_message ("%s: scandir error: %s", __func__,
			   g_strerror (errnum));
#endif
		g_free (entry_part);
		g_free (dir_part);
		return (INVALID_HANDLE_VALUE);
	}

	g_free (entry_part);
	
#ifdef _DEBUG
	g_message ("%s: Got %d matches", __func__, result);
#endif

	find_handle.dir_part = dir_part;
	find_handle.num = result;
	find_handle.count = 0;
	
	handle = _wapi_handle_new (WAPI_HANDLE_FIND, &find_handle);
	if (handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating find handle", __func__);
		g_free (dir_part);
		SetLastError (ENOMEM);
		
		return(INVALID_HANDLE_VALUE);
	}

	if (handle != INVALID_HANDLE_VALUE &&
	    !FindNextFile (handle, find_data)) {
		FindClose (handle);
		SetLastError (ENFILE);
		handle = INVALID_HANDLE_VALUE;
	}

	return (handle);
}

gboolean FindNextFile (gpointer handle, WapiFindData *find_data)
{
	struct _WapiHandle_find *find_handle;
	gboolean ok;
	struct stat buf;
	gchar *filename;
	gchar *utf8_filename, *utf8_basename;
	time_t create_time;
	int thr_ret;
	int bytes;
	gboolean ret = FALSE;
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FIND,
				(gpointer *)&find_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up find handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	pthread_cleanup_push ((void(*)(void *))_wapi_handle_unlock_handle,
			      handle);
	thr_ret = _wapi_handle_lock_handle (handle);
	g_assert (thr_ret == 0);
	
retry:
	if (find_handle->count >= find_handle->num) {
		SetLastError (ENFILE);
		goto cleanup;
	}

	/* stat next match */

	filename = g_build_filename (find_handle->dir_part, find_handle->namelist[find_handle->count ++], NULL);
	if (lstat (filename, &buf) != 0) {
#ifdef _DEBUG
		g_message ("%s: lstat failed: %s", __func__, filename);
#endif

		g_free (filename);
		goto retry;
	}

	/* hx: Don't return target file directly, if we back up root path /, may occur dead loop.
     * /mnt/sdb/.Trash-0/files/sdb ---> /mnt/sdb
	 */
	/*if(S_ISLNK (buf.st_mode)) {
		if(stat (filename, &buf) != 0) {
			g_free (filename);
			goto retry;
		}
	}*/
	
#ifdef __S_IFIFO
	/*
	 @hx: If the file is pipe file, ignore it, because ReadFile will be blocked if FIFO, see bug 3286 
	*/
	if (S_ISFIFO (buf.st_mode)) {
		g_free (filename);
		goto retry;
	}
#endif

	utf8_filename = mono_utf8_from_external (filename);
	if (utf8_filename == NULL) {
		/*
		  转换失败，说明文件名并不是 UTF8 格式，可能是使用 GB2312 等编码保存的字符串记录，为了保证正常显示读取，直接使用旧编码内容做文件名
		  utf8_filename 指向 filename 资源，并在后面执行时使用 g_free (utf8_filename) 释放 filename 资源
		 */
		utf8_filename = filename;
	}
	else {
		/*
		  编码转换成功 filename 内容已经复制一份到 utf8_filename 中，因此释放 filename 资源
		*/
		g_free (filename);
	}
	
#ifdef _DEBUG
	g_message ("%s: Found [%s]", __func__, utf8_filename);
#endif
	
	/* fill data block */

	if (buf.st_mtime < buf.st_ctime)
		create_time = buf.st_mtime;
	else
		create_time = buf.st_ctime;
	
	find_data->dwFileAttributes = _wapi_stat_to_file_attributes (&buf);

	_wapi_time_t_to_filetime (create_time, &find_data->ftCreationTime);
	_wapi_time_t_to_filetime (buf.st_atime, &find_data->ftLastAccessTime);
	_wapi_time_t_to_filetime (buf.st_mtime, &find_data->ftLastWriteTime);

	if (find_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		find_data->nFileSizeHigh = 0;
		find_data->nFileSizeLow = 0;
	} else {
		find_data->nFileSizeHigh = buf.st_size >> 32;
		find_data->nFileSizeLow = buf.st_size & 0xFFFFFFFF;
	}

	find_data->dwReserved0 = 0;
	find_data->dwReserved1 = 0;

	utf8_basename = g_path_get_basename (utf8_filename);

	ret = TRUE;
	
	/* Truncating a utf8 string like this might leave the last
	 * char incomplete
	 */
	bytes = strlen (utf8_basename);

	if (bytes < MAX_PATH -1) {
		memcpy (find_data->cFileName, 
			     utf8_basename, 
			     bytes);
		find_data->cFileName[bytes] = '\0';
	}
	else {
		memcpy (find_data->cFileName, 
			  utf8_basename, 
			  MAX_PATH-1);
		find_data->cFileName[MAX_PATH-1] = '\0';
	}
	
	find_data->cAlternateFileName [0] = 0;	/* not used */

	g_free (utf8_basename);
	g_free (utf8_filename);

cleanup:
	thr_ret = _wapi_handle_unlock_handle (handle);
	g_assert (thr_ret == 0);
	pthread_cleanup_pop (0);
	
	return(ret);
}

/**
 * FindClose:
 * @wapi_handle: the find handle to close.
 *
 * Closes find handle @wapi_handle
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean FindClose (gpointer handle)
{
	struct _WapiHandle_find *find_handle;
	gboolean ok;
	int thr_ret;

	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FIND,
				(gpointer *)&find_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up find handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	pthread_cleanup_push ((void(*)(void *))_wapi_handle_unlock_handle,
			      handle);
	thr_ret = _wapi_handle_lock_handle (handle);
	g_assert (thr_ret == 0);
	
	g_strfreev (find_handle->namelist);
	g_free (find_handle->dir_part);

	thr_ret = _wapi_handle_unlock_handle (handle);
	g_assert (thr_ret == 0);
	pthread_cleanup_pop (0);
	
	_wapi_handle_unref (handle);
	
	return(TRUE);
}

/**
 * CreateDirectory:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the directory to be created.
 * @security: ignored for now
 *
 * Creates directory @name
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean CreateDirectory (const gchar *name,
			  WapiSecurityAttributes *security)
{
	int result;
	struct stat buf;
	guint32 attrs;
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}
	
	result = mkdir (name, 0777);

	if (result == 0) {
		return TRUE;
	}

	if (errno == EEXIST) {
		result = stat (name, &buf);
		if (result == -1) {
			_wapi_set_last_error_from_errno ();
			return FALSE;
		}

		attrs = _wapi_stat_to_file_attributes (&buf);
		if ((attrs & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
			return TRUE;

		errno = EEXIST;
		_wapi_set_last_error_from_errno ();
		return FALSE;
	}

	_wapi_set_last_error_from_errno ();
	return FALSE;
}

/**
 * RemoveDirectory:
 * @name: a pointer to a NULL-terminated unicode string, that names
 * the directory to be removed.
 *
 * Removes directory @name
 *
 * Return value: %TRUE on success, %FALSE otherwise.
 */
gboolean RemoveDirectory (const gchar *name)
{
	int result;
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	result = rmdir (name);

	if (result == 0)
		return TRUE;
	
	_wapi_set_last_error_from_errno ();
	return FALSE;
}

/**
 * GetFileAttributes:
 * @name: a pointer to a NULL-terminated unicode filename.
 *
 * Gets the attributes for @name;
 *
 * Return value: %INVALID_FILE_ATTRIBUTES on failure
 */
guint32 GetFileAttributes (const gchar *name)
{
	struct stat buf;
	int result;
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}
	
	result = lstat (name, &buf);

	if (result != 0) {
		_wapi_set_last_error_from_errno ();
		return (INVALID_FILE_ATTRIBUTES);
	}
	
	return _wapi_stat_to_file_attributes (&buf);
}

static gboolean get_file_info_by_handle (gpointer handle, gpointer fileInfo, gboolean reGetInfo)
{
	WapiFileAttributesDataEx *data = 0;

	struct _WapiHandle_file *file_handle;
	gboolean ok;
	time_t create_time;
	struct stat statbuf;
	int ret;
	int fd = GPOINTER_TO_UINT(handle);
	
	ok=_wapi_lookup_handle (handle, WAPI_HANDLE_FILE,
				(gpointer *)&file_handle);
	if(ok==FALSE) {
		g_warning ("%s: error looking up file handle %p", __func__,
			   handle);
		SetLastError (EBADF);
		return(FALSE);
	}

	if(!(file_handle->fileaccess & GENERIC_READ) &&
	   !(file_handle->fileaccess & GENERIC_ALL)) {
#ifdef _DEBUG
		g_message("%s: handle %p doesn't have GENERIC_READ access: %u",
			  __func__, handle, file_handle->fileaccess);
#endif

		SetLastError (EACCES);
		return(FALSE);
	}
	
	if (reGetInfo == TRUE) 
		ret=lstat(file_handle->filename, &statbuf);
	else
		ret=fstat(fd, &statbuf);
	
	if(ret==-1) {
#ifdef _DEBUG
	if (reGetInfo == TRUE) 
		g_message("%s: handle %p lstat failed: %s", __func__, handle,
	else
		g_message("%s: handle %p fstat failed: %s", __func__, handle,
			  strerror(errno));
#endif

		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}

	/* fill data block */
	data = (WapiFileAttributesDataEx *)fileInfo;

	if (statbuf.st_mtime < statbuf.st_ctime)
		create_time = statbuf.st_mtime;
	else
		create_time = statbuf.st_ctime;
	
	data->dwFileAttributes = _wapi_stat_to_file_attributes (&statbuf);

	_wapi_time_t_to_filetime (create_time, & (data->ftCreationTime));
	_wapi_time_t_to_filetime (statbuf.st_atime, &(data->ftLastAccessTime));
	_wapi_time_t_to_filetime (statbuf.st_mtime, &(data->ftLastWriteTime));

	if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		data->nFileSizeHigh = 0;
		data->nFileSizeLow = 0;
	}
	else {
		data->nFileSizeHigh = statbuf.st_size >> 32;
		data->nFileSizeLow = statbuf.st_size & 0xFFFFFFFF;
	}

	// parameter for windows, do not exists under linux.
	data->dwVolumeSerialNumber = 0;
	data->nNumberOfLinks = 0;
	data->nFileIndexHigh = 0;
	data->nFileIndexLow = 0;

	/**
	 * fill linux file privilege info.
	 */
	data->st_mode = statbuf.st_mode;
	data->st_uid = statbuf.st_uid;
	data->st_gid = statbuf.st_gid;

	// get the name of a symbolic link
	if (S_ISLNK (statbuf.st_mode)) {
		ssize_t len;
		if ((len = readlink (file_handle->filename,
							 data->cTargetFileName, 
							 MAX_PATH - 1)) != -1)
			data->cTargetFileName[len] = '\0';
	}

	return TRUE;
}

gboolean GetFileInformationByHandleEx (gpointer handle, gpointer fileInfo)
{
	gboolean reGetInfo = TRUE;
	return get_file_info_by_handle (handle, fileInfo, reGetInfo);
}

gboolean GetFileInformationByHandle (gpointer handle, gpointer fileInfo)
{
	gboolean reGetInfo = FALSE;
	return get_file_info_by_handle (handle, fileInfo, reGetInfo);
}


/**
 * GetFileAttributesEx:
 * @name: a pointer to a NULL-terminated unicode filename.
 * @level: must be GetFileExInfoStandard
 * @info: pointer to a WapiFileAttributesData structure
 *
 * Gets attributes, size and filetimes for @name;
 *
 * Return value: %TRUE on success, %FALSE on failure
 */
gboolean GetFileAttributesEx (const gchar *name, WapiGetFileExInfoLevels level, gpointer info)
{
	WapiFileAttributesData *data;

	struct stat buf;
	time_t create_time;
	int result;
	
	if (level != GetFileExInfoStandard) {
#ifdef _DEBUG
		g_message ("%s: info level %d not supported.", __func__,
			   level);
#endif

		SetLastError (EINVAL);
		return FALSE;
	}
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	result = lstat (name, &buf);

	if (result != 0) {
		_wapi_set_last_error_from_errno ();
		return FALSE;
	}

	/* fill data block */

	data = (WapiFileAttributesData *)info;

	if (buf.st_mtime < buf.st_ctime)
		create_time = buf.st_mtime;
	else
		create_time = buf.st_ctime;
	
	data->dwFileAttributes = _wapi_stat_to_file_attributes (&buf);

	_wapi_time_t_to_filetime (create_time, &data->ftCreationTime);
	_wapi_time_t_to_filetime (buf.st_atime, &data->ftLastAccessTime);
	_wapi_time_t_to_filetime (buf.st_mtime, &data->ftLastWriteTime);

	if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		data->nFileSizeHigh = 0;
		data->nFileSizeLow = 0;
	}
	else {
		data->nFileSizeHigh = buf.st_size >> 32;
		data->nFileSizeLow = buf.st_size & 0xFFFFFFFF;
	}

	return TRUE;
}

/**
 * SetFileAttributes
 * @name: name of file
 * @attrs: attributes to set
 *
 * Changes the attributes on a named file.
 *
 * Return value: %TRUE on success, %FALSE on failure.
 */
extern gboolean SetFileAttributes (const gchar *name, guint32 attrs)
{
	/* FIXME: think of something clever to do on unix */
	struct stat buf;
	int result;

	/*
	 * Currently we only handle one *internal* case, with a value that is
	 * not standard: 0x80000000, which means `set executable bit'
	 */
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	result = lstat (name, &buf);
	if (result != 0) {
		_wapi_set_last_error_from_errno ();
		return FALSE;
	}

	/* Contrary to the documentation, ms allows NORMAL to be
	 * specified along with other attributes, so dont bother to
	 * catch that case here.
	 */
	if (attrs & FILE_ATTRIBUTE_READONLY) {
		result = chmod (name, buf.st_mode & ~(S_IWRITE | S_IWOTH | S_IWGRP));
	} else {
		result = chmod (name, buf.st_mode | S_IWRITE);
	}

	/* Ignore the other attributes for now */

	if (attrs & 0x80000000){
		mode_t exec_mask = 0;

		if ((buf.st_mode & S_IRUSR) != 0)
			exec_mask |= S_IXUSR;

		if ((buf.st_mode & S_IRGRP) != 0)
			exec_mask |= S_IXGRP;

		if ((buf.st_mode & S_IROTH) != 0)
			exec_mask |= S_IXOTH;

		result = chmod (name, buf.st_mode | exec_mask);
	}
	/* Don't bother to reset executable (might need to change this
	 * policy)
	 */
	
	return(TRUE);
}

/**
 * GetCurrentDirectory
 * @length: size of the buffer
 * @buffer: pointer to buffer that recieves path
 *
 * Retrieves the current directory for the current process.
 *
 * Return value: number of characters in buffer on success, zero on failure
 */
extern guint32 GetCurrentDirectory (guint32 length, gchar *buffer)
{
	gchar *path;
	glong count;
	
	path = g_get_current_dir ();
	if (path == NULL)
		return 0;

	/* if buffer too small, return number of characters required.
	 * this is plain dumb.
	 */

	count = strlen (path);	
	if (count > length) {
		g_free(path);
		
		return (count);
	}

	/* Add the terminator */

	memset (buffer, '\0', count + 1);
	memcpy (buffer, path, count);
	
	g_free (path);

	return count;
}

/**
 * SetCurrentDirectory
 * @path: path to new directory
 *
 * Changes the directory path for the current process.
 *
 * Return value: %TRUE on success, %FALSE on failure.
 */
extern gboolean SetCurrentDirectory (const gchar *path)
{
	gboolean result;

	if (chdir (path) != 0) {
		_wapi_set_last_error_from_errno ();
		result = FALSE;
	}
	else
		result = TRUE;

	return result;
}

gboolean CreatePipe (gpointer *readpipe, gpointer *writepipe,
		     WapiSecurityAttributes *security G_GNUC_UNUSED, guint32 size)
{
	struct _WapiHandle_file pipe_read_handle = {0};
	struct _WapiHandle_file pipe_write_handle = {0};
	gpointer read_handle;
	gpointer write_handle;
	int filedes[2];
	int ret;
	
#ifdef _DEBUG
	g_message ("%s: Creating pipe", __func__);
#endif

	ret=pipe (filedes);
	if(ret==-1) {
#ifdef _DEBUG
		g_message ("%s: Error creating pipe: %s", __func__,
			   strerror (errno));
#endif
		
		_wapi_set_last_error_from_errno ();
		return(FALSE);
	}

	if (filedes[0] >= _wapi_fd_reserve ||
	    filedes[1] >= _wapi_fd_reserve) {
#ifdef _DEBUG
		g_message ("%s: File descriptor is too big", __func__);
#endif

		SetLastError (EMFILE);
		
		close (filedes[0]);
		close (filedes[1]);
		
		return(FALSE);
	}
	
	/* filedes[0] is open for reading, filedes[1] for writing */

	pipe_read_handle.fileaccess = GENERIC_READ;
	read_handle = _wapi_handle_new_fd (WAPI_HANDLE_PIPE, filedes[0],
					   &pipe_read_handle);
	if (read_handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating pipe read handle", __func__);
		close (filedes[0]);
		close (filedes[1]);
		SetLastError (ENOMEM);
		
		return(FALSE);
	}
	
	pipe_write_handle.fileaccess = GENERIC_WRITE;
	write_handle = _wapi_handle_new_fd (WAPI_HANDLE_PIPE, filedes[1],
					    &pipe_write_handle);
	if (write_handle == _WAPI_HANDLE_INVALID) {
		g_warning ("%s: error creating pipe write handle", __func__);
		_wapi_handle_unref (read_handle);
		
		close (filedes[0]);
		close (filedes[1]);
		SetLastError (ENOMEM);
		
		return(FALSE);
	}
	
	*readpipe = read_handle;
	*writepipe = write_handle;

#ifdef _DEBUG
	g_message ("%s: Returning pipe: read handle %p, write handle %p",
		   __func__, read_handle, write_handle);
#endif

	return(TRUE);
}

guint32 GetTempPath (guint32 len, gchar *buf)
{
	gchar *tmpdir=g_strdup (g_get_tmp_dir ());
	glong dirlen;
	guint32 ret;
	
	if(tmpdir[strlen (tmpdir)]!='/') {
		g_free (tmpdir);
		tmpdir=g_strdup_printf ("%s/", g_get_tmp_dir ());
	}
	
	dirlen = strlen (tmpdir);	
		
	if(dirlen+1>len) {
#ifdef _DEBUG
		g_message ("%s: Size %d smaller than needed (%ld)",
				    __func__, len, dirlen+1);
#endif
		
		ret=dirlen+1;
	} else {
		/* Add the terminator */
		memset (buf, '\0', dirlen+1);
		memcpy (buf, tmpdir, dirlen);
		
		ret=dirlen;
	}

	g_free (tmpdir);
	
	return(ret);
}

gint32
GetLogicalDriveStrings (guint32 len, gchar *buf)
{
	FILE *fp;
	glong length, total = 0;
	gchar buffer [512];
	memset (buffer, 0, 512);
	gchar **splitted;
	gchar *dir;

	if (buf != 0 && len > 3) {
		memset (buf, 0, len); 
		buf [0] = '/';
		buf [1] = 0;
		buf [2] = 0;
	}

	/* Sigh, mntent and friends don't work well.
	 * It stops on the first line that doesn't begin with a '/'.
	 * (linux 2.6.5, libc 2.3.2.ds1-12) - Gonz */
	fp = fopen ("/etc/mtab", "rw");
	if (fp == NULL) {
		fp = fopen ("/etc/mnttab", "rw");
		if (fp == NULL)
			return 1;
	}

	while (fgets (buffer, 512, fp) != NULL) {
		if (*buffer != '/')
			continue;

		splitted = g_strsplit (buffer, " ", 0);
		if (!*splitted || !*(splitted + 1)) {
			g_strfreev (splitted);
			continue;
		}

		dir = *(splitted + 1);
		length = strlen (dir);		

		/*if (total + length + 1 > len) {
			fclose (fp);
			return len * 2; 
		}*/

		if (buf != 0)
			memcpy (buf + total, dir, length);
			
		total += length + 1;
		g_strfreev (splitted);
	}

	fclose (fp);
	return total;
/* Commented out, does not work with my mtab!!! - Gonz */
#ifdef NOTENABLED /* HAVE_MNTENT_H */
{
	FILE *fp;
	struct mntent *mnt;
	gunichar2 *ptr, *dir;
	glong len, total = 0;
	

	fp = setmntent ("/etc/mtab", "rt");
	if (fp == NULL) {
		fp = setmntent ("/etc/mnttab", "rt");
		if (fp == NULL)
			return;
	}

	ptr = buf;
	while ((mnt = getmntent (fp)) != NULL) {
		g_print ("GOT %s\n", mnt->mnt_dir);
		dir = g_utf8_to_utf16 (mnt->mnt_dir, &len, NULL, NULL, NULL);
		if (total + len + 1 > len) {
			return len * 2; /* guess */
		}

		memcpy (ptr + total, dir, sizeof (gunichar2) * len);
		g_free (dir);
		total += len + 1;
	}

	endmntent (fp);
	return total;
}
#endif
}

/**
 * SetFileAttributesEx
 * @name: name of file
 * @pFileInfo: extra file information in linux to set
 *
 * Changes the attributes on a named file.
 *
 * Return value: %TRUE on success, %FALSE on failure.
 */
extern gboolean SetFileAttributesEx (const gchar *name, const BY_HANDLE_FILE_INFORMATION * pFileInfo)
{
	/* FIXME: think of something clever to do on unix */
	struct stat buf;
	int result;

	/*
	 * Currently we only handle one *internal* case, with a value that is
	 * not standard: 0x80000000, which means `set executable bit'
	 */
	
	if (name == NULL) {
#ifdef _DEBUG
		g_message("%s: name is NULL", __func__);
#endif

		SetLastError (EINVAL);
		return(FALSE);
	}

	result = lstat (name, &buf);
	if (result != 0) {
		_wapi_set_last_error_from_errno ();
		return FALSE;
	}

	/* Contrary to the documentation, ms allows NORMAL to be
	 * specified along with other attributes, so dont bother to
	 * catch that case here.
	 */
	/*
		@yy_cn:
			当 chmod 放在前面，添加带有 S 属性的权限后
			执行 chown 会将 S 属性清除掉，因此将 chown 提前执行
			
			经测试无任何问题
	*/
	result = chown (name, pFileInfo->st_uid, pFileInfo->st_gid);
	result = chmod (name, pFileInfo->st_mode);

	return(TRUE);
}
