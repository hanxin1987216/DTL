/***************************************************************************************************
log.cpp:	
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
#include <dtprec.h>
#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"


#include "log.h"

void
TraceLog::createConsoleLogger(int level)
{
	if (Poco::Logger::has("console") == NULL) {
		// set up two channel chains - one to the
		// console and the other one to a log file.
		Poco::FormattingChannel* pFCConsole = new Poco::FormattingChannel(new Poco::PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%p:%t"));
		pFCConsole->setChannel(new Poco::ConsoleChannel);
		pFCConsole->open();
		
		Poco::Logger& consoleLogger = Poco::Logger::create("console", pFCConsole, level);	
	}
}

void 
TraceLog::createModule  (const String& moduleName, const String& path, int level)
{
	Poco::FormattingChannel* pFCFile = new Poco::FormattingChannel(new Poco::PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%p:%t"));
	pFCFile->setChannel(new Poco::FileChannel(path.getCStr()));
	pFCFile->open();
	
	Poco::Logger& fileLogger = Poco::Logger::create(moduleName.getCStr(), pFCFile, level);
}

void 
TraceLog::info(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;

	Poco::Logger::get(moduleName.getCStr()).information (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::warning(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;

	Poco::Logger::get(moduleName.getCStr()).warning (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::error(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;

	Poco::Logger::get(moduleName.getCStr()).error (msg.getCStr(), file.getCStr(), line);
}
void 
TraceLog::debug(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;
		
	Poco::Logger::get(moduleName.getCStr()).debug (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::trace(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;
	Poco::Logger::get(moduleName.getCStr()).trace (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::notice(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;
		
	Poco::Logger::get(moduleName.getCStr()).notice (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::critical(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;
	
	Poco::Logger::get(moduleName.getCStr()).critical (msg.getCStr(), file.getCStr(), line);
}

void 
TraceLog::fatal(const String& moduleName,const String& msg, const String& file, int line)
{
	if (Poco::Logger::has(moduleName.getCStr()) == NULL)
		return;
		
	Poco::Logger::get(moduleName.getCStr()).fatal (msg.getCStr(), file.getCStr(), line);
}

