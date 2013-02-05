/***************************************************************************************************
library.cpp:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	
	ÔËÐÐÊ± Runtime
	
Author:
	º«ÐÀ

Creating Time:
	2012-03-10  	
***************************************************************************************************/

#include "../prec.h"
#include <stdlib.h>
#include "../lang/string.h"
#include "../sys/exception.h"


#ifndef __WINDOWS__
#include <dlfcn.h>
#endif

#include "env.h"
#include "runtime.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// class Library

#define	__WIN9X__ (Environment::getCurrentOSVersion () < OS_WINNT)

#ifdef __WINDOWS__
void exitWinNT (unsigned int uFlags)
{
	void* hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	if (!::OpenProcessToken (GetCurrentProcess(), 
	    		    		 TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
	    &hToken))
		THROW (strerror(errno));
	 
	if (!::LookupPrivilegeValue (NULL, SE_SHUTDOWN_NAME, 
	     				  	     &tkp.Privileges[0].Luid))
		THROW (strerror(errno));
	 
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	 
	if (!::AdjustTokenPrivileges (hToken, FALSE, &tkp, 0, 
	        			  	     (PTOKEN_PRIVILEGES)NULL, 0))
		THROW (strerror(errno));
      			 	 
	unsigned int errId = ::GetLastError ();
	if (errId != ERROR_SUCCESS)
		THROW (strerror(errno));

	if (!::ExitWindowsEx (uFlags, 0L)) {
		errId = ::GetLastError ();
		THROW (strerror(errno));
	}	
}

#endif /* __WINDOWS__ */

// public static
void 
Runtime::exit (int status)
{	
	::exit (status);
}

// public static
void 
Runtime::atexit (void (* fun) (void))
{	
	if (!fun)
	{
		THROW (_T("IDS_NULL_ARGUMENT"));	
	}
	
	if (!::atexit (fun)) {
		THROW (_T("IDS_RUNTIME_CANNOT_FUN_EXIT"));
	}
}

// public static 
void 
Runtime::reboot (void)
{
#ifdef __WINDOWS__
	if (__WIN9X__)
	{
		if(!::ExitWindowsEx (EWX_REBOOT, 0L))
			THROW (strerror(errno));
	}
	else
		exitWinNT (EWX_REBOOT);
#else
		exit (EXIT_SUCCESS);
#endif /* __WINDOWS__ */
}

// public static 
void 
Runtime::shutdown (void)
{	
#ifdef __WINDOWS__
	if (__WIN9X__)
	{
		if (!::ExitWindowsEx (EWX_SHUTDOWN, 0L))
			THROW (strerror(errno));
	}
	else
		exitWinNT (EWX_SHUTDOWN);
#else
		exit (EXIT_SUCCESS);
#endif /* __WINDOWS__ */
}

// public static 
void 
Runtime::logout (void)
{	
#ifdef __WINDOWS__
	if (__WIN9X__)
	{	
		if (!::ExitWindowsEx (EWX_LOGOFF, 0L))
			THROW (strerror(errno));
	}
	else
		exitWinNT (EWX_LOGOFF);
#else
		exit (EXIT_SUCCESS);
#endif /* __WINDOWS__ */
}

// public static 
void 
Runtime::poweroff (void)
{	
#ifdef __WINDOWS__
	if (__WIN9X__)
	{
		if (!::ExitWindowsEx (EWX_POWEROFF, 0L))
			THROW (strerror(errno));
	}
	else
		exitWinNT (EWX_POWEROFF);
#else
		exit (EXIT_SUCCESS);
#endif /* __WINDOWS__ */
}
