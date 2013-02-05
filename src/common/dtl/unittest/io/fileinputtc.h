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
		CPPUNIT_TEST_DESCRIPTION (ctors, _T("���� FileInputStream�๹�캯�� "));
		CPPUNIT_TEST_DESCRIPTION (getFileName, _T("���� FileInputStream���ȡ�ļ��� "));
		CPPUNIT_TEST_DESCRIPTION (read,  _T("���� FileInputStream������ݽӿ�"));	
		CPPUNIT_TEST_DESCRIPTION (seek,  _T("���� FileInputStream seek �ӿ�"));
		CPPUNIT_TEST_DESCRIPTION (close,  _T("���� FileInputStream�� close�ر����ӿ�"));
		CPPUNIT_TEST_DESCRIPTION (available,  _T("���� FileInputStream�� avaliableʣ��δ��������"));	
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

