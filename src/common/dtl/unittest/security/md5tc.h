/***************************************************************************************************
md5tc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	MD5 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-18
 ****************************************************************/
#ifndef __RANDOM_TC_H__
#define __RANDOM_TC_H__

#include <cppunit/tester.h>

class Md5TestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (Md5TestCase);

		CPPUNIT_TEST_DESCRIPTION(testMd5, _T("测试testMd5, 测试多种形式的密码通过MD5转换后的正确性"));
	
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testMd5(void);
	
private:

};

#endif //end  __RANDOM_TC_H__
