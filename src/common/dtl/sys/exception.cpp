/***************************************************************************************************
exception.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	异常
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2011-11-28
***************************************************************************************************/

#include "../prec.h"
#include "../lang/int.h"
#include "exception.h"

const int Exception::NO_MAPPED_ERROR_ID = (int)0x00000000;

Exception::Exception (void) 
	: _errId (Exception::NO_MAPPED_ERROR_ID)
	, _file ()
	, _line (0)
	, _msg ()
	, _causeExp (0)
	, _errProvider (0)
{
	// Do nothing
}

Exception::Exception (const String& msg, 
					  const String& file,
			          const int& line, 
					  int errId /* = Exception::NO_MAPPED_ERROR_ID */,
					  IErrorProvider* errProvider /*= 0*/) 
	: _errId (errId)
	, _file (file)
	, _line (line)
	, _msg (msg)
	, _causeExp (0)
	, _errProvider (errProvider)
{

}

Exception::Exception (const String& msg,  
					  const String& file,
			          const int& line, 
					  const Exception& exp,
					  int errId /*= Exception::NO_MAPPED_ERROR_ID*/,
				   	  IErrorProvider* errProvider /*= 0*/
					  ) 
	: _errId (errId)
	, _file (file)
	, _line (line)
	, _msg (msg)
	, _causeExp (exp.clone ())
	, _errProvider (errProvider)	
{

}

Exception::~Exception (void)
{
	if (_causeExp != 0) {
		delete _causeExp;
	}
}

Exception::Exception (const Exception& exp) 
	: _errId (exp._errId)
	, _file (exp._file)
	, _line (exp._line)
	, _msg (exp._msg)
	, _causeExp (0)
	, _errProvider (exp._errProvider)
{
	if (exp._causeExp != 0)
		_causeExp = exp._causeExp->clone ();
}

Exception& 
Exception::operator= (const Exception& exp) 
{
	_msg 		 = exp._msg;
	_errId		 = exp._errId;
	_errProvider = exp._errProvider;	
	_file 		 = exp._file;
	_line 		 = exp._line;
	if (exp._causeExp != 0)
		_causeExp = exp._causeExp->clone ();
		
	return *this;
}

// public virtual 
String 
Exception::getMessage (void) const
{
	return _msg;
}

const Exception* 
Exception::clone (void) const
{ 
	Exception* exptObj = new Exception;
	exptObj->_msg = _msg;
	exptObj->_errId = _errId;
	exptObj->_errProvider = _errProvider;
	exptObj->_file = _file;
	exptObj->_line = _line;
	if (_causeExp != 0)
		exptObj->_causeExp = _causeExp->clone ();
	return exptObj;
}

// public virtual
String 
Exception::toString (void) const
{
	String msg = getMessage ();

	String providerName;
	if (_errProvider == 0) {
		providerName = _T("Unknown Provider");
	}
	else {
		providerName = _errProvider->getProviderName ();
	}

	String str = "Error:";
	str += msg;
	if (getErrorId () != NO_MAPPED_ERROR_ID) {
		str += ", ErrorCode:";
		str += Int::toString (_errId);
	}

	str += ", Error Provider:";
	str += providerName;
	str += ", File:";
	str += _file;
	str += ", Line:";
	str += Int::toString (_line);

	return str;
}

// public virtual 
String 
Exception::getAdditionalInfo (void) const 
{
	String additionalInfo;
	if (_causeExp != 0) {
		additionalInfo = _causeExp->toString ();
		if (_causeExp->getAdditionalInfo ().isEmpty () == false) {
			String innerMsg = _causeExp->getAdditionalInfo ();
			additionalInfo += innerMsg;
		}
	}
	
	return additionalInfo;	
}

// public virtual 
String 
Exception::toFullString (void) const
{
	String msg = toString ();

	if (_causeExp != 0) {
		String additionalInfo = "Additional Info:";
		additionalInfo += getAdditionalInfo ();
		msg += additionalInfo;
	}

	return msg;
}

// public virtual 
const Exception* 
Exception::getBaseException (void) const
{
	const Exception* inner = _causeExp;
	
	// Get the root exception.	
	while (inner != 0) {
		if (inner->getCause () != 0)
			inner = inner->getCause ();
		else
			return inner;
	}

	return this;
}


