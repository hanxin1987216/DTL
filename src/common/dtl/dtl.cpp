/***************************************************************************************************
dtl.cpp:	
	Public Header
	Copyright (c) Datatom Software, Inc.(2004 - 2008), All rights reserved

Purpose:
	dtl 
Author:
	韩欣

Creating Time:
	2011-12-2
***************************************************************************************************/
#include "prec.h"
#include "./mono_base/uglify.h"

#include "./lang/string.h"
#include "./lang/int.h"
#include "./sys/exception.h"
#include "./sys/locale.h"
#include "./util/resreader.h"
#include "./log/log.h"
#include "version.h"


#ifdef __LINUX__
	#include <memory.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <signal.h>
	#include <execinfo.h>
#endif


IResourceReader* dtlResReader = 0;


void InitDTLibrary (void)
{		
#ifndef __WINDOWS__
	_wapi_init_handles ();
#endif

	
	// TODO:  init dtlResReader
	if (dtlResReader != 0)
		return;

	if (dtlResReader == 0) {		
	
		String resName (_T("dtl.do"));

		try {
			dtlResReader = new DoResourceReader (resName, true);
		}
		catch (Exception& e) {
			//
			// 转为 SharedLibraryException 异常。
			//
			// TODO 
		}
	}
	
	// init TraceLog console
	TraceLog::createConsoleLogger ();

}

String dtGetVersion (void)
{
	String ret;
	ret.format ("%d.%d.%d", DTL_MAJOR_VERSION, DTL_MINOR_VERSION, DTL_PATCH_VERSION);
	return ret;
}


int dtGetMajorVersion (const String& ver)
{
	vector<String> subs;
	ver.split (".", subs);

	return Int::getValue(subs[0]);
}

int dtGetMinorVersion (const String& ver)
{
	vector<String> subs;
	ver.split (".", subs);

	return  Int::getValue(subs[1]);
}

int dtGetPatchVersion (const String& ver)
{
	vector<String> subs;
	ver.split (".", subs);

	return Int::getValue (subs[2]);
}

//
// 比较版本大小，用于兼容性检查(只比较Major和Minor version)
// 若ver1比ver2旧，则返回 -1
// 若ver1与ver2相同，则返回 0
// 若ver1比ver2新，则返回 1
//
int dtCompairVersion (const String & ver1, 
							    const String& ver2,
							    bool needCompairPatchVersion)
{
	//
	// 先比较主版本
	//
	if (dtGetMajorVersion (ver1) < dtGetMajorVersion (ver2))
		return -1;

	if (dtGetMajorVersion (ver1) > dtGetMajorVersion (ver2))
		return 1;

	//
	// 主版本相同，则比较次版本
	//
	if (dtGetMinorVersion (ver1) < dtGetMinorVersion (ver2))
		return -1;

	if (dtGetMinorVersion (ver1) > dtGetMinorVersion (ver2))
		return 1;

	if (needCompairPatchVersion == true) {
		//
		// 主版本和次版本都相同，则比较补丁版本
		//
		if (dtGetPatchVersion (ver1) < dtGetPatchVersion (ver2))
			return -1;

		if (dtGetPatchVersion (ver1) > dtGetPatchVersion (ver2))
			return 1;
	}

	//
	// 版本相同
	//
	return 0;
}


	
