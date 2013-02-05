/***************************************************************************************************
fileoutputtc.h:	
	Copyright (c) Datatom Software, Inc.(2004 - 2009), All rights reserved

Purpose:
	 Unit Test code for class cpp::io::FileOutputStream


Author:
	hanxin
Creating Time:
	2008.5.21
***************************************************************************************************/


#ifndef __FILEOUTPUTTC_H__
#define __FILEOUTPUTTC_H__

#include <cppunit/tester.h>


class FileOutputStreamTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (FileOutputStreamTestCase);
		CPPUNIT_TEST_DESCRIPTION (ctors, _T("测试 FileOutputStream 的构造函数"));
		CPPUNIT_TEST_DESCRIPTION (write, _T("测试 FileOutputStream write 接口"));	
		CPPUNIT_TEST_DESCRIPTION (seek, _T("测试 FileOutputStream seek 接口"));
		CPPUNIT_TEST_DESCRIPTION (close, _T("测试 FileOutputStream close 文件句柄关闭接口"));
		CPPUNIT_TEST_DESCRIPTION (flush, _T("测试 FileOutputStream flush 刷新文件缓存接口"));	
		CPPUNIT_TEST_DESCRIPTION (getCurrentOffset, _T("测试 FileOutputStream getCurrentOffset 获得当前偏移量接口"));	
		
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);	
	
	void tearDown (void);
	
	
protected:
	void ctors (void);
	void write (void);
	void seek (void);
	void close (void);	
	void flush (void);	
	void getCurrentOffset (void);
}; // End class FileOutputStreamTestCase


#endif // __FILEOUTPUTTC_H__

