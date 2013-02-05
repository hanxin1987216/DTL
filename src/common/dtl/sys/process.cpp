/***************************************************************************************************
process.cpp:	
	C++ Foundation Library source files
	Copyright (c) Datatom Software, Inc.(2004 - 2005)

Purpose:
	This file contains implementation of class Process

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

#include "../prec.h"
#include "../lang/string.h"
#include "../lang/int.h"
#include "../mono_base/processes.h"
#include "../mono_base/uglify.h"

#ifdef __SOLARIS__
	#include <procfs.h>
#endif

#ifdef __WINDOWS__
	#include "Tlhelp32.h"
	#include "Psapi.h"
	#define		PSAPI_LIB_NAME					_T("psapi.dll")
	#define		ENUM_PROCESS_MODULES_NAME		_T("EnumProcessModules")
	#define		GET_MODULE_BASE_NAME			_T("GetModuleBaseNameW")

	//
	// The EnumProcessModules function retrieves a handle for each module in the specified process.
	//
	typedef int (__stdcall * ENUM_PROCESS_MODULES_NAME_PROC)(void*, 
															  void**, 
															  unsigned int, 
															  unsigned int*);

	//
	// The EnumProcessModules function retrieves a handle for each module in the specified process.
	//
	typedef unsigned int (__stdcall * GET_MODULE_BASE_NAME_PROC)(void*,
														  void*,
														  tchar_t*,
														  unsigned int);

#else
	#include <fcntl.h>
	#include <unistd.h>
	#include "../sys/exception.h"
	#include "../io/file.h"

#endif // __WINDOWS__


#include "process.h"


// private ctor
Process::Process (pid_t pid, 
				  prcHandle handle, 
				  const String &name/* = String::EMPTY*/)
	: _pid (pid)
	, _prcHandle (handle)
	, _name (name)
#ifdef __SOLARIS__
	, _envVariables ()
#else
	//, _envVariables (less<String> (), pair<const String, String> ())
#endif
{

}


// public ctor
Process::~Process (void)
{
	//
    // Close process and thread handles. 
    //
    ::CloseHandle (_prcHandle);    	
}

bool 
Process::executeCmd (const String& cmd, vector<String> &lines)
{
	lines.clear ();
	if (cmd == String::EMPTY)
		return false;
	
	FILE * rp = popen (cmd.getCStr(), "r");
	if (rp == NULL)
		return false;
	
	char * line = 0;
	size_t len;
	ssize_t result = 0;
    while ((result = getline(&line, &len, rp)) != -1) {
    	if (line == 0) continue;
    	if (strlen (line) == 0) continue;
    	lines.push_back (line);
    }
	
	if (line) free (line);
	pclose (rp);
	return true;
}


// public static 
Process* 
Process::getCurrentProcess (void)
{	
	prcHandle handle = ::GetCurrentProcess ();
	
	pid_t pid = ::GetCurrentProcessId ();
	

	if (!pid)
		THROW_ID ("GetCurrentProcessId Failed", ::GetLastError ());
	
	return (new Process (pid, handle));
}

// public static 
void
Process::GetAllProcesses (vector <Process*>& vec)
{
#ifdef __WINDOWS__
	//
	// 声明进程信息变量	
	//
	PROCESSENTRY32 ProcessInfo;

	void* SnapShot = ::CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);

	//
	// 设置ProcessInfo的大小
	// 
	ProcessInfo.dwSize = sizeof (ProcessInfo);
	
	//
	// 返回系统中第一个进程的信息
	//
	int Status = ::Process32First (SnapShot, &ProcessInfo);

	while (Status) {
		void* hProcess = ::OpenProcess( PROCESS_ALL_ACCESS, FALSE, ProcessInfo.th32ProcessID);
		
		vec.push_back (new Process (ProcessInfo.th32ProcessID, hProcess, String (ProcessInfo.szExeFile)));
		
		//
		// 获取下一个进程的信息
		//
		Status = ::Process32Next (SnapShot, &ProcessInfo);
	}
	::CloseHandle (SnapShot);
#endif
}

