/***************************************************************************************************
sha1.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	sha1 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-18
 ****************************************************************/
#ifndef __SHA1_TC_H__
#define __SHA1_TC_H__

#include <cppunit/tester.h>
#include <dtl/security/sha1.h>
#include <dtl/security/sha1.cpp>

class Sha1TestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (Sha1TestCase);

		CPPUNIT_TEST_DESCRIPTION(testSHA1, _T("测试testSha1, 测试多种形式的密码通过SHA1转换后的正确性"));
	
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testSHA1(void);
	void testSHA1HMACHash(void);
	
private:

};

#endif //end  __SHA1_TC_H__
