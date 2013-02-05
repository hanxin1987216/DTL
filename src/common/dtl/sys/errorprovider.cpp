/***************************************************************************************************
errorprovider.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	异常提供者
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2011-11-28
***************************************************************************************************/

#include "../prec.h"
#include "errorprovider.h"
#include "exception.h"

#include "../util/util.h"

bool inline errorToString (const int& errorId, String & msg)
{
	/*
	map<int, String>  errorMsg;
	vector <String> allLine;
	bool p = getFileContent ("/var/error", allLine);
	if (!p)
		return false;
	vector<String>::iterator it;
	for (it = allLine.begin (); it != allLine.end (); ++it)
	{
		String key;
		String value;
		size_t pos = (*it).find ("=");
		key = (*it).subString (0, pos);
		value = (*it).subString (pos).trim ();
		int tmpId = atoi (key.getCStr());		
		if (errorId == tmpId)
		{
			msg = value;
			break;
		}
	}

	*/
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 系统异常提供者
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

 SystemErrorHandler* SystemErrorHandler::_inst = 0;

 // public static
 SystemErrorHandler*
 SystemErrorHandler::getInstance (void)
 {
	 if (SystemErrorHandler::_inst == 0) {
		 SystemErrorHandler::_inst = new SystemErrorHandler;
	 }
	
	 return SystemErrorHandler::_inst;
 }

 // public static
 void
 SystemErrorHandler::delInstance (void)
 {
	 if (SystemErrorHandler::_inst != 0) {
		 delete SystemErrorHandler::_inst;
		 SystemErrorHandler::_inst = 0;
	 }
 }
		
 // public virtual
 String
 SystemErrorHandler::toString (int errCode) const
 {
	 const String empty;
	 return toString (empty, errCode);
 }

 // public virtual
 String
 SystemErrorHandler::toString (const String& prefix, int errCode) const
 {
	 String errMsg (prefix);	
	 errMsg += strerror(errCode);
	 return errMsg;
 }

 // public virtual
 String
 SystemErrorHandler::getProviderName (void) const
 {
	 static String providerName ("POSIX System");
	 return providerName;
 }



 
//
// The name of DTL Common Module
//
#define DTL_ERROR_PROVIDER_NAME	_T("DTL")



static dtBaseErrorProvider* unknwonErrorProvider = 0;

 //
 // DTL ErrorProvider instanse
 //
static dtBaseErrorProvider* dtlErrorProvider = 0;


IErrorProvider* 
ncGetErrorProvider (const String& providerName)
{
	if (::ncIsDTLErrorProvider (providerName) == true)
		return ::ncGetDTLErrorProvider ();

	// TODO add

	//
	// 没有找到匹配异常，就返回Unkown ErrorProvider
	//
	if (unknwonErrorProvider == 0) {
		unknwonErrorProvider = new dtBaseErrorProvider (providerName);
	}
	
	return unknwonErrorProvider;
}




// DTL
IErrorProvider* 
ncGetDTLErrorProvider (void)
{
	if (dtlErrorProvider == 0) {
		dtlErrorProvider = new dtBaseErrorProvider (DTL_ERROR_PROVIDER_NAME);
	}
	
	return dtlErrorProvider;
}


// DTL
bool
ncIsDTLErrorProvider (const String& providerName)
{
	return (providerName.compareIgnoreCase(DTL_ERROR_PROVIDER_NAME) == 0);
}
