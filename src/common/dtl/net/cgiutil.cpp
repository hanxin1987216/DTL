/***************************************************************************************************
util.h:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	util for cgi
		
Author:
	Lyre
	
Creating Time:
	2012-03-31
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "./mono_base/uglify.h"
#include "../sys/exception.h"
#include "../lang/string.h"
#include "../lang/int64.h"
#include "../lang/int.h"
#include "../lang/uint.h"
#include "../util/resreader.h"

#include "cgiexcept.h"
#include "jsontextwriter.h"

#include "cgiutil.h"


//
// 读取字符串资源
//
extern IResourceReader* cgiResLoader;
#define LOAD_STRING(IDS)				\
		cgiResLoader->loadString (IDS)


static void dtWriteExptError (Exception& e, JsonTextWriter *writer);
////////////////////////////////////////////////////////////////////////////////////////////////
//
// 公共函数
//
inline String genResourceName (const String& resName)
{
	String ret = resName;
	ret.append (".do");
	return ret;
}

IResourceReader *dtGetResLoader (IResourceReader *resLoader, const String &libResFile)
{

	#ifndef __WINDOWS__
		_wapi_init_handles ();
	#endif


	if (resLoader == NULL)
	{
		try {
			String resName = genResourceName (libResFile);
			resLoader = new DoResourceReader (resName, true);
		}
		catch (Exception& e) {
			CGI_THROW_BY_CAUSE(_T("加载资源文件失败"), e);
		}
	}
	
	return resLoader;
}

IResourceReader *dtGetCgiResLoader (const String &libResFile)
{
	return dtGetResLoader (cgiResLoader, libResFile);;
}

void dtWriteExptError (Exception& e, JsonTextWriter *writer)
{

	writer->StartObject ();
		writer->WriteElement ("code", CGI_RET_CODE_EXCPTION);
		
		writer->StartObject (_T("result"));
		writer->WriteElement (_T("content"), e.toFullString ());
		writer->EndObject ();
		
	writer->EndObject ();
	
	
}

void dtOutputExptError (Exception& e)
{	
	String msg = "";
	JsonTextWriter writer;
	dtWriteExptError (e, &writer);
	msg = writer.getJsonStr();
	cout<<msg.getCStr ()<<endl;
}


void dtOutputInterfaceList (vector <dtCmdFunInfo> &cmds, JsonTextWriter *writer)
{
	writer->StartArray ();
	
	vector <dtCmdFunInfo>::iterator it, itend = cmds.end ();
	for (it = cmds.begin (); it != itend; ++it) {
		writer->StartObject ();
		writer->WriteElement ("interface", it->cmd);
		writer->StartObject ("params");
		for (size_t i = 0; i < it->funInfo.params.size (); ++i) {
			writer->WriteElement (it->funInfo.params[i].type.getCStr (), it->funInfo.params[i].name);
		}
		writer->EndObject ();
		writer->EndObject ();
	}
	
	writer->EndArray ();
}