/****************************************************************************************************
prec.h
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	DTL prec

Auther:
	hanxin (han.xin@datatom.com)

Created Time:
	2011-10-13
****************************************************************************************************/
#ifndef __DTL_PREC_H__
#define __DTL_PREC_H__

#include <dtprec.h>


#ifdef __MAKE_DTL_DLL__

#	define DTL_CDLLEXPORT			extern "C" DT_EXPORT
#	define DTL_DLLEXPORT			DT_EXPORT
#	define DTL_DLLEXPORT_DATA(type) DT_EXPORT type
#	define DTL_DLLEXPORT_CTORFN

#elif defined(__USE_DTL_DLL__)

#	define DTL_CDLLEXPORT			extern "C" DT_IMPORT
#	define DTL_DLLEXPORT			DT_IMPORT
#	define DTL_DLLEXPORT_DATA(type) DT_IMPORT type
#	define DTL_DLLEXPORT_CTORFN

#else // not make nor useDLL

#	define DTL_CDLLEXPORT			extern "C"
#	define DTL_DLLEXPORT
#	define DTL_DLLEXPORT_DATA(type) type
#	define DTL_DLLEXPORT_CTORFN

#endif /* __MAKE_DTL_DLL__ */

#endif //__DTL_PREC_H__
