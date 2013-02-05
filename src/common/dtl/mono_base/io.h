/*
 * io.h: File, console and find handles
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_IO_H_
#define _WAPI_IO_H_

#include <stdlib.h>

#include "./wapi.h"
#include "./timefuncs.h"

G_BEGIN_DECLS

typedef struct _WapiSecurityAttributes WapiSecurityAttributes;

struct _WapiSecurityAttributes 
{
	guint32 nLength;
	gpointer lpSecurityDescriptor;
	gboolean bInheritHandle;
};

typedef struct _WapiOverlapped WapiOverlapped;

struct _WapiOverlapped
{
	guint32 Internal;
	guint32 InternalHigh;
	guint32 Offset;
	guint32 OffsetHigh;
	gpointer hEvent;
	gpointer handle1;
	gpointer handle2;
};

typedef void (*WapiOverlappedCB) (guint32 error, guint32 numbytes,
				  WapiOverlapped *overlapped);
#define MAX_PATH	260
#define GENERIC_READ	0x80000000
#define GENERIC_WRITE	0x40000000
#define GENERIC_EXECUTE	0x20000000
#define GENERIC_ALL	0x10000000

#define FILE_SHARE_READ		0x00000001
#define FILE_SHARE_WRITE	0x00000002
#define FILE_SHARE_DELETE	0x00000004

#define CREATE_NEW		1
#define CREATE_ALWAYS		2
#define OPEN_EXISTING		3
#define OPEN_ALWAYS		4
#define TRUNCATE_EXISTING	5


#define FILE_ATTRIBUTE_READONLY			0x00000001
#define FILE_ATTRIBUTE_HIDDEN			0x00000002
#define FILE_ATTRIBUTE_SYSTEM			0x00000004
#define FILE_ATTRIBUTE_DIRECTORY		0x00000010
#define FILE_ATTRIBUTE_ARCHIVE			0x00000020
#define FILE_ATTRIBUTE_ENCRYPTED		0x00000040
#define FILE_ATTRIBUTE_NORMAL			0x00000080
#define FILE_ATTRIBUTE_TEMPORARY		0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE		0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT		0x00000400
#define FILE_ATTRIBUTE_COMPRESSED		0x00000800
#define FILE_ATTRIBUTE_OFFLINE			0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED	0x00002000
#define FILE_FLAG_OPEN_NO_RECALL		0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT		0x00200000

#define FILE_ATTRIBUTE_SYMBOLIC_LINK	0x01000000
#define FILE_ATTRIBUTE_CHAR				0x02000000
#define FILE_ATTRIBUTE_BLOCK			0x04000000
#define FILE_ATTRIBUTE_FIFO				0x08000000
#define FILE_ATTRIBUTE_SOCK				0x10000000

#define FILE_ATTRIBUTE_DEV_FILE			(FILE_ATTRIBUTE_CHAR | FILE_ATTRIBUTE_BLOCK | FILE_ATTRIBUTE_FIFO | FILE_ATTRIBUTE_SOCK)

/*#define FILE_FLAG_POSIX_SEMANTICS		0x01000000
#define FILE_FLAG_BACKUP_SEMANTICS		0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE		0x04000000
#define FILE_FLAG_SEQUENTIAL_SCAN		0x08000000
#define FILE_FLAG_RANDOM_ACCESS			0x10000000
#define FILE_FLAG_NO_BUFFERING			0x20000000
#define FILE_FLAG_OVERLAPPED			0x40000000
#define FILE_FLAG_WRITE_THROUGH			0x80000000*/

typedef enum {
	STD_INPUT_HANDLE=-10,
	STD_OUTPUT_HANDLE=-11,
	STD_ERROR_HANDLE=-12
} WapiStdHandle;

typedef enum {
	FILE_BEGIN=0,
	FILE_CURRENT=1,
	FILE_END=2
} WapiSeekMethod;

typedef enum {
	FILE_TYPE_UNKNOWN=0x0000,
	FILE_TYPE_DISK=0x0001,
	FILE_TYPE_CHAR=0x0002,
	FILE_TYPE_PIPE=0x0003,
	FILE_TYPE_REMOTE=0x8000
} WapiFileType;

typedef enum {
	GetFileExInfoStandard=0x0000,
	GetFileExMaxInfoLevel=0x0001
} WapiGetFileExInfoLevels;

typedef struct 
{
	guint16 wYear;
	guint16 wMonth;
	guint16 wDayOfWeek;
	guint16 wDay;
	guint16 wHour;
	guint16 wMinute;
	guint16 wSecond;
	guint16 wMilliseconds;
} WapiSystemTime;

