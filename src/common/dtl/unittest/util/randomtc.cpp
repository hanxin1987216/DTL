/***************************************************************************************************
random.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Compress 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-17
 ****************************************************************/

#include "randomtc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RandomTestCase);

void
RandomTestCase::setUp(void) {}

void
RandomTestCase::tearDown(void) {}

void 
RandomTestCase::testConst(void)
{
	CPPUNIT_ASSERT(Random::max_32_bit_long == _T(0xFFFFFFFFLU));
	CPPUNIT_ASSERT(Random::random_max == _T(Random::max_32_bit_long));
}

void 
RandomTestCase::testRand_double(void)
{
	//返回[0.0, 1.0]之间的双精度浮点
	Random random;
	double double_random = random.rand_double();
	CPPUNIT_ASSERT(double_random >= 0.0 && double_random<= 1.0);
}	

void
RandomTestCase::testGet_rand(void)
{
	//获得区间随机数
	CPPUNIT_ASSERT((Random::get_rand(1, 10) >= 1) && (Random::get_rand(1, 10) < 10));
	CPPUNIT_ASSERT((Random::get_rand(2, 9) >= 2) && (Random::get_rand(2, 9) < 9));
	CPPUNIT_ASSERT((Random::get_rand(3, 8) >= 3) && (Random::get_rand(3, 8) < 8));
	CPPUNIT_ASSERT((Random::get_rand(4, 7) >= 4) && (Random::get_rand(4, 7) < 7));
	CPPUNIT_ASSERT((Random::get_rand(5, 6) >= 5) && (Random::get_rand(5, 6) < 6));
}

void
RandomTestCase::testRanduint(void)
{
	//多次测试
	Random random;
	CPPUNIT_ASSERT(random.rand_uint() > 0 && random.rand_uint() < Random::random_max);CPPUNIT_ASSERT (random.rand_uint() > 0 && random.rand_uint() < Random::random_max);
	CPPUNIT_ASSERT(random.rand_uint() > 0 && random.rand_uint() < Random::random_max);CPPUNIT_ASSERT (random.rand_uint() > 0 && random.rand_uint() < Random::random_max);
	CPPUNIT_ASSERT(random.rand_uint() > 0 && random.rand_uint() < Random::random_max);CPPUNIT_ASSERT (random.rand_uint() > 0 && random.rand_uint() < Random::random_max);
	CPPUNIT_ASSERT(random.rand_uint() > 0 && random.rand_uint() < Random::random_max);CPPUNIT_ASSERT (random.rand_uint() > 0 && random.rand_uint() < Random::random_max);
}








