/***************************************************************************************************
Path.h:	
	C++ Foundation Library header Paths
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This Path contain the declaration of classes:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__PATH_H__
#define __DTL__PATH_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT Path
{
public:
	Path (void);
	~Path (void);

// Static public members
public:
#ifdef __WINDOWS__		 
	static const tchar_t separator;						// The system-dependent default name-separator character. 
	static const tchar_t altSeparator;					// Provides a platform-specific alternate character used to separate directory 
														// levels in a path string that reflects a hierarchical file system organization.
														
	static const tchar_t volumeSeparator;				// Provides a platform-specific volume separator character.
	static const tchar_t pathSeparator;			 		// A platform-specific separator character used to separate path strings
														// in environment variables.
#else
	static const tchar_t separator;			 			// The system-dependent default name-separator character. 
	
	static const tchar_t altSeparator;			 		// Provides a platform-specific alternate character used to separate directory 
														// levels in a path string that reflects a hierarchical file system organization
	static const tchar_t volumeSeparator;			 	// Provides a platform-specific volume separator character.
	static const tchar_t pathSeparator; 				// A platform-specific separator character used to separate path strings
														// in environment variables.
#endif

	/**
	 * Provides a platform-specific array of characters that cannot be specified in 
	 *	path string arguments passed to members of the #Path class.
	 */
	static const tchar_t invalidPathChars[];
	
	/**
	 * The string contained the separator and altSeparator.
	 */
	static const tchar_t separatorChars[];

public:
	/**
	 * Combines two path strings.
	 *
	 * @param	path1 The left path string.
	 * @param	path2 The right path string
	 *
	 * @throw	ArgumentException if path1 or path2 contains invalid path characters.
	 * @return	A string path that was combined with the two string. If one of the string is empty, return 
	 *			another path. If the path2 is an absolute path, return it.
	 */
	static String combine (const String& path1, const String& path2);

	/**
	 * Makes the absolute path for the specified path string.
	 *
	 * @param	path The string to make the absolute path.
	 * @throw 	ArgumentException if path is empty string or only contain whitespace character 
	 *			or the path is a illegal form of a UNC path.
	 * @return 	The absolute path of the input path.
	 */
	static String makeFullPath (const String& path);

	/**
	 * Check the path whether or not be an absolute path
	 *
	 * @param	path the path to test. 
	 * @throw 	ArgumentException if path contains invalid path characters.
	 * @return 	true if path contains an absolute path; otherwise false.
	 */
	static bool isAbsolutePath (const String& path);

	/**
	 * Returns the current working directory of the application.
	 *
	 * @return 	A string containing the path of the current working directory.
	 */
	static String getCurrentPath (void);

	/**
	 * Returns the directory information for the specified path string.
	 *
	 * @param	path			is the path of a file or directory. 
	 * @throw 	Exception		if path is empty.
	 * @return 					a string containing directory information for path
	 */
	static String getDirectoryName (const String& path);

	/**
	 * Returns the file name and extension of the specified path string.
	 *
	 * @param	path is the path string from which to obtain the file name and extension. 
	 * @throw 	ArgumentException if path contains invalid path characters.
	 * @return 	a string consisting of the characters after the last directory 
	 *			character in path. If the last character of path is a directory or volume 
	 *			separator character, this method returns empty string. 
	 */
	static String getFileName (const String& path);


	/**
	 * Returns the root directory information of the specified path.
	 *
	 * @param	path is the path from which to obtain root directory information. 
	 *
	 * @return 	a string containing the root directory of path, if 
	 *			the path is not a absolute path, return empty string.
	 */
	static String getPathRoot (const String& path);

	/**
	 * Changes the path's extension file name as extension
	 *
	 * @param	path is the path want to change, after calling, this string may change its value.
     * @param	extension is the new file extension name. If it is empty, remove the path's 
     *			extension name.
	 * @throw 	ArgumentException if path contains invalid path characters
     *          or path not has a filename such as /root/include/
	 */
	static void changeExtension (String& path, const String& extension);

	/**
	 * add the extension file name to path
	 *
	 * @param	path is the path to add extension name, after calling, this string may change its value.
     * @param	extension is the new file extension name, if extension is empty, do nothing
	 * @throw 	ArgumentException if path contains invalid path characters.
     *          or path not has a filename such as /root/include/
	 */
	static void addExtension (String& path, const String& extension);

	/**
	* Returns the extension name of specified path.
	* @return 	the extension name of specified path
	*/
	static String getExtensionName (const String& path);


	/**
	* Checks the path whether or not be a valid path, i.e the path don't contains any 
	* invalid characters
	*
	* @param	path is the specified path name.
	* @return 	true if path is a valid path, otherwise return false
	*/
	static bool isValidPath (const String& path);

	/**
	* Returns current module path.
	*/
	static String getCurrentModulePath (void);
		
	/**
	 * Compare to path whether or not be the same path.
	 */
	static bool equal (const String& path1, const String& path2);

	/**
	 * Checks the path1 whether or not be parent path of path2.
	 * @param	path1 The left path string.
	 * @param	path2 The right path string.
	 * return   true if path1 is the parent path of path2.
	 */
	static bool isParentPath (const String& path1, const String& path2);	


	/**
	 * Returns the string that contains only invalid path chars.
	 */
	static String getInvalidPathChars (void);
	
	/**
	 * Returns the string that contains only the seperator char in a path string.
	 */
	static String getSeparatorChars (void);
	
    /**
     * Returns the string with seperators adapted to system, to WINDOWS is '\\', to POSIX is '/'
     *
     * In windows, if path start with '\', it's maybe an absolute path
     * or an UNC path(\\server\mount\dir), or current drive(\dir1\dir2\dir3)
     * so when a path start with '\', such as \\\a\b, we preserve it unchanged
     * where a\\\b changed to a\b
     *
     * In POSIX path, only double slash is preserved(//server/mnt/dir)
     * path start with '\' like ///dir1/dir2/dir3 will be changed to /dir1/dir2/dir3
     *
     * @param   path the path string to adapted
     * @return  the path string adapted
     */
    static String adaptSep(const String& path);
    
    /**
     * split the given [path] into directory part and filename part
     * if lack of directory or filename in [path], that part will be an
     * empty string
     *
     * @param   path the input path String
     * @param   dir the directory part of input [path], will be String::EMPTY if [path] has no directory
     * @param   file the file part of input [path], will be String::EMPTY if [path] has no directory
     */
    static void split(const String& path, String &dir, String &file);
}; // End class Path

#endif // __DTL__PATH_H__
