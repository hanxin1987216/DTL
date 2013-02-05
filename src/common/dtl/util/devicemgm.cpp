/***************************************************************************************************
DeviceMgm.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011-2012)

Purpose:
	implement class of DeviceMgm

Author:
	Shi Zhanhui (shi.zhanhui@datatom.com)

Creating Time:
	2012-07-27
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../lang/string.h"
#include "../lang/int64.h"
#include "../io/comdef.h"
#include "../io/path.h"
#include "../io/file.h"
#include "../io/directory.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "../sys/process.h"
#include "devicemgm.h"

#define SUCCESS 0
#define FAIL -1

//private
static void
excludePath(String &fullpath)
{
	int len = fullpath.getLength();
	if(len > 2){
		if(fullpath[len - 1] == '/'){
			fullpath = fullpath.subString(0, len - 1);	
		}			
	}
}

bool 
getDeviceSizes(const String &devname
					, int64 &capacity
					, int64 &used
					, int64 &free
					, String &mountpoint)
{
	vector<String> lines;
	if(!Process::executeCmd("df -P", lines)){
		return false;	
	}
	char src[256];
	char dest[256];
	char usedstr[256];
	char freestr[256];
	char capacitystr[256];
	char persentagestr[256];
	
	memset(src, 0, sizeof(src));
	memset(dest, 0, sizeof(dest));
	memset(usedstr, 0, sizeof(usedstr));
	memset(freestr, 0, sizeof(freestr));
	memset(capacitystr, 0, sizeof(capacitystr));
	memset(persentagestr, 0, sizeof(persentagestr));
	String devpath = devname;
	excludePath(devpath);
	for(size_t i = 0; i < lines.size(); ++i){
		sscanf(lines[i].getCStr()
						, "%s\t%s\t%s\t%s\t%s\t%s"
						, src, capacitystr, usedstr, freestr, persentagestr, dest);
		String srcstr (src);
		String deststr (dest);
		excludePath(srcstr);
		excludePath(deststr);
		if(srcstr == devpath || deststr == devpath){
			capacity = Int64::getValue(capacitystr);
			used = Int64::getValue(usedstr);
			free = Int64::getValue(freestr);
			mountpoint = deststr;
			return true;
		}
		memset(src, 0, sizeof(src));
		memset(dest, 0, sizeof(dest));
		memset(usedstr, 0, sizeof(usedstr));
		memset(freestr, 0, sizeof(freestr));
		memset(capacitystr, 0, sizeof(capacitystr));
		memset(persentagestr, 0, sizeof(persentagestr));
	}
	return false;	
}

bool 
DeviceMgm::getCapacity(const String &devname, int64 &capacity)
{
	int64 used;
	int64 free;
	String mountpoint;
	return getDeviceSizes(devname, capacity, used, free, mountpoint);	
}

bool 
DeviceMgm::getFreeSpace(const String &devname, int64 &freespace)
{
	int64 used;
	int64 capacity;
	String mountpoint;
	return getDeviceSizes(devname, capacity, used, freespace, mountpoint);
}

bool 
DeviceMgm::mount(const String &srcpath
				, const String &destpath
				, const int storageType /*= LOCAL_STORAGE*/
				, const String &hostip /*= String::EMPTY*/
				, const String &user /*= String::EMPTY*/
				, const String &passwd /*= String::EMPTY*/)
{
	String cmd;
	Directory dir(destpath);
	if(!dir.exists()){
		dir.create();
	}
	if(storageType == SHARE_STORAGE){
		cmd.format("mount //%s/%s %s -o username=%s,password=%s >/dev/null 2>&1"
					 , hostip.getCStr()
					 , srcpath.getCStr()
					 , destpath.getCStr()
					 , user.getCStr()
					 , passwd.getCStr());
	}else if(storageType == LOCAL_STORAGE){
		cmd.format("mount %s %s >/dev/null 2>&1", srcpath.getCStr(), destpath.getCStr());
	}
	
	if (system(cmd.getCStr()) == SUCCESS)
		return true;
		
	return false;
}

bool 
DeviceMgm::umount(const String &devpath)
{
	String cmd;
	cmd.format("umount %s >/dev/null 2>&1", devpath.getCStr());

	if (system(cmd.getCStr()) == SUCCESS)
		return true;
	return false;
}

bool 
DeviceMgm::isMount(const String &devpath)
{
	int64 used;
	int64 capacity;
	String mountpoint;
	int64 freespace;
	return getDeviceSizes(devpath, capacity, used, freespace, mountpoint);
}

bool 
DeviceMgm::getMountPoint(const String &devpath, String &mountpoint)
{
	int64 used;
	int64 capacity;
	int64 freespace;
	return getDeviceSizes(devpath, capacity, used, freespace, mountpoint);
}

