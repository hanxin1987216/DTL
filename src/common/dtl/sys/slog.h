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

#ifndef __DTL_SYS_LOG_H__
#define __DTL_SYS_LOG_H__

#if PRAGMA_ONCE
#pragma once
#endif

/**
 * Defines log type.
 */
enum SysLogType
{
	// Information
	INFO_LOG,

	// Warning
	WARNING_LOG,

	// Error
	ERROR_LOG,
}; // End enum SysLogType


/**
 * Class to write a log on system log.
 */
class DTL_DLLEXPORT SysLog
{
public:
	static SysLog* getInstance (void);
	static void delInstance (void);

public:
	/**
	 * Set the application name which is the logger key in system log.
	 *
	 * @throw ArgumentException if @appName is empty.
	 */
	void setAppName (const String& appName);

	/**
	 * Write a log to system log.
	 */
	void log (SysLogType type, const tchar_t* fmt, ...) NO_THROW;

	/**
	 * Equal to log(type, _T("[%s:%d]:%s"), __FILE__, __LINE__, fmt, ...);
	 */
	void log (const char* filename, 
		 	  int line, 
			  SysLogType type, 
			  const tchar_t* fmt, ...) NO_THROW;

	/**
	 * Equal to log(type, _T("%s(LastError=%d)"), fmt, ..., ::GetLastError());
	 */
	void logLastError (SysLogType type, const tchar_t* fmt, ...) NO_THROW;

	/**
	 * Equal to log(type, _T("[%s:%d]:%s(LastError=%d)"), __FILE__, __LINE__, fmt, ..., ::GetLastError());
	 */
	void logLastError (const char* filename, 
					   int line, 
					   SysLogType type, 
					   const tchar_t* fmt, ...) NO_THROW;

private:
	SysLog (void);
	~SysLog (void);
	
private:
	static SysLog* _inst;
	
#ifdef __WINDOWS__
	class WinSysLogImpl* _impl;
#else
	class UnixSysLogImpl* _impl;
#endif
}; // End class SysLog


#endif // __DTL_SYS_LOG_H__
