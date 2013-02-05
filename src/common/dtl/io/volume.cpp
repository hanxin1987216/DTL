/***************************************************************************************************
volume.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011-2012)

Purpose:
	implement class of volume

Author:
	hanxin (han.xin@datatom.com)

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

#include <sys/statfs.h>

#include "volume.h"

Volume::Volume(const String& path)
	: _path(path)
	, _capacity(0)
	, _freespace(0)
	, _fstype (UNKNOWN_TYPE)
{
	struct statfs disk_statfs;
	if(statfs(path.getCStr(), &disk_statfs) >= 0 )
	{
		_freespace = (int64)(disk_statfs.f_bfree * disk_statfs.f_bsize);;
		_capacity = (int64)(disk_statfs.f_blocks * disk_statfs.f_bsize);
	}
	
	switch (disk_statfs.f_type)
	{
		case 0xEF52:
			_fstype = EXT2_TYPE;	
		case 0xEF53:
			_fstype = EXT3_TYPE;
		case 0x58465342:
			_fstype = XFS_TYPE;
	}
}

/**
* 获得某个路径的容量
* @return
*/
int64 
Volume::getCapacity()
{
	return _capacity;
}

/**
* 获得某个路径的空余空间
* @return
*/
int64 
Volume::getFreeSpace()
{
	return _freespace;
}

/**
* 获取卷
*/
FileSystemType 
Volume::getFileSystemType()
{
	return _fstype;
}
