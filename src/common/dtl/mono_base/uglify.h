/*
 * uglify.h:  Optional header to provide the nasty w32 typedefs
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_UGLIFY_H_
#define _WAPI_UGLIFY_H_

/* Include this file if you insist on using the nasty Win32 typedefs */

#include <stdlib.h>
#include "./wapi.h"

#ifdef WapiSecurityAttributes
typedef WapiSecurityAttributes SECURITY_ATTRIBUTES;
typedef WapiSecurityAttributes *LPSECURITY_ATTRIBUTES;
#endif

#ifndef PSECURITY_DESCRIPTOR
typedef void* PSECURITY_DESCRIPTOR;
#endif

typedef WapiOverlapped *LPOVERLAPPED;
typedef WapiOverlappedCB LPOVERLAPPED_COMPLETION_ROUTINE;
typedef WapiThreadStart LPTHREAD_START_ROUTINE;
typedef WapiCriticalSection CRITICAL_SECTION;
typedef WapiCriticalSection *LPCRITICAL_SECTION;
typedef WapiFileTime FILETIME;
typedef WapiFileTime *LPFILETIME;
typedef WapiSystemTime SYSTEMTIME;
typedef WapiSystemTime *LPSYSTEMTIME;
typedef WapiLargeInteger LARGE_INTEGER;
typedef WapiLargeInteger *PLARGE_INTEGER;
typedef WapiLargeInteger ULARGE_INTEGER;

typedef WapiFindData WIN32_FIND_DATA;
typedef WapiFindData *LPWIN32_FIND_DATA;
typedef WapiFileAttributesData WIN32_FILE_ATTRIBUTE_DATA;
typedef WapiGetFileExInfoLevels GET_FILEEX_INFO_LEVELS;
typedef WapiStartupInfo STARTUPINFO;
typedef WapiStartupInfo *LPSTARTUPINFO;
typedef WapiProcessInformation PROCESS_INFORMATION;
typedef WapiFixedFileInfo VS_FIXEDFILEINFO;
typedef WapiApcProc PAPCFUNC;
typedef WapiShellExecuteInfo SHELLEXECUTEINFO;
typedef WapiShellExecuteInfo *LPSHELLEXECUTEINFO;

#define CONST const
#define VOID void

#define IN
#define OUT
#define WINAPI

#endif /* _WAPI_UGLIFY_H_ */
