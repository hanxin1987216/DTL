/***************************************************************************************************
exception.cpp:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	cgi exception
		
Author:
	Lyre
	
Creating Time:
	2012-04-26
***************************************************************************************************/
#include "../prec.h"
#include "../sys/exception.h"
#include "../lang/string.h"
#include "../lang/int64.h"

#include "cgiexcept.h"
//
// The name of CGI Common Module
//
#define CGI_ERROR_PROVIDER_NAME	_T("CGI")

//
// CGI ErrorProvider instanse
//
static dtBaseErrorProvider* cgiErrorProvider = 0;


IErrorProvider*
dtGetCGIErrorProvider (void)
{
	if (cgiErrorProvider == 0) {
		cgiErrorProvider = new dtBaseErrorProvider (CGI_ERROR_PROVIDER_NAME);
	}
	
	return cgiErrorProvider;
}

///////////////////////////////////////////////////////////////////////////
// class dtCGIException
///////////////////////////////////////////////////////////////////////////
dtCGIException::dtCGIException (void)
	: Exception (_T("cgi exception was thrown."),  __FILE__, __LINE__)
{
}

dtCGIException::dtCGIException (const String& msg,
					const String& file,
					const int& line,
					int errId,
					IErrorProvider* errProvider)
	: Exception (msg,  file, line, errId, errProvider)
{
	if (errProvider != 0)
		setErrorProvider (errProvider);
}


dtCGIException::dtCGIException (const String& msg, 
			const String& file,
			const int& line,
			const Exception& exp,  
			int errId,
			IErrorProvider* errProvider)
	: Exception (msg, file, line, exp, errId, errProvider)
{
	if (errProvider != 0)
		setErrorProvider (errProvider);
}