// public 
void 
Process::getEnvVariable (map<String, String>& envVariables)
{
#ifdef __WINSOWS__
	
	typedef EnvVariableMap::value_type value_type;
	
	if (_envVariables.empty ())
	{
		LPVOID lpvEnv;
		lpvEnv = ::GetEnvironmentStrings ();
		
		if (!lpvEnv)
			THROW_ID ("GetEnvironmentStrings Failed", ::GetLastError ());
		
		//
		// 处理并传入 map
		//
		tchar_t* pPos;
		String strKey, strValue;

		pPos = (tchar_t *) lpvEnv;
		
		while (*pPos) {
			strKey.clear ();
			while (*pPos != _T('=')) {
				strKey += *pPos;
				++pPos;
			}
			
			if (*pPos == _T('='))
				++pPos;
			
			int value = 0;
			while (*pPos) {
				strKey += *pPos;
				++pPos;
			}
			
			//	
			// 传入 map 容器中
			//
			envVariables.insert (value_type (strKey, strValue));
			
			++pPos;
		}
		//
		// End 处理
		//
		if (!::FreeEnvironmentStrings (tchar_t* (lpvEnv)))
			THROW_ID ("FreeEnvironmentStrings Failed", ::GetLastError ());
		return;
	}
	
	envVariables.clear ();
	envVariables.insert (_envVariables.begin (), _envVariables.end ());
#endif
}

// public 
void 
Process::setEnvVariable (const ProcessStartInfo::EnvVariableArray& envVariables)
{
#ifdef __WINDOWS__
	typedef ProcessStartInfo::EnvVariableArray::const_iterator iterator;
	typedef EnvVariableMap::value_type value_type;

	iterator itend = envVariables.end();
	for (iterator it = envVariables.begin(); it != itend; ++it) {
		value_type value ((*it).first, (*it).second);
		_envVariables.insert (value);
	}
#else
	THROW (_T("setEnvVariable Not Implement"));
#endif // __WINDOWS__
}

// public 
Process*
Process::start (const ProcessStartInfo& startInfo)
{	
    STARTUPINFO si;

	memset (&si, 0, sizeof (si));
    si.cb = sizeof (si);
    
    PROCESS_INFORMATION pi;
	
	String strPath =_T("\"");
	strPath += startInfo.appName;
	strPath += _T("\" ");
	strPath += startInfo.arguments;

	String strEnvVariables;
	if (!startInfo.envVariables.empty ()) {
		typedef ProcessStartInfo::EnvVariableArray::const_iterator iterator;
	
		iterator itend = startInfo.envVariables.end();
		for (iterator it = startInfo.envVariables.begin(); it != itend; ++it) {
			strEnvVariables += (*it).first;
			strEnvVariables += _T("=");
			strEnvVariables += (*it).second;
			
			strEnvVariables += _T('\0');			
		}
		strEnvVariables += _T('\0');
	}
	
	//
    // Start the child process.
    //    
	if (::CreateProcess (NULL,
						 const_cast<tchar_t *> (strPath.getCStr ()),
						 NULL,
						 NULL,
						 FALSE,
						 startInfo.flags | CREATE_UNICODE_ENVIRONMENT,
						 (strEnvVariables.isEmpty () ? NULL : (void*) (strEnvVariables.getCStr ())),
						 (startInfo.workingPath.isEmpty () ? NULL : startInfo.workingPath.getCStr ()),
						 &si,
						 &pi) == FALSE) 
	{
		
		
		THROW_BY_HANDLER (GET_SYSTEM_ERROR_HANDLER->toString (::GetLastError ()), ::GetLastError (), SystemErrorHandler::getInstance ());
	}
	
	if (!::CloseHandle (pi.hThread)) {
		String error;
		error.format("Start Process %s Failed!", strPath.getCStr());
		THROW (error);
	}
	    
	Process* process = new Process (pi.dwProcessId, pi.hProcess, startInfo.appName);
	
	if (!process) {
		String error;
		error.format(_T("Start Process %s Failed!"), strPath.getCStr());
		THROW (error);
	}
	
	if (!startInfo.envVariables.empty ())
		process->setEnvVariable (startInfo.envVariables);
	
	return process;
}

// public 
pid_t 
Process::getProcessId (void) const
{
	return _pid;
}

