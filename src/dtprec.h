/***************************************************************************************************
dtprec.h:	
	Configuration file
	Copyright (c) Datatom Co., Ltd. (2011), All rights reserved

Purpose:
	Precompilation header file for all source.
	
Author:
	han.xin@datatom.com

Creating Time:
	2011-9-7
***************************************************************************************************/

#ifndef __DTPREC_H__
#define __DTPREC_H__

#include <config.h>
#include <string>
#include <list>
#include <iostream>

#ifdef __WINDOWS__

	// MFC does not allow include <windows.h> before using its headers.
	#ifdef __USING_MFC__

		#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

		#include <afxwin.h>
		#include <afxext.h>

		#ifndef _AFX_NO_OLE_SUPPORT
			#include <afxole.h>
			#include <afxodlgs.h>
			#include <afxdisp.h>
		#endif // _AFX_NO_OLE_SUPPORT

		#ifndef _AFX_NO_DB_SUPPORT
			#include <afxdb.h>
		#endif // _AFX_NO_DB_SUPPORT

		#ifndef _AFX_NO_DAO_SUPPORT
			#include <afxdao.h>	
		#endif // _AFX_NO_DAO_SUPPORT

		#include <afxdtctl.h>
			
		#ifndef _AFX_NO_AFXCMN_SUPPORT
			#include <afxcmn.h>
			#include <afxmt.h>
			#include <afxcview.h>
		#endif // _AFX_NO_AFXCMN_SUPPORT

	#endif // __USING_MFC__
#else
#include <errno.h>
#include <sys/stat.h>
#endif	// __WINDOWS__

#ifdef __WINDOWS__

	#ifndef _WINDOWS_
		// System header files.
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#endif

	#if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
	#include <winsock2.h>
	#endif

	#undef WIN32_LEAN_AND_MEAN

	// STL header files.
	#include <vector>
	#include <map>
	#include <set>
	#include <list>
	#include <stack>
	#include <queue>
	#include <algorithm>
	#include <functional>
	#include <memory>
	
//	#include <hash_map>
//	#include <hash_set>

#else // __WINDOWS__
	#include <queue>
	#include <map>
	#include <vector>
	#include <algorithm>
	
#ifdef __LINUX__
//	#include <ext/hash_map>

	//#include <ext/hash_set>
	#define stdext __gnu_cxx
	#define _STDEXT_BEGIN	namespace __gnu_cxx {
	#define _STDEXT_END		}
	using namespace stdext;
	#define _HASH_SEED (size_t)0xdeadbeef

#endif // __LINUX__

#endif // __WINDOWS__

using namespace std;

#include <dlldecl.h>


#ifdef __HPPA__
#define  VOLATILE
#else
#define VOLATILE volatile
#endif

#ifdef __LINUX__
#include <defs.h>
#endif // __LINUX__


#define MAX_PATH 260


#ifndef UINT16
#define UINT16 unsigned short
#endif //UINT16



#ifndef UINT32
#define UINT32 unsigned int
#endif //UINT32


#ifndef UINT64
#define UINT64 unsigned long long
#endif //UINT64





#endif // __DTPREC_H__
