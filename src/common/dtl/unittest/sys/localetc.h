/***************************************************************************************************
localetc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Locale 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-13
***************************************************************************************************/
#ifndef __LOCALE_TC_H__
#define __LOCALE_TC_H__

#include <cppunit/tester.h>


class LocaleTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (LocaleTestCase);

		CPPUNIT_TEST_DESCRIPTION (testToStringSet, _T("测试Locale, toString, getCountry, getLanguage, getRegion, getXXXXName系列是否返回正确String"));	
		CPPUNIT_TEST_DESCRIPTION (testGetLocale, _T("测试Locale, getXXXXLocal系列是否返回正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetAllLocale, _T("测试Locale, getAllLocal是否返回正确"));	
		CPPUNIT_TEST_DESCRIPTION (testSetCurrentLocale, _T("测试Locale, setCurrentLocale是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testSetSystemDefaultLocale, _T("测试Locale, setSystemDefaultLocale是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testFindLocale, _T("测试Locale, findLocale是否返回正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsOfficialLanguage, _T("测试Locale, isOfficialLanguage是否返回正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
	void testToStringSet(void);
    void testGetLocale(void);
    void testGetAllLocale(void);
    void testSetCurrentLocale(void);
    void testFindLocale(void);
    void testSetSystemDefaultLocale(void);
    void testIsOfficialLanguage(void);
private:
}; // End class LocaleTestCase

#endif // __LOCALE_TC_H__

