/***************************************************************************************************
syslog.h:	
	Copyright (c) Datatom Software, Inc.(2004 - 2008), All rights reserved

Purpose:
	This header file defines SysLog class which write log into System Log.

Author:
	hanxin (han.xin@datatom.com)

Creating Time:
	2012-5-1
***************************************************************************************************/

#include "../prec.h"

#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "../sys/exception.h"

#ifndef __WINDOWS__
	#include <syslog.h>
#endif

#include <assert.h>



#include "slog.h"

// public static 
SysLog* SysLog::_inst = 0;

#ifdef __WINDOWS__

class WinSysLogImpl
{
public:
	WinSysLogImpl (const String& appName);
	
	~WinSysLogImpl (void)
	{
		if (_eventHandle != 0)
			::DeregisterEventSource (_eventHandle);
	}
	
	void formatv (SysLogType logType, const tchar_t* fmt, va_list ap);

private:
	HANDLE _eventHandle;
}; // End class WinSysLogImpl

// public ctor
WinSysLogImpl::WinSysLogImpl (const String& appName)
	: _eventHandle (0)
{
	tchar_t msgFileName [AB_MAX_PATH];

	if (!GetModuleFileName (0, msgFileName, AB_MAX_PATH)) {
    	assert (false);
    	return;
    }
    	
	String cflname = Path::combine (Path::getDirectoryName (msgFileName), _T("cfl.dll"));
  	
	unsigned int cflnameLen = ((cflname.getLength () + 1) * sizeof (tchar_t));

	//
	// Information is stored in the registry at a location based on the
	// program name.
	//
	String regkey (_T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"));
	regkey.append (appName);
	
	//
	// Add the event source to the registry. Note that if this fails it
	// is not fatal. The application will still be able to write entries
	// to the event log, they just won't be formatted correctly.
	//
  	HKEY hkey;
  	if (RegCreateKey (HKEY_LOCAL_MACHINE, regkey.getCStr (), &hkey) != ERROR_SUCCESS) {
  		assert (false);
  		// Ignore error instead of throw exception.
  		return; 
  	}
  
  	unsigned int flags = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;
  	RegSetValueEx (hkey,
                   _T("TypesSupported"),
				   0,
				   REG_DWORD,
				   (LPBYTE) &flags,
				   sizeof (unsigned int));
				   
  	RegSetValueEx (hkey,
                   _T("EventMessageFile"),
                   0,
                   REG_SZ,
                   (LPBYTE) cflname.getCStr (),
                   cflnameLen);
  	::RegCloseKey (hkey);

  	// Obtain a handle to the event source.
  	this->_eventHandle = ::RegisterEventSource (0, appName.getCStr ());
}

// public
void 
WinSysLogImpl::formatv (SysLogType logType, 
						   const tchar_t* fmt, 
						   va_list ap)
{
	String msg;
	msg.formatv (fmt, ap);
	
	// Map the ACE log record type to an event log type.
	unsigned short eventType;
	switch (logType)
	{
	case INFORMATION_LOG_TYPE:
		eventType = EVENTLOG_INFORMATION_TYPE;
		break;
	
	case WARNING_LOG_TYPE:
		eventType = EVENTLOG_WARNING_TYPE;
		break;
	
	case ERROR_LOG_TYPE:
	default:
		eventType = EVENTLOG_ERROR_TYPE;
		break;
	}

	//
	// Send the log message to the system event log.
	//
	const tchar_t* msgs [1];
	msgs[0] = msg.getCStr ();

	if (::ReportEvent (_eventHandle,
                       eventType, 
                       0, 
                       0, 
                       0, 
                       1, 
                       0, 
                       msgs, 
                       0) == 0)
		assert (false);  
}
	
#else // __WINDOWS__

class UnixSysLogImpl
{
public:
	UnixSysLogImpl (const String& appName);
	~UnixSysLogImpl (void)
	{
		::closelog ();
	}
	
	void formatv (SysLogType logType, const tchar_t* fmt, va_list ap);
}; // End class UnixSysLogImpl;

// public ctor
UnixSysLogImpl::UnixSysLogImpl (const String& appName)
{
	//
	// Initialize the UNIX syslog facility.  Default the syslog log
	// options LOG_CONS and LOG_PID to be set.  There really should be a
	// logging strategy option to control the syslog log options,
	// however, we'll take the easy way out for now.
	//
	::openlog (appName.getCStr (), LOG_CONS|LOG_PID, LOG_USER);

	//
	// Enable logging of all syslog priorities.  If logging of all
	// priorities is not desired, use the ACE_Log_Msg::priority_mask()
	// method to control the log output sent to the syslog daemon via
	// the log() method, or use the system's syslog.conf file to select
	// desired level of information.
	//
	(void) ::setlogmask (LOG_UPTO (LOG_DEBUG));
}

// public
void 
UnixSysLogImpl::formatv (SysLogType logType, const tchar_t* fmt, va_list ap)
{
	int logPriority;
	switch (logType)
	{
	case INFO_LOG:
  	  	logPriority = LOG_INFO;
    	break;
  
  	case WARNING_LOG:
    	logPriority = LOG_WARNING;
    	break;
  
	case ERROR_LOG:
	default:
    	logPriority = LOG_ERR;
    	break;
  	}
  
	//
	// The UNIX syslog() facility does not support multi-line messages.
	// Break up the message data into separate lines and send each line
	// to the syslog daemon.
	//
	String msg;
	msg.formatv (fmt, ap);
	
	vector<String> lines;
	msg.split (_T("\n"), lines);
	
	vector<String>::iterator itend = lines.end ();
	for (vector<String>::iterator it = lines.begin (); it != itend; ++it) {
		String& line = *it;
  		::syslog (logPriority, line.getCStr ());
#if !defined(__WINDOWS__) && defined(__DEBUG__)
		printf (_T("type:\t%d\nlog:\t%s\n"), logPriority, line.getCStr ());
#endif
    }
}

#endif // __WINDOWS__

// public static 
SysLog* 
SysLog::getInstance (void)
{
	if (SysLog::_inst == 0) 
		SysLog::_inst = new SysLog;
			
	return SysLog::_inst;
}

// public static
void 
SysLog::delInstance (void)
{
	if (SysLog::_inst != 0) {
		delete SysLog::_inst;
		SysLog::_inst = 0;
	}
}

// private ctor
SysLog::SysLog (void)
	: _impl (0)
{
	setAppName (_T("Unknown Source"));
}

// private dtor
SysLog::~SysLog (void)
{
	delete _impl;
}
		
// public 
void 
SysLog::setAppName (const String& appName)
{
	if (appName.isEmpty () == true)
		THROW (_T("IDS_EMPTY_STRING"));
		
	delete _impl;
#ifdef __WINDOWS__
	_impl = new WinSysLogImpl (appName);
#else
	_impl= new UnixSysLogImpl (appName);
#endif
}

// public
void 
SysLog::log (SysLogType type, const tchar_t* fmt, ...) NO_THROW
{
	try {
		va_list ap;
	    va_start (ap, fmt);
	
		_impl->formatv (type, fmt, ap);
	
	    va_end (ap);    
	}
	catch (Exception&) {
		assert (false);
	}
}
	
// public
void 
SysLog::log (const char* filename, 
				int line, 
				SysLogType type, 
				const tchar_t* fmt, ...) NO_THROW
{
	try {
#ifdef __WINDOWS__	
		String ufilename (filename);
		String fullfmt;
		fullfmt.format (_T("[%s:%d]:%s"), ufilename.getCStr (), line, fmt);
#else
		String fullfmt;
		fullfmt.format (_T("[%s:%d]:%s"), filename, line, fmt);
#endif

		va_list ap;
		va_start (ap, fmt);
		
		_impl->formatv (type, fullfmt.getCStr (), ap);
		
		va_end (ap);
	}
	catch (Exception&) {
		assert (false);
	}
}
	
// public static 
void 
SysLog::logLastError (SysLogType type, const tchar_t* fmt, ...) NO_THROW
{
	try {
		String fullfmt;
		fullfmt.format (_T("%s(LastError=%d)"), fmt, ::GetLastError ());
	
		va_list ap;
		va_start (ap, fmt);
		
		_impl->formatv (type, fullfmt.getCStr (), ap);
		
		va_end (ap);
	}
	catch (Exception&) {
		assert (false);
	}
}
	
// public static 
void 
SysLog::logLastError (const char* filename, 
						 int line, 
						 SysLogType type, 
						 const tchar_t* fmt, ...) NO_THROW
{
	try {
#ifdef __WINDOWS__	
		String ufilename (filename);
#endif

		String fullfmt;
		fullfmt.format (_T("[%s:%d]:%s(LastError=%d)"), 
#ifdef __WINDOWS__
						ufilename.getCStr (), 
#else	
						filename,
#endif	
						line, 
						fmt, 
						::GetLastError ());

		va_list ap;
		va_start (ap, fmt);
		
		_impl->formatv (type, fullfmt.getCStr (), ap);
		
		va_end (ap);
	}
	catch (Exception&) {
		assert (false);
	}
}