typedef struct
{
	guint32 dwFileAttributes;
	WapiFileTime ftCreationTime;
	WapiFileTime ftLastAccessTime;
	WapiFileTime ftLastWriteTime;
	guint32 nFileSizeHigh;
	guint32 nFileSizeLow;
	guint32 dwReserved0;
	guint32 dwReserved1;
	gchar cFileName [MAX_PATH];
	gchar cAlternateFileName [14];
} WapiFindData;

typedef struct
{
	guint32 dwFileAttributes;
	WapiFileTime ftCreationTime;
	WapiFileTime ftLastAccessTime;
	WapiFileTime ftLastWriteTime;
	guint32 nFileSizeHigh;
	guint32 nFileSizeLow;
} WapiFileAttributesData;

typedef struct
{
	guint32 dwFileAttributes;
	WapiFileTime ftCreationTime;
	WapiFileTime ftLastAccessTime;
	WapiFileTime ftLastWriteTime;
	guint32 dwVolumeSerialNumber;
	guint32 nFileSizeHigh;
	guint32 nFileSizeLow;
	guint32 nNumberOfLinks;
	guint32 nFileIndexHigh;
	guint32 nFileIndexLow;
	mode_t st_mode;
	uid_t st_uid;
	gid_t st_gid;
	gchar cTargetFileName [MAX_PATH];
} WapiFileAttributesDataEx;

typedef WapiFileAttributesDataEx BY_HANDLE_FILE_INFORMATION;

#define INVALID_SET_FILE_POINTER ((guint32)-1)
#define INVALID_FILE_SIZE ((guint32)0xFFFFFFFF)
#define INVALID_FILE_ATTRIBUTES ((guint32)-1)

extern gpointer CreateFile(const gchar *name, guint32 fileaccess,
			   guint32 sharemode,
			   WapiSecurityAttributes *security,
			   guint32 createmode,
			   guint32 attrs, gpointer tmplate);
extern gboolean DeleteFile(const gchar *name);
extern gpointer GetStdHandle(WapiStdHandle stdhandle);
extern gboolean ReadFile(gpointer handle, gpointer buffer, guint32 numbytes,
			 guint32 *bytesread, WapiOverlapped *overlapped);
extern gboolean WriteFile(gpointer handle, gconstpointer buffer,
			  guint32 numbytes, guint32 *byteswritten,
			  WapiOverlapped *overlapped);
extern gboolean FlushFileBuffers(gpointer handle);
extern gboolean SetEndOfFile(gpointer handle);
extern guint32 SetFilePointer(gpointer handle, gint32 movedistance,
			      gint32 *highmovedistance, WapiSeekMethod method);
extern WapiFileType GetFileType(gpointer handle);
extern guint32 GetFileSize(gpointer handle, guint32 *highsize);
extern gboolean GetFileTime(gpointer handle, WapiFileTime *create_time,
			    WapiFileTime *last_access,
			    WapiFileTime *last_write);
extern gboolean SetFileTime(gpointer handle, const WapiFileTime *create_time,
			    const WapiFileTime *last_access,
			    const WapiFileTime *last_write);
extern gboolean FileTimeToSystemTime(const WapiFileTime *file_time,
				     WapiSystemTime *system_time);
extern gpointer FindFirstFile (const gchar *pattern,
			       WapiFindData *find_data);
extern gboolean FindNextFile (gpointer handle, WapiFindData *find_data);
extern gboolean FindClose (gpointer handle);
extern gboolean CreateDirectory (const gchar *name,
				 WapiSecurityAttributes *security);
extern gboolean RemoveDirectory (const gchar *name);
extern gboolean MoveFile (const gchar *name, const gchar *dest_name);
extern gboolean CopyFile (const gchar *name, const gchar *dest_name,
			  gboolean fail_if_exists);
extern gboolean GetFileInformationByHandle (gpointer handle, gpointer fileInfo);
extern gboolean GetFileInformationByHandleEx (gpointer handle, gpointer fileInfo);
extern guint32 GetFileAttributes (const gchar *name);
extern gboolean GetFileAttributesEx (const gchar *name,
				     WapiGetFileExInfoLevels level,
				     gpointer info);
extern gboolean SetFileAttributes (const gchar *name, guint32 attrs);
extern guint32 GetCurrentDirectory (guint32 length, gchar *buffer);
extern gboolean SetCurrentDirectory (const gchar *path);
extern gboolean CreatePipe (gpointer *readpipe, gpointer *writepipe,
			    WapiSecurityAttributes *security, guint32 size);
extern guint32 GetTempPath (guint32 len, gchar *buf);
extern gint32 GetLogicalDriveStrings (guint32 len, gchar *buf);
extern gboolean SetFileAttributesEx (const gchar *name, 
									 const BY_HANDLE_FILE_INFORMATION * pFileInfo);
G_END_DECLS

#endif /* _WAPI_IO_H_ */
