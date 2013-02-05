/***************************************************************************************************
timezonetc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	TimeZone 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-12
***************************************************************************************************/
#ifndef __TIME_ZONE_TC_H__
#define __TIME_ZONE_TC_H__

#include <cppunit/tester.h>


class TimeZoneTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (TimeZoneTestCase);

		CPPUNIT_TEST_DESCRIPTION (testGetCurrentTimeZone, _T("测试TimeZone, getCurrentTimeZone 返回是否正确"));	
        CPPUNIT_TEST_DESCRIPTION (testInDaylightTime, _T("测试CurrentTimeZone, inDaylightTime  返回是否正确"));
        CPPUNIT_TEST_DESCRIPTION (testGetUTCOffset, _T("测试CurrentTimeZone, getUTCOffset  返回是否正确"));	
        CPPUNIT_TEST_DESCRIPTION (testGetDisplayName, _T("测试TimeZone, getDisplayName  返回是否正确"));

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
	void testGetUTCOffset(void);
	void testGetCurrentTimeZone(void);
    void testInDaylightTime(void);
    void testGetDisplayName(void);
private:
    TimeZone * m_1;
    Date * m_curDate, *m_halfDayAfter;
}; // End class TimeZoneTestCase

#endif // __TIME_ZONE_TC_H__

