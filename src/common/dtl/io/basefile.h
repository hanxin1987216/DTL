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

#ifndef __DTL__BASE_FILE_H__
#define __DTL__BASE_FILE_H__

#if PRAGMA_ONCE
#	pragma once
#endif


/**
 * This class 
 */
class DTL_DLLEXPORT BaseFile
{
public:
    /**
     * Constructs a system file object with path specified.
     *
     * @param path	The specified path of this file.         
     */
    explicit BaseFile (const String& path);
        
    /**
     * Copies a system file object.
     */
    BaseFile (const BaseFile& file);
    
    /**
     * Assigns a system file object.
     */
    BaseFile& operator= (const BaseFile& file);

    /**
     * Destroys a system file object.
     */
    virtual ~BaseFile(void);

// Public methods
public:
    /**
     * Tests whether the file or directory exists.
     *
     * @return true if exists, false otherwise.
     */
    virtual bool exists (void) const = 0;
    
    /**
     * @return the relative name of this file or directory.
     */
    virtual String getName (void) const = 0;
    
    /**
     * @return the full name of this file or directory.
     */
    String getFullName (void) const
    {
        return _fullPath;
    }

    /**
     * Refreshs the file or directory attributes.
     */
    void refresh (void)
    {
        loadFileAttrs ();
    }

    /**
     * Returns the time that the file or directory was last modified.
     * 
     * @return A 64-bit integer value representing the time that the file
     * 	or directory was last modified.
     */
    int64 getLastModified (void) const;
    
    /**
     * Returns the time that the file or directory was created.
     * 
     * @return	return A 64-bit integer value representing the time that the file
     *  		or directory was created.
     */
    int64 getCreationTime (void) const;
    

    /**
     * Returns the time that the file or directory was accessed.
     * 
     * @return	return A 64-bit integer value representing the time that the file
     *  		or directory was accessed.
     */
    int64 getLastAccess (void) const;
    

    /**
     * Returns the attributes that the file or directory had.
     * 
     * @return The combination of enumeration contants on FileAttributes.
     */
    FileAttributes getFileAttrs (void) const;
    
    /**
     * Changes the attributes of the file or directory.
     *
     * @param	attrs The new attributes that is combination of enum FileAttributes.
     * @throw	throw IOException or its subclass exception when cannot change the attributes.
     */
    void setFileAttrs (int attrs);
				   
// Static methods
public:
    /**
     * Check the path whether represents a file.
     * 
     * @param	path is the name which need to check.
     *
     * @return  true is @path is a file, otherwise return false if not be a file
     * 			or doesn't exists.
     */
    static bool isFile (const String& path);

    /**
     * Check the dir whether represents a directory.
     * 
     * @param	dir is the name which need to check.
     *
     * @return  true is dir is a directory, otherwise return false if not be a directory
     * 			or doesn't exists.
     */
    static bool isDirectory (const String& dir);

    /**
     * Returns the time that the file or directory was last modified.
     * 
     * @param	path The file or directory name.
     * @return  A 64-bit integer value representing the time that the file
     *  		or directory was last modified.
     * @throw	throw IOException or its subclass exception when cannot get the time.
     */
    static int64 getLastModified (const String& path);
    
    /**
     * Returns the time that the file or directory was created.
     * 
     * @param	path The file or directory name.
     * @return  A 64-bit integer value representing the time that the file
     *  		or directory was created.
     * @throw	throw IOException or its subclass exception when cannot get the time.
     */
    static int64 getCreationTime (const String& path);

    /**
     * Returns the time that the file or directory was accessed.
     * 
     * @param	path The file or directory name.
     * @return	return A 64-bit integer value representing the time that the file
     *  		or directory was accessed.
     * @throw	throw IOException or its subclass exception when cannot get the time.
     */
    static int64 getLastAccess (const String& path);
   

    /**
     * Returns the attributes that the file or directory had.
     * 
     * @param	path The file or directory name.
     * @return  The combination of enumeration contants on FileAttributes.
     *  		INVALID_FILE if the file or directory doesn't exist.
     */
    static FileAttributes getFileAttrs (const String& path);
    
    /**
     * Changes the attributes of the file or directory.
     *
     * @param	path The file or directory name.
     * @param	attrs The new attributes that is combination of enum FileAttributes.
     * @throw	throw IOException or its subclass exception when cannot change the attributes.
     */
    static void setFileAttrs (const String& path, int attrs);

protected:
	void loadFileAttrs (void);
	void setFileAttrs (const WapiFindData& fdata);
	
	BaseFile (const String& path, bool fullPath);
	
    struct FileData 
    {
        FileAttributes attrs;
        int64 length;
        int64 creationTime;
        int64 lastAccessTime;
        int64 lastModifiedTime;
    }; // FileData

	friend void generateList (std::vector<BaseFile*>& entries, 
								  const String& path, 
								  const String& pattern, 
								  int lastMask);		

    // We used a buffered skill to get the file informations
    FileData* _data;

    bool _needLoad;

    String _fullPath; 


}; // End class File

#endif // __DTL__FILE_H__
