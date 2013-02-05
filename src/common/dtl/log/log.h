/***************************************************************************************************
log.h:	
	C++ Foundation Library header files
	Copyright (c) DateTome Software Inc.(2012)

Purpose:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-02-07
	
	This library is free software; you can redistribute it and/or modify it under the terms of the 
 	GNU Lesser General Public License as published by the Free Software Foundation; either version 
 	2 of the License, or (at your option) any later version.  	
***************************************************************************************************/
#ifndef _DTL_LOG_H_
#define _DTL_LOG_H_

#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/Message.h>

//
// define color
#define DTL_RED_COLOR_HEAD              "\033[0;31m"
#define DTL_YELLOW_COLOR_HEAD           "\033[1;33m"
#define DTL_GREEN_COLOR_HEAD            "\033[32m"
#define DTL_NONE_COLOR_HEAD             "\033[0m"
#define DTL_COLOR_END                   "\033[0m"


#define DTL_LOG_INFO(module,msg)	\
	TraceLog::info(module,msg,__FILE__, __LINE__);

#define DTL_LOG_WARNING(module,msg)	\
	TraceLog::warning(module,msg,__FILE__, __LINE__);
	
#define DTL_LOG_ERROR(module,msg)	\
	TraceLog::error(module,msg,__FILE__, __LINE__);

#define DTL_LOG_DEBUG(module,msg)	\
	TraceLog::debug(module,msg,__FILE__, __LINE__);

#define DTL_LOG_TRACE(module,msg)	\
	TraceLog::trace(module,msg,__FILE__, __LINE__);

#define DTL_LOG_NOTICE(module,msg)	\
	TraceLog::notice(module,msg,__FILE__, __LINE__);
	
#define DTL_LOG_CRITICAL(module,msg)	\
	TraceLog::critical(module,msg,__FILE__, __LINE__);

#define DTL_LOG_FATAL(module,msg)	\
	TraceLog::fatal(module,msg,__FILE__, __LINE__);
	
	
class DTL_DLLEXPORT TraceLog {

public:
	TraceLog(){}
	~TraceLog (){}
	
public:

	/**
	* 创建日志模块 module 
	* @param moduleName 模块名  eg:idmlserver
	* @param path 		日志文件的路径
	* @param level 		日志级别，0 ~ 8, level = 0, turn off logging, 
							PRIO_FATAL = 1,   /// A fatal error. The application will most likely terminate. This is the highest priority.
							PRIO_CRITICAL,    /// A critical error. The application might not be able to continue running successfully.
							PRIO_ERROR,       /// An error. An operation did not complete successfully, but the application as a whole is not affected.
							PRIO_WARNING,     /// A warning. An operation completed with an unexpected result.
							PRIO_NOTICE,      /// A notice, which is an information with just a higher priority.
							PRIO_INFORMATION, /// An informational message, usually denoting the successful completion of an operation.
							PRIO_DEBUG,       /// A debugging message.
							PRIO_TRACE        /// A tracing message. This is the lowest priority.
	* @noreturn
	*/
	static void createModule  (const String& moduleName, const String& path, int level = Poco::Message::PRIO_INFORMATION);
	
	static void createConsoleLogger  (int level = Poco::Message::PRIO_INFORMATION);
		
	/**
	* 设置日志级别
	* @param moduleName 模块名
	* @param level   0 ~8  
	*/ 
	static void setLogLevel (const String& moduleName, int level);
	
	static void getModuleNames (vector<String>& names);
	
	
	static void info(const String& moduleName, const String& msg, const String& file, int line);
	static void warning(const String& moduleName, const String& msg, const String& file, int line);
	static void error(const String& moduleName, const String& msg, const String& file, int line);
	static void debug(const String& moduleName, const String& msg, const String& file, int line);
	static void trace(const String& moduleName, const String& msg, const String& file, int line);
	static void notice(const String& moduleName, const String& msg, const String& file, int line);
	static void critical(const String& moduleName, const String& msg, const String& file, int line);
	static void fatal(const String& moduleName, const String& msg, const String& file, int line);

	
};


#endif	//_DTL_LOG_H_

