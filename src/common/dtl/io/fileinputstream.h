/***************************************************************************************************
FileInputStream.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileInputStream块
	
Auther:
	严支能 (yan.zhineng@datatom.com)

Created Time:
	2012-02-28
***************************************************************************************************/
#ifndef __DTL_FILEINPUTSTREAM_HEAD_H__
#define __DTL_FILEINPUTSTREAM_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif



/**
* A #FileInputStream obtains input bytes from a file in a file system.
* What files are available depends on the host environment.
*/
class DTL_DLLEXPORT FileInputStream
{
	
	DTL_DECLARE_NO_COPY_CLASS (FileInputStream)

public:
	/**
	* Constructs a #FileInputStream by opening a connection to an actual file,
	* the file named by the #File object file in the file system.
	*
	* @param file the file to be opened for reading.
	* @param share the share mode when opened the file, the default is share
			  read and write
	*
	* @throw FileNotFoundException if the file does not exist,
	*		 or for some other reason cannot be opened for  reading.
	*/
	explicit FileInputStream (const File& file, FileShare share = READ_WRITE_SHARE);

	/**
	* Constructs a #FileInputStream by opening a connection to an actual file,
	* the file named by the path name name in the file system.
	*
	* @param name the system-dependent file name.
	* @share the share mode when opened the file, the default is share read
	and write
	*
	* @throw FileNotFoundException if the file does not exist,
	* or for some other reason cannot be opened for
	* reading.
	*/
	explicit FileInputStream (const String& name, FileShare share = READ_WRITE_SHARE);

	~FileInputStream (void)
	{
		close ();
	}



public:


	/**
     * Reads a byte of data from this input stream. 
     *
     * @return	The next byte of data, or -1 if the end of the
     *          file is reached.
     * @throw	Exception  If any I/O error occurs.
     */
	 int read (void);


	/**
	* Reads up to len bytes of data from the file into an array of bytes.
	*
	* @param bytes The buffer into which the data is read.
	* @param len The maximum number of bytes read.
	* 
	* @return The total number of bytes read into the buffer, or
	*		  -1 if there is no more data because the end of the file has been reached.
	* @throw ArgumentException If bytes is null.
	* @throw IOException If any I/O error occurs.
	*/
	int read (unsigned char* bytes, int len);

	/**
	* Moves the current file pointer of this file to a specified location.
	*
	* @param offset The offset of bytes to be moved.
	* @param origin The initial position
	*
	* @return The offset, in bytes, of the new position from the beginning of the file.
	* @throw IOException If an I/O error occurs.
	*/
	int64 seek (int64 offset, SeekOrigin origin);

	/**
	* Closes this file.
	*/
	void close (void) NO_THROW;

	/**
	* Returns the number of bytes that can be read from this file.
	*
	* @return The number of bytes that can be read from this file.
	* @throw IOException If an I/O error occurs.
	*/
	int64 available (void) const;

	String getFileName (void) const
	{
		return _name;
	}

protected:
	void open (FileShare share);

// Data members
protected:
	
	// The file name
	String _name;

	// The file handle
	void* _handle;

	int64 _hasRead;

}; // End class FileInputStream


#endif //  __FILESTREAM_HEAD_H__
