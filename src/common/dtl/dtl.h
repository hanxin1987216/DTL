/***************************************************************************************************
dtl.h:	
	Public Header
	Copyright (c) Datatom Software, Inc.(2004 - 2008), All rights reserved

Purpose:
	dtl head file
	
Author:
	韩欣

Creating Time:
	2011-12-2
***************************************************************************************************/

#ifndef __DTL_HEAD_H__
#define __DTL_HEAD_H__

#include <dtl/mono_base/uglify.h>

#include <dtl/prec.h>

//
// lang
//
#include <dtl/lang/string.h>
#include <dtl/lang/int.h>
#include <dtl/lang/int64.h>
#include <dtl/lang/char.h>
#include <dtl/lang/uint.h>


// 
// sys
//
#include <dtl/sys/exception.h>
#include <dtl/sys/errorprovider.h>
#include <dtl/sys/lockfile.h>
#include <dtl/sys/timer.h>
#include <dtl/sys/date.h>
#include <dtl/sys/locale.h>
#include <dtl/sys/timezone.h>
#include <dtl/sys/dateformat.h>
#include <dtl/sys/date.h>
#include <dtl/sys/process.h>
#include <dtl/sys/lock.h>
#include <dtl/sys/timediff.h>
#include <dtl/sys/daemon.h>
#include <dtl/sys/thread.h>
#include <dtl/sys/library.h>
#include <dtl/sys/slog.h>
#include <dtl/sys/env.h>
#include <dtl/sys/runtime.h>
#include <dtl/sys/signal_handler.h>



//
// io
//
#include <dtl/io/path.h>
#include <dtl/io/comdef.h>
#include <dtl/io/basefile.h>
#include <dtl/io/file.h>
#include <dtl/io/directory.h>
#include <dtl/io/streamwriter.h>
#include <dtl/io/streamreader.h>
#include <dtl/io/filestream.h>
#include <dtl/io/fileinputstream.h>
#include <dtl/io/fileoutputstream.h>
#include <dtl/io/volume.h>
#include <dtl/io/filetool.h>


//
// security
//
#include <dtl/security/base16.h>
#include <dtl/security/base64.h>
#include <dtl/security/rijndael.h>
#include <dtl/security/encrypt.h>
#include <dtl/security/md5.h>
#include <dtl/security/rc4.h>




//
// log
//
#include <dtl/log/log.h>

//
// util
//
#include <dtl/util/resreader.h>
#include <dtl/util/guid.h>
#include <dtl/util/gzcompress.h>
#include <dtl/util/random.h>
#include <dtl/util/singleton.h>
#include <dtl/util/hash.h>
#include <dtl/util/util.h>
#include <dtl/util/linenoise.h>
#include <dtl/util/performance.h>
#include <dtl/util/devicemgm.h>



//
// config
//
#include <dtl/config/tinyxml/tinyxml.h>
#include <dtl/rude/rudeconfig/ConfigImpl.h>
#include <dtl/config/configfile.h>


//
// net
//
#include <dtl/net/httpsocket.h>
#include <dtl/net/json.h>
#include <dtl/net/jsontextwriter.h>
#include <dtl/net/bson.h>
#include <dtl/net/bcon.h>
#include <dtl/net/smtp.h>

#include <dtl/net/cgiutil.h>
#include <dtl/net/cgiexcept.h>
#include <dtl/net/cgi.h>



//version
#include <dtl/version.h>


extern IResourceReader* dtlResReader;



/**
 * Duplicate from String object to C-sytle string.
 *
 * @param str	String object to duplicate.
 * @return C-style string, terminating char is 'Null'.
 */
inline tchar_t* 
dupString (const String& str)
{
	tchar_t* wcstr = new tchar_t[str.getLength () + 1];
#ifdef __WINDOWS__
	::wcscpy (wcstr, str.getCStr ());
#else
	::strcpy (wcstr, str.getCStr ());
#endif
	
	return wcstr;
}

/**
 * 使用二分法从数组中查找指定条件的对象。
 * 
 * @return 返回该对象在数组中的位置，如果未找到，返回数组的最后位置。
 */
template<class Iterator, class Pred>
inline Iterator
binary_find (Iterator first, Iterator last, Pred pred)
{
	size_t count = std::distance (first, last);	
	for (; 0 < count; ) {	
		size_t count2 = count / 2;
		Iterator mid = first;
		std::advance (mid, count2);

		if (pred (*mid))
			first = ++mid, count -= count2 + 1;
		else
			count = count2;
	}

	return first;
}


/**
 * Auto allocate for array, delete it when destruct.
 */
template<typename T>
struct auto_array_ptr
{
	auto_array_ptr (void)
		: ptr (0)
	{
	}
	
	~auto_array_ptr (void)
	{
		delete [] ptr;
	}
	
	void alloc (size_t size)
	{
		if (ptr != 0)
			delete [] ptr;
			
		ptr = new T[size];
	}
	
	T* ptr;
	
}; // End struct auto_array_ptr





/**
*  初始化 DTL 库，使用DTL库之前必须先调用此函数，只需要调用一次即可
*/
void InitDTLibrary (void);

// load res
#define LOAD_STR(IDS)				\
		dtlResReader->loadString (IDS)
	
		
//safe delete		
#define DSAFE_DELETE(x) { if (NULL != x) { delete(x); (x) = NULL; } }
#define DSAFE_DELETE_ARR(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }


// safe free
#define DSAFE_FREE(x) { if (NULL != x) { free(x); (x) = NULL; } }


// timespan
#define INIT_TIME 	struct timeval time1,time2;
#define START_TIME 	gettimeofday(&time1,NULL);
#define STOP_TIME   gettimeofday(&time2,NULL); 
#define PRINT_TIME  cout<<"Time:"<<time2.tv_sec-time1.tv_sec<<"s: "<<time2.tv_usec-time1.tv_usec<<endl;

#endif // __DTL_HEAD_H__
