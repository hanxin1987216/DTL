/***************************************************************************************************
timedifftc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	TimeDiff 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-12
***************************************************************************************************/
#ifndef __TIME_DIFF_TC_H__
#define __TIME_DIFF_TC_H__

#include <cppunit/tester.h>


class TimeDiffTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (TimeDiffTestCase);

		CPPUNIT_TEST_DESCRIPTION (testGetDays, _T("测试TimeDiff, getDays 返回是否正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
	void testGetDays(void);
	void testConstructor(void);
private:
    TimeDiff * m_1;
    TimeDiff * m_2;
    TimeDiff * m_3;
}; // End class TimeDiffTestCase

#endif // __TIME_DIFF_TC_H__

