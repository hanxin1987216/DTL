/***************************************************************************************************
daemon.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	后台服务类
Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_SYS_DAEMON_H__
#define __DTL_SYS_DAEMON_H__

#if PRAGMA_ONCE
#pragma once
#endif


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include <time.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <sys/wait.h>



typedef void (*fun_ptr)(const int); 


class DTL_DLLEXPORT Daemon
{
public:
	
	Daemon () 
	{
	}

	~Daemon () {}

	/**
	 * int daemon Process
	 * @param processName  ps显示进程名
	 * @param argc         参数个数
	 * @param argv         命令行参数值
	 * @param envp		   环境
	 */
	static void init (const String& processName, int argc, char *argv[], char *envp[], fun_ptr workerHandler);

private:


	fun_ptr		_masterHandler;
	fun_ptr		_workerHandler;
};


#endif // __DTL_SYS_TIMEDIFF_H__

