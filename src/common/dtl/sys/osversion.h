/***************************************************************************************************
osversion.h:	
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	This header file contains enum OSVersion that is the version of the operation system. 
		
Author:
	hanxin (han.xin@datatom.com)

Creating Time:
	2012.1.16
***************************************************************************************************/

#ifndef __DTL_SYS_OSVERSION_H__
#define __DTL_SYS_OSVERSION_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * enum #OSVersion is the version of different Operating System.
 */
enum OSVersion 
{
	// Unknown OS version
	OS_UNKNOWN = 0,

	// The OS is Win95
	OS_WIN95 = 0x00000001,

	// 
	OS_WIN95_B,
	
	OS_WIN95_OSR2,		
	
	// The OS is Win98
	OS_WIN98,

	// The OS is Win98 Second
	OS_WIN98_SE,

	// The OS is Win98 Me
	OS_WIN98_ME,

	OS_WINNT, // The following window version always be WINNT family.
	
	OS_WINNT35,
	
	OS_WINNT351,
	
	// The os is WinNT4.0
	OS_WINNT4,

	OS_WINNT4_SP2,
	
	OS_WINNT4_SP3,
	
	OS_WINNT4_SP4,
	
	OS_WINNT4_SP5,
	
	OS_WINNT4_SP6,
	
	// The os is Win2000
	OS_WIN2000,
	
	OS_WIN2000_SP1,
	
	OS_WIN2000_SP2,
	
	OS_WIN2000_SP3,
	
	OS_WIN2000_SP4,

	OS_WIN2000_SVR,

	OS_WIN2000_SVR_SP1,

	OS_WIN2000_SVR_SP2,

	OS_WIN2000_SVR_SP3,

	OS_WIN2000_SVR_SP4,
	
	// The os is WinXP
	OS_WINXP,
	
	OS_WINXP_SP2,
	
	OS_WINXP_64,
	
	// The os is Win2003
	OS_WIN2003,
	
	OS_WIN2003_SP1,
	
	OS_WIN2003_SP2,
	
	// The os is Windows Vista
	OS_WINVISTA,
	
	// The os is Windows 2008
	OS_WIN2008,

	OS_WIN2008_R2, 

	OS_WIN7,
	
	// Windows os mask
	OS_WINDOWSMASK = 0x000000FF,

	// The os is linux
	OS_LINUX = 0x00000100,
	
	// Linux os mask
	OS_LINUXMASK = 0x0000FF00,

	OS_AIX = 0x00010000,

	OS_HPUX = 0x00020000,
	
	OS_SOLARIS = 0x00030000,
	
	// unix os mask
	OS_UNIXMASK = 0x00FF0000,

	// mac os mask
	OS_MACMASK = 0xFF000000,
	
}; // End enum OSVersion

// Helper routines to determine which OSVersion is.
inline bool isWinntFamily (OSVersion os)
{
	return (os > OS_WINNT);
}

inline bool isWin2000Family (OSVersion os)
{
	return ((os >= OS_WIN2000) && (os < OS_WIN7));
}

#endif // __DTL_SYS_OSVERSION_H__
