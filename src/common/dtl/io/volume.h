/***************************************************************************************************
volume.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011-2012)

Purpose:
	delcare class of volume

Author:
	hanxin (han.xin@datatom.com)

Creating Time:
	2012-07-27
***************************************************************************************************/
#ifndef __DTL_VOLUME__H__
#define __DTL_VOLUME__H__

enum FileSystemType 
{
	UNKNOWN_TYPE,
	FAT12_TYPE,
	FAT16_TYPE,
	FAT32_TYPE,
	NTFS_TYPE,
	EXT2_TYPE, 
	EXT3_TYPE,
	EXT4_TYPE,
	XFS_TYPE,
	
	// ...
};


class Volume
{
public:
	Volume (const String& path);
	~Volume(){}

public:
	/**
	* 获得某个路径的容量
	* @return
	*/
	int64 getCapacity();

	/**
	* 获得某个路径的空余空间
	* @return
	*/
	int64 getFreeSpace();
	
	/**
	* 获取文件系统类型
	*/
	FileSystemType getFileSystemType();
	
private:

	String				_path;	
	int64				_capacity;
	int64				_freespace;
	FileSystemType		_fstype;
};

#endif //__DEV__MGM__H__
