/***************************************************************************************************
version.h:	
	Public Header
	Copyright (c) Datatom Software, Inc.(2004 - 2008), All rights reserved

Purpose:
	dtl version head file
	
Author:
	����

Creating Time:
	2011-12-2
***************************************************************************************************/

#ifndef __DTL_VERSION_H__
#define __DTL_VERSION_H__

//
// DTL version: major.minor.patch (in one 32-bit integer)
//              32-24.24-12.12-0
//
// Major version: Max value is 255. The DTL make a VERY important 
//  			  changes, the lower version never compatible with higher
//				  version. And the higher version maybe not compatible with
//				  lower version.
//
// Minor version: Max value is 4095. The DTL make some new changes on structure.
//				  The lower version never compatible with higher version. 
//				  And the higher version must compatible with the lower version.
//
// Patch version: Max value is 4095. The DTL do some minor changes. 
//				  It is compatible between lower version and higher version. 
//				  Includes downward and upward compatibility.
//
#define DTL_MAJOR_VERSION		1

#define DTL_MINOR_VERSION		1

#define DTL_PATCH_VERSION		0

DTL_DLLEXPORT String dtGetVersion (void);
DTL_DLLEXPORT int dtGetMajorVersion (const String& ver);
DTL_DLLEXPORT int dtGetMinorVersion (const String& ver);
DTL_DLLEXPORT int dtGetPatchVersion (const String& ver);

//
// �Ƚϰ汾��С�����ڼ����Լ��(ֻ�Ƚ�Major��Minor version)
// ��ver1��ver2�ɣ��򷵻� -1
// ��ver1��ver2��ͬ���򷵻� 0
// ��ver1��ver2�£��򷵻� 1
//
DTL_DLLEXPORT int dtCompairVersion (const String& ver1, 
									const String& ver2,
									bool needCompairPatchVersion);




#endif // __DTL_VERSION_H__