// public
String
Process::getName (void) const
{	
	if (_name.isEmpty () == false)
		return _name;

#ifdef __WINDOWS__
	void* mod = 0;
	tchar_t name [MAX_PATH];
	unsigned int needed, len;

	// 
	// 将 Psapi.dll 装载出来
	//
	void* PSAPI_Lib = 0;	// 指向 psapi.dll 共享库。
	PSAPI_Lib = Runtime::loadLibrary (PSAPI_LIB_NAME);

	ENUM_PROCESS_MODULES_NAME_PROC PSAPI_EnumProc = (ENUM_PROCESS_MODULES_NAME_PROC) Runtime::loadSymbol (PSAPI_Lib,
																										  String (ENUM_PROCESS_MODULES_NAME));

	if (!PSAPI_EnumProc (_prcHandle, &mod, sizeof(mod), &needed)) {
		Runtime::unloadLibrary (PSAPI_LIB_NAME);
		THROW (::GetLastError ());
	}

	GET_MODULE_BASE_NAME_PROC PSAPI_GetNameProc = (GET_MODULE_BASE_NAME_PROC) Runtime::loadSymbol (PSAPI_Lib,
																								   String (GET_MODULE_BASE_NAME));

	if (!(len = PSAPI_GetNameProc (_prcHandle, mod, name, sizeof (name)))) {
		Runtime::unloadLibrary (PSAPI_LIB_NAME);
		THROW ("Get Process Name failed"); 
	}

	// lzma.dll 已经被装载，缷除。
	Runtime::unloadLibrary (PSAPI_Lib);

	const_cast<Process*>(this)->_name.assign (name, len);
	return _name;
	
#elif defined(__SOLARIS__)
	const_cast<Process*>(this)->_name = ::getexecname ();
	return _name;
	
#elif defined(__AIX__) || defined(__HPPA__)
	unsigned int pid = ::GetCurrentProcessId ();
		
	#define PATH_BUF_LEN		(1024)
	char *buf = new char[PATH_BUF_LEN]; 
    ::memset (buf, 0, PATH_BUF_LEN);								// 初始化buf,以免后面写如乱码到文件中
    
    String cmd;
    
#if defined(__SOLARIS__)
	cmd.format ("ps -e | grep %d | awk '{print $5}'", pid);
#elif defined(__HPPA__)
	cmd.format ("ps -e | grep %d | awk '{print $4}'", pid);
#else
    cmd.format ("ps -p %d -o args=", pid);
#endif

    FILE *stream = ::popen (cmd.getCStr (), "r");					// 将 "ps" 命令的输出 通过管道读取 ("pid" 参数) 到 FILE* stream
    size_t len = ::fread (buf, sizeof (char), PATH_BUF_LEN, stream);				// 将刚刚 stream 的数据流读取到buf中
    ::pclose (stream);  
    
    //
    // 去除多余的换行符，防止上层使用时出错
    //
	for (int i = 0; i < strlen (buf); ++i) {
		//
		// 检查是否存在 \n 换行符，将换行符修改为 \0
		//
		if (buf[i] == '\n') {
			buf[i] = '\0';
			break;
		}
	}
	
    String name (buf);
    name = name.trim ('\n');
    name = name.trim ('\r');
    size_t pos = name.rfind (_T('/'), name.getLength ());
    if (pos != String::NO_POSITION)
    	name = name.subString (pos + 1, name.getLength () - pos);
    	
    //printf ("name: %s\n\n", name.getCStr ());
	const_cast<Process*>(this)->_name = name;
    return _name;
#else
	guint32 pid = GetCurrentProcessId ();
	String fileName;
	fileName.format (_T("/proc/%d/cmdline"), pid);
	int fd = open (fileName.getCStr (), 0);
	if (fd == -1) {
		String error;
		error.format(_T("Get Process Name  %s Failed"), fileName.getCStr());
		THROW (error);
	}

	char buf [1024];
	String line;

	errno = 0;
	char* ptr = buf;
	while (true) {
		memset (ptr, 0, 1024);
		size_t len = read (fd, ptr, 1024);
		if (len > SSIZE_MAX)
			break;

		if (len == 0)
			break;

		line.append (ptr);
	}

	//
	// 关闭打开的文件
	//
	close (fd);

	File file (line);
	String prgname = file.getName ();
	const_cast<Process*>(this)->_name.assign (prgname);
	return _name;	
#endif
}

// public 
void 
Process::waitFor (void)
{	
	//
    // Wait until child process exits.
    //
	if (::WaitForSingleObject (_prcHandle, Int::INFINITE_VALUE) == WAIT_FAILED)
		THROW ("WaitForSingleObject Error!");
}

// public 
void 
Process::waitFor (int timeout)
{	
	//
    // Wait until child process exits.
    //
    if (::WaitForSingleObject (_prcHandle, timeout) == WAIT_FAILED)
		THROW ("WaitForSingleObject Error");
}

// public 
void 
Process::terminate (int exitCode)
{	
	if (!::TerminateProcess (_prcHandle, exitCode))
		THROW ("TerminateProcess error");
}

// public 
bool 
Process::hasExited (void) const
{	
	unsigned int exitCode;
	if (!::GetExitCodeProcess (_prcHandle, TO_DWORD_PTR(&exitCode)))
		THROW ("GetExitCodeProcess error");
	
	if (exitCode == STILL_ACTIVE)
		return false;
	else
		return true;
}

// public 
int 
Process::getExitCode (void) const
{
	unsigned int exitCode;
	if (!::GetExitCodeProcess (_prcHandle, TO_DWORD_PTR(&exitCode)))
		THROW ("GetExitCodeProcess error");
	
	if (exitCode == STILL_ACTIVE) {
		THROW ("InvalidOperation");
	}
			
	return exitCode;
}
