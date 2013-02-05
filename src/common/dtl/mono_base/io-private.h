/*
 * io-private.h:  Private definitions for file, console and find handles
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_IO_PRIVATE_H_
#define _WAPI_IO_PRIVATE_H_

#include <config.h>
#include <glib.h>
#include <dirent.h>
#include <mono_base/io.h>
#include <mono_base/wapi-private.h>

extern struct _WapiHandleOps _wapi_file_ops;
extern struct _WapiHandleOps _wapi_console_ops;
extern struct _WapiHandleOps _wapi_find_ops;
extern struct _WapiHandleOps _wapi_pipe_ops;

extern void _wapi_file_details (gpointer handle_info);
extern void _wapi_console_details (gpointer handle_info);
extern void _wapi_pipe_details (gpointer handle_info);

/* Currently used for both FILE, CONSOLE and PIPE handle types.  This may
 * have to change in future.
 */
struct _WapiHandle_file
{
	gchar *filename;
	struct _WapiFileShare *share_info;	/* Pointer into shared mem */
	guint32 security_attributes;
	guint32 fileaccess;
	guint32 sharemode;
	guint32 attrs;
};

struct _WapiHandle_find
{
	gchar **namelist;
	gchar *dir_part;
	int num;
	size_t count;
};

#endif /* _WAPI_IO_PRIVATE_H_ */
