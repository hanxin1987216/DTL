/***************************************************************************************************
random.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Compress 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-17
 ****************************************************************/
#ifndef __RANDOM_TC_H__
#define __RANDOM_TC_H__

#include <cppunit/tester.h>

class RandomTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (RandomTestCase);

	CPPUNIT_TEST_DESCRIPTION(testConst, _T("测试testConst, 测试static const"));
	CPPUNIT_TEST_DESCRIPTION(testRand_double, _T("测试rand_double, 返回[0.0, 1.0]之间的双精度浮点是否正确"));
	CPPUNIT_TEST_DESCRIPTION(testGet_rand, _T("测试testGetrand, 测试const"));
	CPPUNIT_TEST_DESCRIPTION(testRanduint, _T("测试testRanduint, 测试Randuint"));
	
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testRand_double(void);
	void testConst(void);
	void testGet_rand(void);
	void testRanduint(void);
	
	
private:

};

#endif //end  __RANDOM_TC_H__
