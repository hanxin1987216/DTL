/***************************************************************************************************
datetc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Date 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-13
***************************************************************************************************/
#ifndef __DATE_TC_H__
#define __DATE_TC_H__

#include <cppunit/tester.h>


class DateTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (DateTestCase);

		CPPUNIT_TEST_DESCRIPTION (testToStringSet, _T("测试Date, toString, toXXXXString返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testTime, _T("测试Date, time是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetLocalTime, _T("测试Date, getLocalTime是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testSetLocalTime, _T("测试Date, setLocalTime是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testToUIntSet, _T("测试Date, getYear, getMonth, getDay, getDayofYear, getHours, getMinutes, getSeconds, getDayOfWeek, timeOfDay是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testAddDays, _T("测试Date, addDays是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testAddHours, _T("测试Date, addHours是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testSubtract, _T("测试Date, subtract是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testAdd, _T("测试Date, add是否正确"));	

        //static methods
		CPPUNIT_TEST_DESCRIPTION (testGetCurrentTime, _T("测试Date, getCurrentTime是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsLeapYear, _T("测试Date, isLeapYear是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testParse, _T("测试Date, parse是否正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
	void testToStringSet(void);
    void testToUIntSet(void);
    void testGetCurrentTime(void);
    void testIsLeapYear(void);
    void testParse(void);
    void testTime(void);
    void testAddDays(void);
    void testAddHours(void);
    void testSubtract(void);
    void testAdd(void);

    /**these functions have not implement 
     * list them here
     */
    void testGetLocalTime(void);
    void testSetLocalTime(void);
private:
}; // End class DateTestCase

#endif // __DATE_TC_H__

