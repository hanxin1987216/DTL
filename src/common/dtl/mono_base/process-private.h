/*
 * process-private.h: Private definitions for process handles
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_PROCESS_PRIVATE_H_
#define _WAPI_PROCESS_PRIVATE_H_

#include <config.h>
#include <glib.h>

extern struct _WapiHandleOps _wapi_process_ops;

#define _WAPI_PROC_NAME_MAX_LEN _POSIX_PATH_MAX

struct _WapiHandle_process
{
	pid_t id;
	guint32 exitstatus;
	gpointer main_thread;
	gchar proc_name[_WAPI_PROC_NAME_MAX_LEN];	
};

extern void _wapi_process_reap (void);

#endif /* _WAPI_PROCESS_PRIVATE_H_ */
