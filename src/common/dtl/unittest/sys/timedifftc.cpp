/***************************************************************************************************
timedifftc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	TimeDiff 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-12
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "timedifftc.h"
const int64 USECONDSADAY = 24*60*60*1000000;

CPPUNIT_TEST_SUITE_REGISTRATION( TimeDiffTestCase );

void
TimeDiffTestCase::setUp(void) {
}

void 
TimeDiffTestCase::tearDown(void) {
}
void
TimeDiffTestCase::testGetDays(void)
{
	Date date1 (2012, 2, 21);
	Date date2 (2012, 2, 29);

	TimeDiff diff (date2.time () - date1.time ());
    CPPUNIT_ASSERT( diff.getDays() == 8);


	Date date3 (2012, 2, 21);
	TimeDiff diff3 (date3.time () - date1.time ());
    CPPUNIT_ASSERT( diff3.getDays() == 0);

}

void 
TimeDiffTestCase::testConstructor(void) {
}
