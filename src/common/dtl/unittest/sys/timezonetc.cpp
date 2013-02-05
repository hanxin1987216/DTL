/***************************************************************************************************
timezonetc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	TimeZone 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-12
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "timezonetc.h"


CPPUNIT_TEST_SUITE_REGISTRATION( TimeZoneTestCase );

void
TimeZoneTestCase::setUp(void) {
    //m_1 = const_cast<TimeZone*>(TimeZone::getCurrentTimeZone());
    m_curDate = new Date();
    m_halfDayAfter = new Date( m_curDate->time() + 12*Date::ticksPerHour);
}

void 
TimeZoneTestCase::tearDown(void) {
    //if (m_1 != NULL ) {
        //delete m_1;
    //}
    delete m_curDate;
    delete m_halfDayAfter;
}


void
TimeZoneTestCase::testGetCurrentTimeZone(void) {
    const TimeZone* tz = TimeZone::getCurrentTimeZone();
    //CPPUNIT_ASSERT( m_1 != NULL );
    CPPUNIT_ASSERT( tz!= NULL );
}

void
TimeZoneTestCase::testInDaylightTime(void) {
    Date curDate;
    const TimeZone* tz = TimeZone::getCurrentTimeZone();
    CPPUNIT_ASSERT( tz!= NULL );
    // 当前时刻和当前时刻的12小时之后总有一个应该是inDaylightTime
    CPPUNIT_ASSERT( tz->inDaylightTime(
                                    const_cast<const Date*>(m_curDate))
                    || tz->inDaylightTime(
                                    const_cast<const Date*>(m_halfDayAfter))
                    );
    
    // 当前时刻和当前时刻的12小时之后总有一个不应该是inDaylightTime
    //CPPUNIT_ASSERT( !m_1->inDaylightTime(const_cast<const Date*>(m_curDate))
     //               || !m_1->inDaylightTime(const_cast<const Date*>(m_halfDayAfter)));
    CPPUNIT_ASSERT( !tz->inDaylightTime(const_cast<const Date*>(m_curDate))
                    || !tz->inDaylightTime(const_cast<const Date*>(m_halfDayAfter)));
    
}

void
TimeZoneTestCase::testGetUTCOffset(void) {
   
    const TimeZone* tz = TimeZone::getCurrentTimeZone();
    CPPUNIT_ASSERT( tz!= NULL );
    // 我们在东8区
    CPPUNIT_ASSERT( tz->getUTCOffset(const_cast<const Date*>(m_curDate))/
                    Date::ticksPerHour == 8);
}

void 
TimeZoneTestCase::testGetDisplayName(void) {
    const TimeZone* tz = TimeZone::getCurrentTimeZone();
    CPPUNIT_ASSERT( tz!= NULL );
    // "CST"是从testcase/datetc/datetc.cpp中抄过来的
    CPPUNIT_ASSERT( tz->getDisplayName() == String("CST"));
}

