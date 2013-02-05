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
		CPPUNIT_TEST_DESCRIPTION (ctors, _T("���� FileOutputStream �Ĺ��캯��"));
		CPPUNIT_TEST_DESCRIPTION (write, _T("���� FileOutputStream write �ӿ�"));	
		CPPUNIT_TEST_DESCRIPTION (seek, _T("���� FileOutputStream seek �ӿ�"));
		CPPUNIT_TEST_DESCRIPTION (close, _T("���� FileOutputStream close �ļ�����رսӿ�"));
		CPPUNIT_TEST_DESCRIPTION (flush, _T("���� FileOutputStream flush ˢ���ļ�����ӿ�"));	
		CPPUNIT_TEST_DESCRIPTION (getCurrentOffset, _T("���� FileOutputStream getCurrentOffset ��õ�ǰƫ�����ӿ�"));	
		
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

