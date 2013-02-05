/****************************************************************************************************
resreader.h
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	resource file reader
	
Auther:
	hanxin

Created Time:
	2012-3-08
****************************************************************************************************/

#ifndef __DTL_UTIL_RES_READER_H__
#define __DTL_UTIL_RES_READER_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include <map>

typedef map<String, String> MessageHash;


/**
 * A interface to load the resource data for different locale. 
 */
class DTL_DLLEXPORT IResourceReader
{
public:
	virtual ~IResourceReader (void) { /* Do nothing */ }		
	
public:	
	/**
	 * Loads string object with the specified resource name. 
	 *
	 * @param resID 	The resource name.
	 * @throw Exception If no mapped resource for the specified name.
	 */
	virtual String loadString (const String& resName) = 0;
			
	/**
	 * Returns the name of the resource file.
	 *
	 * @return The name of the resourece file.
	 */
	virtual String getFileName (void) const = 0;
		
	virtual void* getFileHandle (void) const = 0;

}; // End class IResourceReader
	


/**
* *.do 格式的资源文件读取
*/
class DTL_DLLEXPORT DoResourceReader : public IResourceReader
{
public:
	/**
	 * Constructs DoResourceReader object with the specified .do file.
	 *	
	 * @param path 	The file path of the do file specified.
	 * @throw Exception If cannot open the specifiedmo file.
	 */
	DoResourceReader (const String& path);


	/**
	 * Constructs DoResourceReader object with the specified .do file.
	 *	
	 * @param name 	The file name of the mo file specified. donot include path
	 * @param useLanguage  是否使用语言目录，true 到程序根目录下的 en_US, zh_CN, zh_TW_CN 目录下读取
	 * @throw Exception If cannot open the specifieddo file.
	 */
	DoResourceReader (const String& name, bool useLanguage);

	virtual ~DoResourceReader (void);	
		
	
// Overriden methods
public:

	/**
	 * Loads string object with the specified resource name. 
	 *
	 * @param resID 	The resource name.
	 * @throw Exception If no mapped resource for the specified name.
	 */
	virtual String loadString (const String& resName);

	/**
	 * Returns the name of the resource file.
	 *
	 * @return The name of the resourece file.
	 */
	virtual String getFileName (void) const;

	/**
	 * Returns the handle of the resource file.
	 *
	 * @return The handle pointer for this resource file.
	 */
	virtual void* getFileHandle (void) const;
	
	const MessageHash &getMessages (void) const
	{
		return _strHash;	
	}

protected:
	void init (const String &file);
	String find (const String &msgid);
	
protected:
	String			_doName;
	void			*_fileHandle;
	
	MessageHash		_strHash;
}; // End class DoResourceReader


#endif // __DTL_UTIL_RES_READER_H__
