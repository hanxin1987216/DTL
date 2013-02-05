/***************************************************************************************************
errorprovider.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	异常提供者
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2011-11-28
***************************************************************************************************/

#ifndef __ERROR_PROVIDER_H__
#define __ERROR_PROVIDER_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "../lang/string.h"


/**
* Error Provider Interface
*/
class DTL_DLLEXPORT IErrorProvider
{
public:
	virtual ~IErrorProvider (void) { /* Do nothing */ }
	
	/**
	 * Returns the mapped String for the specified error code.
	 *
	 * @param errCode 	The specified error code to map.
	 * @return The mapped String. If no mapped String, return empty String.
	 */
	virtual String toString (int errCode) const = 0;
	
	/**
	 * Returns the mapped String for the specified error code.
	 *
	 * @param prefix  The prefix String before the mapped String.
	 * @param errCode The specified error code to map.
	 * @return The mapped String. If no mapped String, return the prefix String.
	 */
	virtual String toString (const String& prefix, int errCode) const = 0;
	
	/**
	 * Returns the name of the error provider.
	 */
	virtual String getProviderName (void) const = 0;
	
}; // End class IErrorProvider



/*******************************************************************************************
* 
* SystemErrorHandler
* 
*******************************************************************************************/

class DTL_DLLEXPORT SystemErrorHandler : public IErrorProvider
{
 // Singleton
 public:
	 /**
	  * Returns the instance of this class. If the instance does not exist, this 
	  *	method will create it.
	  *
	  * @return The single instance of this class.
	  */
	 static SystemErrorHandler* getInstance (void);
	
	 #define GET_SYSTEM_ERROR_HANDLER	SystemErrorHandler::getInstance()
		
	 /**
	  * Deletes the single instance of this class.
	  */
	 static void delInstance (void);
		
 private:
	 SystemErrorHandler (void) { /* Do nothing; */ }
	
	 static SystemErrorHandler* _inst;
		
 public:
	 /**
	  * Returns the mapped String for the specified error code.
	  *
	  * @param errCode 	The specified error code to map.
	  * @return The mapped String. If no mapped String, return empty String.
	  */
	 virtual String toString (int errCode) const;
	
	 /**
	  * Returns the mapped String for the specified error code.
	  *
	  * @param prefix  The prefix String before the mapped String.
	  * @param errCode The specified error code to map.
	  * @return The mapped String. If no mapped String, return the prefix String.
	  */
	 virtual String toString (const String& prefix, int errCode) const;
	
	 /**
	  * Returns the name of the error provider.
	  */
	 virtual String getProviderName (void) const;

}; 



class dtBaseErrorProvider : public IErrorProvider
{
public:
	dtBaseErrorProvider (const String& providerName) 
		: _providerName (providerName)
	{
	}
	
	
	virtual String toString (int errCode) const
	{
		return toString (String::EMPTY, errCode);
	}
	
	virtual String toString (const String& prefix, int errCode) const
	{
		//
		// Just convert errcode into string format.
		//
		String result;
		result.format (_T("%sErrorCode=%d"), prefix.getCStr (), errCode);
		
		return result;
	}
	
	/**
	 * Returns the name of the error provider.
	 */
	virtual String getProviderName (void) const
	{
		return _providerName;
	}
	
private:
	String _providerName;
	
}; // End class dtBaseErrorProvider
	




/**
* Get the ncGetSystemErrorProvider instance. Never delete the returned instance after using.
*/
DTL_DLLEXPORT 
IErrorProvider* ncGetErrorProvider (const String& providerName);


/**
 * Get the ncGetDTLErrorProvider instance. Never delete the returned instance after using.
 */
DTL_DLLEXPORT
IErrorProvider* ncGetDTLErrorProvider (void);

/**
* Determine the provider name whether be ncGetDTLErrorProvider.
*
* @return true if the provider name is equal to ncGetDTLErrorProvider's name.
*/
DTL_DLLEXPORT 
bool ncIsDTLErrorProvider (const String& providerName);





#endif // __ERROR_PROVIDER_H__
