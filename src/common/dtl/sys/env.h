/***************************************************************************************************
env.h:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	
	环境变量配置
	
Author:
	韩欣

Creating Time:
	2012-03-10  	
  	
***************************************************************************************************/

#ifndef __DTL_SYS_ENVIRONMENT_H__
#define __DTL_SYS_ENVIRONMENT_H__

#include <vector>

#if PRAGMA_ONCE
#	pragma once
#endif

#include "osversion.h"
using std::vector;
/**
 * This class abtains enviroment information for current thread CFL running, 
 *	such as the user, os type, and computer name.
 */
class DTL_DLLEXPORT Environment
{
private:
	Environment (void) { /* Do nothing */ }
	
public:
	/**
	 * Returns the user of the calling process. The user is the one currently
	 *  logged onto the system.
	 *
	 * @return A user object.
	 */
	
	// TODO, User 暂未整合进DTL
	//static User* getCurrentUser (void);
	
	/**
	 * Obtains the version of the operating system that is currently running.
	 *
	 * @return A member of enum OSVersion that is the current version of the running OS.
	 */
	static OSVersion getCurrentOSVersion (void);

	/**
	 * 获得指定系统的名称
	 */
	static String getOSVerName (OSVersion ver);
	
	/**
	 * Returns the computer name. (NOT DNS name)
	 *
	 * @return A string contains the computer's name.
	 */
	static String getComputerName (void);
	
	/**
	 * Changes the computer name as the speicified name.
	 * NOTE: After this method calling, getComputerName() should return the new name.
	 *
	 * @param newName 	The new name for the computer. 
	 * @throw ArgumentException If the @newName is empty.
	 *		  Exception If error occurred when change the computer name.
	 */ 
	static void setComputerName (const String& newName);
	
	/**
	 * Returns the available number of processors in the computer.
	 *
	 * @return The number of processors.
	 */
	static size_t getAvailProcessors (void);
	
	/**
	 * Returns the size of physical memory avaiable, in bytes.
	 */
	static size_t getAvailPhysicalMemory (void);
	
	/**
	 * Returns the total size of physical memory, in bytes.
	 */
	static size_t getTotalPhysicalMemory (void);
	
	/**
	 * Returns the value of an environment variable.
	 *
	 * @param name	The name of the environment variable.
	 * @return 	The value of this env variable. If the specified 
	 *			environment variable was not found, return a empty
	 *			string.
	 * @exception ArgumentException If @name is empty.
	 */
	static String getEnvVariable (const String& name);		
	
	/**
	 * Changes or sets the value of an environment variable.
	 *
	 * @param name 	The name of the environment variable.
	 * @param value	The value to set. If it is empty, this method
	 *				calls deleteEnvVariable() to delete the speicfied 
	 *				environment variable.
	 *
	 * @exception ArgumentException If @name is empty.
	 *			  Exception If error occurred when set the environment 
	 *				variable's value.
	 */
	static void setEnvVariable (const String& name, const String& value);
	
	/**
	 * Deletes a variable from the environment.
	 * @param name 	The name of the environment variable.
	 * @exception ArgumentException If @name is empty.
	 *			  Exception If error occurred when delete the environment variable.		 
	 */
	static void deleteEnvVariable (const String& name);	
	
	/**
	 * Returns the tempariry path for all user.
	 */
	static String getTempPath (void);
	
	/**
	 * @param domains refer to the computer's domains name.
	 */
	static void getDomainNames (vector<String>& domains);

	//
	// TODO: It is necessary to add methods that returns the processor 
	// types or other processor information?
	//	
	
	/**
	 * Logon with the specified user on current oprating system.
	 *
	 * @param domain	The domain to verify the user. Pass empty string
	 *					if use the local machine.
	 * @param user		
	 * @param password						
	 */
	static bool logonUser (const String& domain, 
						   const String& user, 
						   const String& password);
	
	/**
	 * Returns the page size of the current computer.
	 */
	static size_t getPageSize (void);
	
}; // End class Environment	
		
#endif // __DTL_SYS_ENVIRONMENT_H__
