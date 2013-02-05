/***************************************************************************************************
process.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011 - 2012)

Purpose:
	This header file contains classe Process that
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2012.1.17
	
	This library is free software; you can redistribute it and/or modify it under the terms of the 
 	GNU Lesser General Public License as published by the Free Software Foundation; either version 
 	2 of the License, or (at your option) any later version.
 
 	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 	even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser 
 	General Public License for more details.
 	
  	You should have received a copy of the GNU Lesser General Public License along with this library; if 
  	not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
  	USA.
  	
***************************************************************************************************/

#ifndef __DTL_SYS_PROCESS_H__
#define __DTL_SYS_PROCESS_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include <map>
#include <vector>
#include <utility>


#ifdef __WINDOWS__
	typedef void*		prcHandle;
	typedef unsigned int		pid_t;
#else
	typedef void*		prcHandle;
#endif	
	

/**
* 进程启动信息
*/
struct ProcessStartInfo
{
	int		flags;
			
	String	appName;
	String 	arguments;
	String	workingPath;
	
	typedef pair<String, String> EnvVariablePair;
	typedef vector <EnvVariablePair>  EnvVariableArray;


	EnvVariableArray envVariables;
	
	ProcessStartInfo ()
		: flags (0)
		, appName ()
		, arguments ()
		, workingPath ()
		, envVariables ()
	{
	}
			
}; // End struct ProcessStartInfo

/**
 * This class rerepsents a process in the operating system.
 *
 */
class DTL_DLLEXPORT Process
{	
// Static methods
public:		
	/**
	 * 通过popen执行命令行命令，并获取程序输出
	 * @param cmd  	命令行  eg "ls -la"
	 * @param lines  命令返回值，按行取结果
	 * 
	 * @return   true when success, or false
	 */
	static bool executeCmd (const String& cmd, vector<String> &lines);


	/**
	 * Create a new process with the specified settings.
	 *
	 * 注意：获得此指针后记得删除
	 */
	static Process* start (const ProcessStartInfo& startInfo);	

	/**
	 * Returns a process object that represents the current process.
	 */
	static Process* getCurrentProcess (void);
	
	/**
	 * Returns all process on the current computer.
	 *
	 * 获得此指针后记得删除		 
	 */
	static void GetAllProcesses (vector <Process*>& vec);
	
// Public methods
public:
	/**
	 * Constructs a Process object with specified application name,
	 *	arguments and working path.
	 */
	Process (pid_t pid, 
			 prcHandle handle, 
			 const String &name = String::EMPTY);
		
	/**
	 * Close process and thread handles. 
	 */
	~Process (void);
	
	/**
	 * Returns all environment variables for the new process.
	 *
	 * @param envVariables 	A vector contains the returning value with 
	 *						map[envName, value].
	 */
	void getEnvVariable (map<String, String>& envVariables);
	void setEnvVariable (const ProcessStartInfo::EnvVariableArray& envVariables);
		
	/**
	 * Returns the process Id.
	 * @throw InvalidOperationException If the process still not be created.
	 */
	pid_t getProcessId (void) const;

	/**
	 * Returns the exit code of this process.
	 * 
	 * @throw InvalidOperationException If the process still not exited.
	 */
	int getExitCode (void) const;


	/**
	 * Returns the process name.
	 */
	String getName (void) const;

	/**
	 * Wait util this process terminated.
	 */
	void waitFor (void);
	
	/**
	 * Wait util this process terminated or the timeout elapsed.
	 */
	void waitFor (int timeout);
	
	/**
	 * Terminates this process with specified exit code.
	 */
	void terminate (int exitCode);
	
	/**
	 * Tests this process whether exited.
	 */
	bool hasExited (void) const;
	

	// TODO: Move the starting process data to struct ProcessStartInfo
	// TODO: Adds method to get and set the process priority.
private:
	pid_t		_pid;
	prcHandle	_prcHandle;
	
	//
	// 应用程序名称
	//
	String		_name;
	
	typedef map<String, String> EnvVariableMap;

	EnvVariableMap _envVariables;		
}; // End class Process	

#endif // __DTL_SYS_PROCESS_H__
