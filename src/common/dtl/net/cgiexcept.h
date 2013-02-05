/***************************************************************************************************
exception.h:
	Copyright (c) Datatom, Inc.(2011 - 2012), All rights reserved.

Purpose:
	cgi exception
		
Author:
	Lyre
	
Creating Time:
	2012-04-26
***************************************************************************************************/
#ifndef DATRIX_APPS_CGI_CGIBASE_EXCEPTION_H_
#define DATRIX_APPS_CGI_CGIBASE_EXCEPTION_H_

#include <dtprec.h>
class Exception;

IErrorProvider* dtGetCGIErrorProvider (void);

#define CGI_THROW(msg)	\
	throw dtCGIException (msg, __FILE__, __LINE__, Exception::NO_MAPPED_ERROR_ID, ::dtGetCGIErrorProvider ());

#define CGI_THROW_ID(msg, errorId)	\
	throw dtCGIException (msg, __FILE__, __LINE__, errorId, ::dtGetCGIErrorProvider ());

#define CGI_THROW_BY_CAUSE(msg, e)	\
	throw dtCGIException (msg, __FILE__, __LINE__, e, e.getErrorId (), ::dtGetCGIErrorProvider ());

#define CGI_THROW_BY_CAUSE_AND_ID(msg, e, errorId)	\
	throw dtCGIException (msg, __FILE__, __LINE__, e, errorId, ::dtGetCGIErrorProvider ());


class dtCGIException : public Exception
{
public:
	dtCGIException (void) ;	

	dtCGIException (const String& msg,
				const String& file,
				const int& line,
				int errId = Exception::NO_MAPPED_ERROR_ID,
				IErrorProvider* errProvider = 0);
						
	dtCGIException (const String& msg, 
				const String& file,
				const int& line,
				const Exception& exp,  
				int errId = Exception::NO_MAPPED_ERROR_ID,
				IErrorProvider* errProvider = 0);
			   
};

#endif // DATRIX_APPS_CGI_CGIBASE_EXCEPTION_H_
