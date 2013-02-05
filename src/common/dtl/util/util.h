/****************************************************************************************************
util.h
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	util
	
Auther:
	han.xin@datatom.com

Created Time:
	2011-10-08
****************************************************************************************************/
#ifndef __DTL_UTIL_H__
#define __DTL_UTIL_H__

#if AB_PRAGMA_ONCE
	#pragma once
#endif


#include "../lang/string.h"

/**
* ��ȡ����mac��ַ
*/
DTL_DLLEXPORT String generateNetworkMAC (void);

/**
* ��ȡCPU��Ϣ
*/ 
DTL_DLLEXPORT String generateCPUVendorInfo (void);

/**
* ���ɻ�����
*/
DTL_DLLEXPORT String genMachineCode(void);

#endif //__DTL_UTIL_H__
