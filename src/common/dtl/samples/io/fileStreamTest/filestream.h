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
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef>
#include <dtl.h>
using namespace std;

#define MAX_LENGTH = 1024

/**
* The enumeration represents the attributes of a file and a directory.

enum FileAttributes
{
*/	/**
	* The file is read-only.
	
	READONLY = 0x00001,
*/
	/**
	* The file is hidden.
	
	HIDDEN = 0x00002,
*/
	/**
	* The file is a system file.
	
	SYSTEM = 0x00004,
*/
	/**
	* The file is a directory.
	
	DIRECTORY = 0x00010,
*/
	/**
	* The file is an archived file.
	
	ARCHIVE = 0x00020,
*/
	/** 
	DEVICE = 0x00040, // Reserved for future use (NOT the w32 value).
*/
	/**
	* The file is normal and has no other attributes set.
	
	NORMAL = 0x00080,
*/
	/**
	* The file is temporary.
	
	TEMPORARY = 0x00100,
*/
	/**
	* The file is a sparse file.
	
	SPARSE_FILE = 0x00200,
*/
	/**
	* The file contains a reparse point, which is a block of user-defined
	data associated with a file or a directory.
	
	REPARSE_POINT = 0x00400,
*/
	/**
	* The file is compressed.
	
	COMPRESSED = 0x00800,
*/
	/**
	* The file is offline. The data of the file is not immediately available.
	
	OFFLINE = 0x01000,

	NOT_CONTENT_INDEXED = 0x02000,

	ENCRYPTED = 0x04000, // NOT the w32 value

	SYMBOLIC_LINK = 0x01000000, // Symbolic link on Liux.

	INVALID_FILE = (-1),
};// End enum FileAttributes
*/ 
/**
* Represents the original location when seek a file.

enum SeekOrigin
{
*/	/**
	* Specifies the beginning of a stream.
	
	BEGIN_ORIGIN = 0,
*/
	/**
	* Specifies the current position within a stream.
	
	CURRENT_ORIGIN = 1,
*/
	/**
	* Specifies the end of a stream.
	
	END_ORIGIN = 2,

}; // End enum SeekOrigin
*/
/**
* Represents the action when open or create a file.

enum FileMode
{
*/	/**
	* Specifies that the operating system should create a new file
	
	CREATE_NEW_MODE = 1,      //O_CREAT
*/
	/**
	* Specifies that the operating system should create a new file.
	* If the file already exists, it will be overwritten.
	
	CREATE_MODE = 2,               
*/
	/**
	* Specifies that the operating system should open an existing file.
	
	OPEN_MODE = 3,
*/
	/**
	* Specifies that the operating system should open a file if it exists;
	* otherwise, a new file should be created.
	
	OPEN_OR_CREATE_MODE = 4,         //O_CREAT
*/
	/**
	* Specifies that the operating system should open an existing file.
	* Once opened, the file should be truncated so that its size is zero bytes.
	
	TRUNCATE_MODE = 5,            //O_TRUNC
*/
	/**
	* Opens the file if it exists and seeks to the end of the file,
	* or creates a new file.
	
	APPEND_MODE = 6,           //O_APPEND

}; // END enum FileMode

*/

/**
* Specifies the share mode when open a file.

enum FileShare
{
*/	/**
	* Declines sharing of the current file. Any request to open the file
	* (by this process or another process) will fail until the file is closed.
	
	NONE_SHARE = 0,
*/
	/**
	* Allows subsequent opening of the file for reading.
	
	READ_SHARE = 1,
*/
	/**
	* Allows subsequent opening of the file for writing.
	
	WRITE_SHARE = 2,
*/
	/**
	* Allows subsequent opening of the file for reading or writing.
	
	READ_WRITE_SHARE = 3,

	//FS_INHERITABLE = 16,

}; // End enum FileShare
*/
/////////////////////////////////////////////////////////////////////////////////


class FileStream
{
public:
	/**
	* Constructs a #FileInputStream by opening a connection to an actual file,
	* the file named by the #File object @file in the file system.
	*
	* @name the system-dependent file name.
	* @mode the mode The open, append or create mode when open the specified
	file.
	* @share the share mode when opened the file, the default is share read
	and write
	* @throw FileNotFoundException if the file does not exist,
	* or for some other reason cannot be opened for
	* reading.
	*/
	explicit FileStream (const String& name, int mode, FileShare share);

	/**
	* Constructs a #FileInputStream by opening a connection to an actual file,
	* the file named by the #File object @file in the file system.
	*
	* @file the file to be opened for reading.
	* @share the share mode when opened the file, the default is share read
	and write
	* @throw FileNotFoundException if the file does not exist,
	* or for some other reason cannot be opened for
	* reading.
	*/
	explicit FileStream (const File& file, FileShare share = READ_WRITE_SHARE);

	/**
	* Constructs a #FileInputStream by opening a connection to an actual file,
	* the file named by the path name @name in the file system.
	*
	* @name the system-dependent file name.
	* @share the share mode when opened the file, the default is share read
	and write
	* @throw FileNotFoundException if the file does not exist,
	* or for some other reason cannot be opened for
	* reading.
	*/
	explicit FileStream (const String& name, FileShare share = READ_WRITE_SHARE);

	virtual ~FileStream (void)
	{
		close ();
	}

public:
	/**
	* 获得句柄
	*/
	const int getHandle (void) const
	{
		return _handle;
	}
	
	/**
	* 获得文件长度
	*/
	virtual int64 getFileLength (void) const;
	
	/**
	* 读
	* @param bytes :存放字节
	* @param len :需要read的长度
	*/
	virtual int read (char* bytes, size_t len);
	
	/**
	* 定位文件指针
	* @param offset :偏移量
	* @param origin :SeekOrigin中的一种
	*/
	virtual void seek (int64 offset, SeekOrigin origin);
	
	/**
	* 不清除
	* @
	* @return : no
	*/
	virtual void available (void) const;

	/**
	* 写
	* @param bytes : 写入的字符串
	* @param len :需要write的长度
	* @return no
	* @exception IOException if an I/O error occurs.
	*/
	virtual void write(const char* bytes, size_t len);

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
	* 获得文件名字
	* @return ：no 
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
		_hasRead = fseek(_file,0,SEEK_CUR);
		return _hasRead;
	}

private:
	String open (FileShare share, FileMode mode = OPEN_OR_CREATE_MODE);
	int convert (FileShare share,FileMode mode = OPEN_OR_CREATE_MODE);

	/**
	* 检查文件是否关闭
	* @return ：no 
	* @throw IOException If an I/O error occurs.
	*/
	void checkClosed (void) const;

	//int			_file;
	int      	_handle;
	String		_name;
	int64		_hasRead;
	int 		_checknum;


}; // End class FileStream

