/***************************************************************************************************
comdef.h:	
	C++ Foundation Library header Paths
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	DTL IO 公共定义文件

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__COMMON_IO_HEAD_H__
#define __DTL__COMMON_IO_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif


/**
 * The enumeration represents the attributes of a file and a directory.
 */
enum FileAttributes
{
	/**
	 * The file is read-only.
	 */
	READONLY = 0x00001,

	/**
	 * The file is hidden.
	 */
	HIDDEN = 0x00002,

	/**
	 * The file is a system file.
	 */
	SYSTEM = 0x00004,

	/**
	 * The file is a directory.
	 */
	DIRECTORY = 0x00010,

	/**
	 * The file is an archived file.
	 */
	ARCHIVE = 0x00020,

	/**	 */
	DEVICE = 0x00040, // Reserved for future use (NOT the w32 value). 

	/**
	 * The file is normal and has no other attributes set.
	 */
	NORMAL = 0x00080,

	/**
	 * The file is temporary.
	 */
	TEMPORARY = 0x00100,

	/**
	 * The file is a sparse file.
	 */
	SPARSE_FILE = 0x00200,

	/**
	 * The file contains a reparse point, which is a block of user-defined data associated with a file or a directory.
	 */
	REPARSE_POINT = 0x00400,

	/**
	 * The file is compressed.
	 */
	COMPRESSED = 0x00800, 

	/**
	 * The file is offline. The data of the file is not immediately available.
	 */
	OFFLINE = 0x01000,		

	NOT_CONTENT_INDEXED = 0x02000,

	ENCRYPTED = 0x04000, // NOT the w32 value

	SYMBOLIC_LINK = 0x01000000, // Symbolic link on Liux.

	INVALID_FILE = (-1),
}; // End enum FileAttributes



/**
 * Represents the action when open or create a file.
 */
enum FileMode 
{
	/**
	 * Specifies that the operating system should create a new file
	 */
	CREATE_NEW_MODE = 1,

	/** 
	 * Specifies that the operating system should create a new file.
	 *	If the file already exists, it will be overwritten. 
	 */
	CREATE_MODE = 2,

	/**
	 * Specifies that the operating system should open an existing file.
	 */
	OPEN_MODE = 3,

	/**
	 * Specifies that the operating system should open a file if it exists; 
	 *	otherwise, a new file should be created.
	 */
	OPEN_OR_CREATE_MODE = 4,

	/**
	 * Specifies that the operating system should open an existing file. 
	 *	Once opened, the file should be truncated so that its size is zero bytes. 
	 */
	TRUNCATE_MODE = 5,

	/**
	 * Opens the file if it exists and seeks to the end of the file, 
	 *	or creates a new file. 
	 */
	APPEND_MODE = 6,
	
}; // END enum FileMode



/**
 * Represents the original location when seek a file.
 */
enum SeekOrigin 
{
	/**
	 * Specifies the beginning of a stream.
	 */
	BEGIN_ORIGIN = 0,

	/**
	 * Specifies the current position within a stream.
	 */
	CURRENT_ORIGIN = 1,

	/**
	 * Specifies the end of a stream.
	 */
	END_ORIGIN = 2,
	
}; // End enum SeekOrigin


/**
 * Specifies the share mode when open a file.
 */
enum FileShare
{
	/**
	 * Declines sharing of the current file. Any request to open the file 
	 *	(by this process or another process) will fail until the file is closed.
	 */
	NONE_SHARE  = 0,

	/**
	 * Allows subsequent opening of the file for reading.
	 */
	READ_SHARE = 1,

	/**
	 * Allows subsequent opening of the file for writing.
	 */
	WRITE_SHARE = 2,

	/**
	 * Allows subsequent opening of the file for reading or writing.
	 */
	READ_WRITE_SHARE = 3,

	//FS_INHERITABLE = 16,

}; // End enum FileShare



static const unsigned int days_of_month[] = 
{
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 
};	


static const unsigned short mon_yday[2][13]={
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
	{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366},
};

unsigned int daysInMonth (unsigned int year, unsigned int month);


// 判断闰年
#define isleap(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))


/** 
*  接口定义
*/
String checkStatResult (int result);


void fileTimeToTime (int64 *result, const FILETIME *input);
void timeToFileTime (FILETIME* pft, const int64& t);


/**
* 加载文件属性
*/
FileAttributes loadFileAttributes (const tchar_t* file);


int convertFileShare (FileShare share);

int convertFileMode (FileMode mode);

int convertSeekOrigin (SeekOrigin origin);

#endif // __DTL__COMMON_IO_HEAD_H__
