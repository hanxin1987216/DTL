/***************************************************************************************************
FileInputStream.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileOutputStream块
	
Auther:
	严支能 (yan.zhineng@datatom.com)
	
Created Time:
	2012-3-1
***************************************************************************************************/

#ifndef __DTL_IO_FILEOUTPUTSTREAM_H__
#define __DTL_IO_FILEOUTPUTSTREAM_H__

#if PRAGMA_ONCE
#	pragma once
#endif


/**
*  文件流
**/
class DTL_DLLEXPORT FileOutputStream
{
	
	DTL_DECLARE_NO_COPY_CLASS (FileOutputStream)

// Ctors and dtor
public:
	/**
	 * Constructs a file output stream to write to the file represented 
	 *	by the specified File object.
	 *
	 * @param	file The specified file.
	 * @param	mode The open, append or create mode when open the specified file.
	 * @param	share The share mode when open a file.
	 *
	 * @throw  	IOException  If an I/O error occurs.
	 */
	FileOutputStream (const File& file,  FileMode mode, FileShare share = READ_WRITE_SHARE);

	/**
	 * Constructs a file output stream to write to the file represented 
	 *	by the specified file name.
	 *
	 * @param	fileName The system-dependent file name.
	 * @param	mode The open, append or create mode when open the specified file.
	 * @param	share The share mode when open a file.
	 *
	 * @throw  	IOException  If an I/O error occurs.
	 *			ArgumentException If fileName is empty.
	 */
	FileOutputStream (const String& fileName, FileMode mode, FileShare share = READ_WRITE_SHARE);

	/**
	 * Close the file stream and release all resources.
	 */
	~FileOutputStream (void)
	{
		close ();
	}

// Overriden methods
public:

	/**
     * Writes the specified byte to this output stream. The general  contract 
	 *	for write() is that one byte is written to the output stream. The byte 
	 *	to be written is the eight low-order bits of the argument . The 24 
     *	high-order bits of @b are ignored.
     *
     * @param	b The byte to write.
     * @throw  	Exception  If an I/O error occurs. 
     */
    void write (int b);
	
	/**
     * Writes len bytes from the specified byte array to this output stream. 
     *
     * @param	bytes The data to write.	     
     * @param	len The number of bytes to write.
     *
     * @throw  	IOException  If an I/O error occurs. 
     *			ArgumentException If bytes is null.
     */
    void write (const unsigned char* bytes, size_t len);

	/**
     * Moves the file pointer to a specified location.
	 *
     * @param	offset The offset of bytes to be skipped.
	 * @param	origin The initial position. 
	 *
     * @return 	The offset, in bytes, of the new position from the beginning of the file.
     * @throw  	IOException  If an I/O error occurs.
     */
	int64 seek (int64 offset, SeekOrigin origin);

    /**
     * Flushes the internal buffer of the file on this output stream.
     *
     * @throw  	IOException  If an I/O error occurs.
     */
    void flush (void);

    /**
     * Closes this output stream and releases any system resources 
     * associated with this stream. 	     	     	     
     */
    void close (void) NO_THROW;

	/**
	 * Returns the current offset of the file pointer.
	 */
	int64 getCurrentOffset (void) const;

	/**
	 * Returns the file name of this output stream.
	 */
	String getFileName (void) const
	{
		return _fileName;
	}
	
	void setEndOfFile(int64 endOFFile) const;
	
protected:
	void open (FileMode mode, FileShare share);
	
// Data members
protected:

	// The file name
	String _fileName;

	// The file handle
	void* _handle;
	//int64 _length;
}; // End class FileOutputStream


#endif //  __DTL_IO_FILEOUTPUTSTREAM_H__
