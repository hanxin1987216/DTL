/***************************************************************************************************
library.cpp:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	
	运行时 Runtime
	
Author:
	韩欣

Creating Time:
	2012-03-10  	
***************************************************************************************************/

#ifndef __DTL_SYS_LIBRARY_H__
#define __DTL_SYS_LIBRARY_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * A class to operate system operation on current DTL runtime.
 */
class DTL_DLLEXPORT Runtime
{
public:
	/**
	 * Terminate the calling process.
	 *
	 * @status The exit status.
	 */
	static void exit (int status);
	
	/**
	 * Register a function that will be executed when the application exit.
	 * NOTE: This method is a wrapper for API atexit() on C-Runtime library.
	 * 
	 * @param fun 	The function to be executed at exit.
	 */
	static void atexit (void (* fun) (void)); 	
	
	/**
	 * Shuts down the computer and then restarts the computer.
	 * @throw SecurityException If the permission is not enough. 
	 */
	static void reboot (void);
	
	/**
	 * Shuts down the computer.
	 * @throw SecurityException If the permission is not enough. 
	 */
	static void shutdown (void);
	
	/**
	 * Logs the current user out.
	 * @throw SecurityException If the permission is not enough. 
	 */
	static void logout (void);
	
	/**
	 * Shuts down the computer and turns off the power.
	 * @throw SecurityException If the permission is not enough. 
	 */
	static void poweroff (void);
	
}; // End class Runtime	
		
#endif //
