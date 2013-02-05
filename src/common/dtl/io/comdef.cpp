/***************************************************************************************************
comdef.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	DTL IO 公共定义文件 常用函数实现

Author:
	韩欣

Creating Time:
	2012-1-10
***************************************************************************************************/

#include "../prec.h"
#include <assert.h>
#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "../sys/exception.h"


#ifndef __WINDOWS__
	#include <sys/stat.h>
	#include <unistd.h>
	#include <fcntl.h>
#endif

#include "comdef.h"

//
// 检查 stat (...) 错误值
//
String checkStatResult (int result)
{
	switch (result) {
		case ENOENT:
			return "文件不存在";
			break;
		case ENOTDIR:
			return "路径中的目录存在但却非真正的目录";
			break;
		case ELOOP:
			return "打开的文件有过多符号连接问题，上限为16符号连接";
			break;
		case EFAULT:
			return "参数buf为无效指针，指向无法存在的内存空间";
			break;
		case ENOMEM:
			return "核心内存不足";
			break;
		case ENAMETOOLONG:
			return "路径名称太长";
			break;
		default:
			break;
	}

	return String::EMPTY;
}


unsigned int 
daysInMonth (unsigned int year, unsigned int month)
{
	unsigned int day = days_of_month[month];

	if (isleap (year) && month == 2)
		day++;

	return day;
}

/**
 * Number of micro-seconds between the beginning of the Windows epoch
 * (Jan. 1, 1601) and the Unix epoch (Jan. 1, 1970) 
 */
static const int64 deltaEpochInUnix = __INT64_C(11644473600000000);



// For time
void 
fileTimeToTime (int64 *result, const WapiFileTime *input)
{
    // Convert FILETIME to 64 bit number so that we can work with it. 
    *result = input->dwHighDateTime;
    *result = (*result) << 32;
    *result |= input->dwLowDateTime;
	// Convert from 100 nano-sec periods to micro-seconds. 
    *result /= 10;    
	// Convert from Windows epoch to Unix epoch 
    *result -= deltaEpochInUnix;  
}

void 
timeToFileTime (WapiFileTime* pft, const int64& t)
{
    int64 ll = (int64)t;

    ll += deltaEpochInUnix;
    ll = ll * 10;
    pft->dwLowDateTime = (unsigned)ll;
    pft->dwHighDateTime = (unsigned) (ll >> 32);
}




FileAttributes
loadFileAttributes (const tchar_t* file)
{
	return (FileAttributes) GetFileAttributes (file);
}




int 
convertFileShare (FileShare share)
{
	switch(share) {
	case NONE_SHARE:
		return 0;

	case READ_SHARE:
		return FILE_SHARE_READ;

	case WRITE_SHARE:
		return FILE_SHARE_WRITE;

	case READ_WRITE_SHARE:
		return FILE_SHARE_READ|FILE_SHARE_WRITE;

	//case FS_INHERITABLE:
	default:
		assert (false);
		break;		
	}
		
	//TODO: what we return?
	return 0;
}

int
convertFileMode (FileMode mode)
{
	switch(mode) {
	case CREATE_NEW_MODE:
		return CREATE_NEW;

	case CREATE_MODE:
		return CREATE_ALWAYS;

	case OPEN_MODE:
		return OPEN_EXISTING;

	case OPEN_OR_CREATE_MODE:
		return OPEN_ALWAYS;

	case TRUNCATE_MODE:
		return TRUNCATE_EXISTING;

	case APPEND_MODE:
		return OPEN_ALWAYS;

	default:
		assert (false);
		break;
	}
		
	//TODO: what we return?
	return OPEN_EXISTING;
}

int
convertSeekOrigin (SeekOrigin origin)
{
	switch (origin) {
	case BEGIN_ORIGIN:
		return FILE_BEGIN;

	case CURRENT_ORIGIN:
		return FILE_CURRENT;

	case END_ORIGIN: 
		return FILE_END;
	}

	// TODO: what we return?
	return FILE_BEGIN;
}