/***************************************************************************************************
volume.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011-2012)

Purpose:
	delcare class of volume

Author:
	Shi Zhanhui (shi.zhanhui@datatom.com)

Creating Time:
	2012-07-27
***************************************************************************************************/
#ifndef __DTL_DEV__MGM__H__
#define __DTL_DEV__MGM__H__

enum STORAGETYPE
{
	LOCAL_STORAGE		= 0,   /* local disks space */
    SHARE_STORAGE		= 1,   /* a share space */
};

class DeviceMgm
{
public:
	/**
	* 获得某个设备容量
	* @param devname  设备名
	* @param capacity 返回容量
	* @return if success return true, or false
	*/
	static bool getCapacity(const String &devname, int64 &capacity);
	static bool getFreeSpace(const String &devname, int64 &freespace);
	static bool umount(const String &devpath);
	static bool isMount(const String &devpath);
	static bool getMountPoint(const String &devpath, String &mountpoint);
	static bool mount(const String &srcpath
									, const String &destpath
									, const int storageType = LOCAL_STORAGE
									, const String &hostip = String::EMPTY
									, const String &user = String::EMPTY
									, const String &passwd = String::EMPTY);
};

#endif //__DEV__MGM__H__
