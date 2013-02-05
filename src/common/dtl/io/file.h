/***************************************************************************************************
File.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__FILE_H__
#define __DTL__FILE_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "./comdef.h"
#include "./basefile.h"

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT File: public BaseFile
{
public:
	File (const String& fileName)
		: BaseFile (fileName)
	{	
	}

public:
	/**
	 * Returns the length in bytes of this file.
	 *
	 * @return The length in bytes of this file, or zero if it doesn't exist.
	 */
	int64 getLength (void) const
	{
		if (exists () == false) 
			return 0;			

		return _data->length;
	}
	
	/**
	 * Check the file whether or not be readonly
	 *
	 * @return false if the file not be readonly or doesn't exist.
	 */
	bool isReadonly (void) const
	{
		if (exists () == false) 
			return false;

		return ((_data->attrs & READONLY) != 0);
	}

	/**
	 * Set file read-only attribute as be readonly
	 *
	 * @param	readonly The new read-only flag for this file.
	 *
	 * @throw 	IOException if I/O error occurred.
	 */
	void setReadonly (bool readonly);

	/**
	* This method deletes an existing file, if the file doesn't exist, 
	*  don't throw exception.
	*
	* @throws 	IOException if any IO errors occur
	*/
	void remove (void);

	/**
	 * Renames this file with the new file name.
	 *
	 * @param newName	The new file name specified to rename.
	 *
	 * @throw 	ArgumentException If the new file name is incorrect.
	 * @throw 	IOException if any IO errors occurred.
	 */
	void rename (const String& newName);
	
	/**
	 * Creates this file.
	 *
	 * @throw IOException if the file already exists or other IO errors occurred.
	 */
	void create (void);

	/**
	 * @param newFileName specifies the name of the new file.
	 * @param failIfExists 	If this parameter is TRUE and the new file 
	 *					   	specified by newFileName already exists, the 
	 *					   	function fails. If this	parameter is FALSE and 
	 *						the new file already exists, the function 
	 *						overwrites the existing file and succeeds.
	 *
	 * @throw IOException if any IO errors occurred.
	 */
	void copy (const String& newFileName, bool failIfExists);
	
	/**
	 * Truncates the file length to the new length.
	 * If the file doesn't exist or its length is less than the new 
	 *	length, this method do nothing.
	 *
	 * @param newLength	The new length to after truncating.
	 * 
	 * @throw IOException if any IO errors occurred.
	 * @return The new length of the file. If the file doesn't exist, return 0.
	 */
	int64 truncate (const int64& newLength);

// Overriden methods
public:

	/**
	* Gets a value indicating whether the file exists.
	* 
	* @return	true if the file exists; false if the file does not exist or 
	*			if the file is a directory.
	*/	
	bool exists (void) const;

	/**
	* Returns the name of the file denoted by this abstract pathname.
	*/
	String getName (void) const;	


}; // End class File

#endif // __DTL__FILE_H__
