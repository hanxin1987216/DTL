/*
 * mono_base.h: Include the right files depending on platform.  This
 * file is the only entry point into the mono_base library.
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _MONO_IOLAYER_IOLAYER_H_
#define _MONO_IOLAYER_IOLAYER_H_

#if defined(__WINDOWS__)
/* Native win32 */
#define UNICODE
#define _UNICODE
#define __USE_W32_SOCKETS
#include <winsock2.h>
#include <windows.h>
#include <winbase.h>
#include <ws2tcpip.h>
#include <psapi.h>
#include <shlobj.h>
#else	/* EVERYONE ELSE */
#include "mono_base/wapi.h"
#include "mono_base/uglify.h"
#endif /* PLATFORM_WIN32 */

#endif /* _MONO_IOLAYER_IOLAYER_H_ */
