/***************************************************************************************************
dlldecl.h:	
	Public Header
	Copyright (c) Datatom Co., Ltd. (2011), All rights reserved

Purpose:
	Defines DLL import and export declaration macro for all modules.
	
Author:
	han.xin@datatom.com

Creating Time:
	2011-9-7
***************************************************************************************************/

#ifndef __DLLDECL_H__
#define __DLLDECL_H__

#include <config.h>

#if PRAGMA_ONCE
#	pragma once
#endif

#if defined(__VISUALC__)
#	define DT_EXPORT __declspec(dllexport)
#	define DT_IMPORT __declspec(dllimport)
#else 
#	define DT_EXPORT
#	define DT_IMPORT
#endif //

#endif // __DLLDECL_H__
