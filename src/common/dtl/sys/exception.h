/***************************************************************************************************
exception.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	异常
	
Author:
	zhangfei
	
Creating Time:
	2011-11-28
***************************************************************************************************/

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include <errorid.h>
#include "errorprovider.h"


/**
*  常用宏
**/
#define THROW(msg)	\
	throw Exception (msg, __FILE__, __LINE__, Exception::NO_MAPPED_ERROR_ID, ::ncGetDTLErrorProvider ());

#define THROW_ID(msg, errorId)	\
	throw Exception (msg, __FILE__, __LINE__, errorId, ::ncGetDTLErrorProvider ());

#define THROW_BY_HANDLER(msg, errorId, handler)	\
	throw Exception (msg, __FILE__, __LINE__, errorId, handler);


#define THROW_BY_CAUSE(msg, e, errorId)	\
	throw Exception (msg, __FILE__, __LINE__, e, errorId, ::ncGetDTLErrorProvider ());




/**
*
* Class of Exception
**/
	
class DTL_DLLEXPORT Exception 
{
	
public:		

	Exception (void) ;	

	explicit Exception (const String& msg, 
						const String& file,
						const int& line,
						int errId = Exception::NO_MAPPED_ERROR_ID,
						IErrorProvider* errProvider = 0);


	Exception (const String& msg, 
    		   const String& file,
			   const int& line, 
			   const Exception& exp,  
			   int errId = Exception::NO_MAPPED_ERROR_ID,
			   IErrorProvider* errProvider = 0);
	

	virtual ~Exception (void);

	Exception(const Exception& exp) ;

	Exception& operator= (const Exception& exp);

// Virtual methods
public:

	virtual String getMessage (void) const;
		
	virtual String toString (void) const;

	virtual String getAdditionalInfo (void) const;
	
	virtual String toFullString (void) const;
	
	virtual const Exception* clone (void) const;

	virtual const Exception* getBaseException (void) const;
		
	int getErrorId (void) const
	{
		return _errId;
	}
	

	IErrorProvider* getErrorProvider (void)
	{
		return _errProvider;
	}
	

	void setErrorProvider (IErrorProvider* errProvider)
	{
		_errProvider = errProvider;
	}
		
	
	const Exception* getCause (void) const
	{
		return _causeExp;
	}
		
protected:
	int						_errId;
	String					_file;
	int						_line;
	String 				 	_msg;
	const Exception* 		_causeExp;
	IErrorProvider* 	 	_errProvider;
		
public:
	static const int NO_MAPPED_ERROR_ID;
	
}; 

#endif //__EXCEPTION_H__



