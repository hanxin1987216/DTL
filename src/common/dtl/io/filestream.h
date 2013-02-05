/***************************************************************************************************
FileStream.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	FileStream
	
Auther:
	刘佳陆 (liu.jialu@datatom.com)

Created Time:
	2012-02-04
***************************************************************************************************/
#ifndef __FILESTREAM_HEAD_H__
#define __FILESTREAM_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif

class DTL_DLLEXPORT FileStream
{
public:
	/**
	* 以流打开二进制文件
	*
	* @param name :the file name.
	* @param mode : the mode The open, append or create mode when open the specified
	file.
	* @param share: the share mode when opened the file
	* @return no
	* @throw FileNotFoundException if the file does not exist,
	* or for some other reason cannot be opened for
	* reading.
	*/
	explicit FileStream (const String& name, FileMode mode, FileShare share);

	/**
	* Constructs a FileInputStream by opening a connection to an actual file,
	* @param name    the file system.
	* @param share   the share mode when opened the file, the default is share read	and write
	* @throw Exception if the file does not exist, or for some other reason cannot be opened for reading.
	* @return no 
	*/
	explicit FileStream (const String& name, FileShare share = READ_WRITE_SHARE);

	virtual ~FileStream (void)
	{
		close ();
	}

public:
	/**
	* get the file handle
	* @return int : the handle of file
	*/
	const int getHandle (void) const
	{
		return _handle;
	}
	
	/**
	* get the length of the file
	* @return int64: the length of the file
	*/
	virtual int64 getFileLength (void) const;
	
	/**
	* read file
	* @param bytes 存放字节
	* @param len 需要read的长度
	* @return int 文件字节数小于len，返回值是实际读出的字节数，如果文件到达结尾返回0，错误返回-1
	*/
	virtual int read (char* bytes, size_t len);
	
	/**
	* 定位文件指针
	* @param offset 偏移量
	* @param origin BEGIN_ORIGIN,CURRENT_ORIGIN,END_ORIGIN
	* @return no
	*/
	virtual void seek (int64 offset, SeekOrigin origin);
	
	/**
	* unknown
	* @return  no
	*/
	virtual void available (void) const;

	/**
	* write
	* @param bytes : 写入的字符串
	* @param len :需要write的长度
	* @return int : 返回实际写到文件中的字节数，出错返回-1
	* @exception IOException if an I/O error occurs.
	*/
	virtual int write(const char* bytes, size_t len);

	/**
	* 强制写入磁盘
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void flush (void);

	/**
	* 关闭流
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	virtual void close (void) NO_THROW;

	/**
	* 文件指针定位到文件末尾
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	void endOfFile (void) const;

	/**
	* get the name of the file
	* @return String : the name of the file 
	* @throw IOException If an I/O error occurs.
	*/
	String getFileName (void)
	{
		return _name;
	}

	/**
	* 获得当前文件指针位置
	* @return ：返回从初始位置到当前位置的字节数 
	* @throw IOException If an I/O error occurs.
	*/
	int64 getCurrentPos (void)
	{
		_hasRead = lseek(_handle,0,SEEK_CUR);
		return _hasRead;
	}

private:
	String open (FileShare share, FileMode mode = OPEN_OR_CREATE_MODE);
	int convert (FileShare share,FileMode mode = OPEN_OR_CREATE_MODE);


	int      	_handle;
	String		_name;
	int64		_hasRead;

}; // End class FileStream
#endif //  __FILESTREAM_HEAD_H__
