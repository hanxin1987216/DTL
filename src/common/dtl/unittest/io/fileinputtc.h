/***************************************************************************************************
fileinputtc.cpp:	
	Copyright (c) Datatom Software, Inc.(2004 - 2009), All rights reserved

Purpose:
	 Unit Test code for class cpp::io::FileInputStream


Author:
	hanxin
Creating Time:
	2008.5.21
***************************************************************************************************/


#ifndef __FILEINPUTTC_H__
#define __FILEINPUTTC_H__
#include <cppunit/tester.h>

class FileInputStreamTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (FileInputStreamTestCase);
		CPPUNIT_TEST_DESCRIPTION (ctors, _T("测试 FileInputStream类构造函数 "));
		CPPUNIT_TEST_DESCRIPTION (getFileName, _T("测试 FileInputStream类获取文件名 "));
		CPPUNIT_TEST_DESCRIPTION (read,  _T("测试 FileInputStream类读数据接口"));	
		CPPUNIT_TEST_DESCRIPTION (seek,  _T("测试 FileInputStream seek 接口"));
		CPPUNIT_TEST_DESCRIPTION (close,  _T("测试 FileInputStream类 close关闭流接口"));
		CPPUNIT_TEST_DESCRIPTION (available,  _T("测试 FileInputStream类 avaliable剩余未读数据量"));	
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp();
	void tearDown ();
	
protected:
	void ctors (void);
	void getFileName (void);
	void read (void);
	void seek (void);
	void close (void);	
	void available (void);	
}; // End class FileInputStreamTestCase


#endif // __FILEINPUTTC_H__

