/***************************************************************************************************
directory.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__DIRECTORY_H__
#define __DTL__DIRECTORY_H__

#if PRAGMA_ONCE
#	pragma once
#endif


/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT Directory: public BaseFile
{
public:
	Directory(const String& fullPath)
		: BaseFile (fullPath)
	{
	}

	/**
	 * Copies directory information from another directory object.
	 */
	Directory (const Directory& dir)
		: BaseFile (dir)
	{
	}

	~Directory (void);

	
// Overriden methods
public:
	/**
	 * Determines whether the given path refers to an existing directory on disk.
	 * @return 	true if path refers to an existing directory; otherwise, false.
	 */
	virtual bool exists (void) const;

	/**
     * Returns the name of the file denoted by this abstract pathname.
     * @return  the name of the file denoted by this abstract pathname
     *          or String::EMPTY if can't get a file name from the path
	 */
	virtual String getName (void) const;


public:
	/**
	 * Creates the directory.
	 * If the directory already exists or be root path, this method does nothing.
	 *
	 * @throw IOException if the directory cannot be created. 
	 */
	void create (void);

	/**
	 * Create a subdirectory at current path this object denoted.
	 *
	 * @param	name The subdirectory name, if it is a form like "dir\subdir", here 
	 *			just use 'subdir' as the subdir name.
	 *
	 * @throw 	IOException if any IO errors occurred.
	 * @return 	The subdirectory object.
	 */
	Directory createSubDirectory (const String& name) const;

	/**
     * Returns an array of strings naming the files and directories in the
     * directory denoted by this abstract pathname.
     *
     * There is no guarantee that the name strings in the resulting array
     * will appear in any specific order; they are not, in particular,
     * guaranteed to appear in alphabetical order.
     *
     * @param subs  A vector of strings naming the files and directories in the
     *          	directory denoted by this abstract pathname.  The array will be
     *          	empty if the directory is empty.
     * @param pattern   	     
     *
     * @throws  IOException if any IO errors occurred.
     */
	void list (vector<String>& subs, const String& pattern = _T("*")) const;
	void list (vector<Directory>& subs, const String& pattern = _T("*")) const;

	/**
     * Returns an array of strings naming the directories in the
     * directory denoted by this abstract pathname.
     *
     * There is no guarantee that the name strings in the resulting array
     * will appear in any specific order; they are not, in particular,
     * guaranteed to appear in alphabetical order.
     *
     * @param	dirs A vector retrieves the subdirs contained at this directory.
     * @param	pattern The filter pattern that list the subdirs. For example, if pattern 
     *			is 'a?', here just list subdirs which is begin with letter 'a'. The default 
     *			value is '*' which means list all subdirs.
     *
     * @throws  IOException if any IO errors occurred.
     */
	void listDirs (vector<String>& dirs, const String& pattern = _T("*")) const;
	void listDirs (vector<Directory>& subs, const String& pattern = _T("*")) const;
	
	/**
     * Returns an array of strings naming the files in the
     * directory denoted by this abstract pathname.
     *
     * There is no guarantee that the name strings in the resulting array
     * will appear in any specific order; they are not, in particular,
     * guaranteed to appear in alphabetical order.
     *
     * @param	files A vector retrieves the files contained at this directory.
     * @param	pattern The filter pattern that list the files. For example, if pattern 
     *	        is '*.cpp', here just list all .cpp type files. The default value is 
     *          '*' which means list all files.
     *
     * @throws  IOException if any IO errors occurred.
     */
	void listFiles (vector<String>& files, const String& pattern = _T("*")) const;
	void listFiles (vector<File>& files, const String& pattern = _T("*")) const;
	
	/**
	 * Returns the parent directory.
	 *
	 * @throw 	IOException if isRoot() return true.
	 * @return 	the directory object that represents the parent path.
	 */
	Directory getParent (void) const;

	/**
	 * Test the directory whether is root path in file system.
	 *
	 * @return 	true if it is a root path, false otherwise.
	 */
	bool isRoot (void) const
	{
		const String& path = _fullPath;
		return (Path::getPathRoot (path) == path);
	}

	/**
	 * Remove this existing empty directory. if the directory doesn't exist, 
	 *  don't throw exception.
	 * @throws 	IOException if any IO errors occurred.
	 */
	void remove (void);

	/**
	 * Remove the directory tree, including sub directory and files. if the directory 
	 *	doesn't exist, don't throw exception.
	 *
	 * @throws 	IOException if any IO errors occurred.
	 */
	void removeTree (void);
	
}; // End class Directory

#endif // __DTL__DIRECTORY_H__
