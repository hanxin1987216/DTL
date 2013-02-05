/***************************************************************************************************
datetc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Date 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-13
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "datetc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( DateTestCase );

void
DateTestCase::setUp(void) {
    const Locale * chnloc = Locale::findLocale(CHINA);
    Locale::setCurrentLocale(chnloc);
}

void 
DateTestCase::tearDown(void) {
}

void
DateTestCase::testToStringSet(void) {
    //const Locale *cur = Locale::getCurrentLocale();
    Locale::setCurrentLocale(Locale::getChinaLocale());
    //cout<< endl<<"TimeZone: "<<TimeZone::getCurrentTimeZone()->getDisplayName().getCStr()<<endl;
    // we are at +8 East timezone
    Date date(2002, 12, 21, 12-8, 21);
    //cout<< "FD_GENERAL_SHORT "<<date.toString(FD_GENERAL_SHORT).getCStr()<<endl;
    //cout<< "FD_GENERAL_LONG "<<date.toString(FD_GENERAL_LONG).getCStr()<<endl;
    //cout<< "FD_GENERAL_FULL "<<date.toString(FD_GENERAL_FULL).getCStr()<<endl;
    CPPUNIT_ASSERT(date.toString(FD_GENERAL_SHORT) == String(_T("2002-12-21 12:21")));
    CPPUNIT_ASSERT(date.toString(FD_GENERAL_LONG) 
                   == String(_T("2002年12月21日 12:21:00")));
    CPPUNIT_ASSERT(date.toString(FD_GENERAL_FULL) 
                   == String(_T("2002年12月21日 12:21:00")));

    CPPUNIT_ASSERT(date.toTimeString(TP_SHORT) == String(_T("12:21")));
    CPPUNIT_ASSERT(date.toTimeString(TP_LONG) == String(_T("12:21:00")));

    //cout<<endl<< cur->getLanguage().getCStr()<<"--"<<date.toDateString(DP_LONG).getCStr()<<endl;
    CPPUNIT_ASSERT(date.toDateString(DP_LONG) == String(_T("2002年12月21日")));
    CPPUNIT_ASSERT(date.toDateString(DP_SHORT) == String(_T("2002-12-21")));
    CPPUNIT_ASSERT(date.toDateString(DP_MONTH_DAY) == String(_T("十二月21日")));
    CPPUNIT_ASSERT(date.toDateString(DP_YEAR_MONTH) == String(_T("2002年十二月")));
}

void
DateTestCase::testTime(void) {
    Date date = Date( 1024 * Date::ticksPerDay);
    CPPUNIT_ASSERT(date.time() == 1024 * Date::ticksPerDay);

    date.time(100);
    CPPUNIT_ASSERT(date.time() == 100);
}

void
DateTestCase::testGetLocalTime(void) {

}

void
DateTestCase::testSetLocalTime(void) {


}

void
DateTestCase::testToUIntSet(void) {
    Locale::setCurrentLocale(Locale::getChinaLocale());
    // we are at +8 East timezone
    Date date(2002, 12, 21, 12-8, 21);
    CPPUNIT_ASSERT(date.getYear() == 2002);
    CPPUNIT_ASSERT(date.getMonth() == 12);
    CPPUNIT_ASSERT(date.getDay() == 21);
    CPPUNIT_ASSERT(date.getDayOfYear() == 355);
    CPPUNIT_ASSERT(date.getDayOfWeek() == 6);
    CPPUNIT_ASSERT(date.getMinutes() == 21);
    CPPUNIT_ASSERT(date.getHours() == 4);
    CPPUNIT_ASSERT(date.getSeconds() == 0);
    CPPUNIT_ASSERT(date.timeOfDay() == __INT64_C(15660000000));
    //printf("\ngetDayOfYear:%d",date.getDayOfYear());
    //printf("\ngetDayOfWeek:%d",date.getDayOfWeek());
    //printf("\ngetMinutes:%d",date.getMinutes());
    //printf("\ngetHours:%d",date.getHours());
}

void
DateTestCase::testAddDays(void) {
    Locale::setCurrentLocale(Locale::getChinaLocale());
    // we are at +8 East timezone
    Date date(2002, 12, 21, 12-8, 21);
    date.addDays(2);
    CPPUNIT_ASSERT(date.getDay() == 23);
}

void
DateTestCase::testAddHours(void) {
    Locale::setCurrentLocale(Locale::getChinaLocale());
    // we are at +8 East timezone
    Date date(2002, 12, 21, 12-8, 21);
    date.addHours(2);
    CPPUNIT_ASSERT(date.getHours() == 6);
}

void
DateTestCase::testSubtract(void) {
    Locale::setCurrentLocale(Locale::getChinaLocale());
    // we are at +8 East timezone
    Date dateP(2002, 12, 21, 12-8, 21);
    Date dateN(2002, 12, 24, 12-8, 21);
    TimeDiff diff = dateP.subtract(dateN);
    CPPUNIT_ASSERT(diff.getDays() == -3);
}

void
DateTestCase::testAdd(void) {
    Locale::setCurrentLocale(Locale::getChinaLocale());
    // we are at +8 East timezone
    Date dateP(2002, 12, 21, 12-8, 21);
    Date dateN(20*Date::ticksPerDay);
    TimeDiff diff = dateP.add(dateN);
    //printf("\ndiff.getDays():%d",diff.getDays());
    CPPUNIT_ASSERT(diff.getDays() == dateP.time()/Date::ticksPerDay + 20);
}

void
DateTestCase::testGetCurrentTime(void) {
    // Date() implement by call Date::getCurrentTime()
    // so it's a useless test here
    Date date; 
    int64 delta = Date::getCurrentTime() - date.time();
    CPPUNIT_ASSERT(delta < Date::ticksPerSecond );
}

void
DateTestCase::testIsLeapYear(void) {
    CPPUNIT_ASSERT(Date::isLeapYear(2000) == true);
    CPPUNIT_ASSERT(Date::isLeapYear(1900) == false);
    CPPUNIT_ASSERT(Date::isLeapYear(2008) == true);
    CPPUNIT_ASSERT(Date::isLeapYear(2009) == false);
}

void
DateTestCase::testParse(void) {


}
