/***************************************************************************************************
localetc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Locale 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-12
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "localetc.h"


CPPUNIT_TEST_SUITE_REGISTRATION( LocaleTestCase );

void
LocaleTestCase::setUp(void) {
}

void 
LocaleTestCase::tearDown(void) {
    Locale::setCurrentLocale(Locale::findLocale(CHINA));
}


void
LocaleTestCase::testToStringSet(void) {
    //locale string "zh_CN","en_US" get from dtl/sys/locale.cpp
    //only test three, need all test?
    Locale loc(CHINA);
    CPPUNIT_ASSERT(loc.toString() == String(_T("zh_CN")) );
    CPPUNIT_ASSERT(loc.getCountry() == String(_T("CN") ));
    CPPUNIT_ASSERT(loc.getLanguage() == String(_T("zh") ));
    CPPUNIT_ASSERT(loc.getRegion() == String(_T("")) );
    CPPUNIT_ASSERT(loc.getLocaleCode() == CHINA );
    CPPUNIT_ASSERT(loc.getNativeName() == String(_T("简体中文 (中华人民共和国)")));
    CPPUNIT_ASSERT(loc.getEnglishName() == String(_T("Chinese (People's Republic of China)")));
    CPPUNIT_ASSERT(loc.getDisplayName() == String(_T("IDS_CHINA_LOCALE_NAME")));


    Locale loc2(UNITED_STATES);
    CPPUNIT_ASSERT(loc2.toString() == String(_T("en_US")) );
    CPPUNIT_ASSERT(loc2.getCountry() == String(_T("US")) );
    CPPUNIT_ASSERT(loc2.getLanguage() == String(_T("en")) );
    CPPUNIT_ASSERT(loc2.getRegion() == String(_T("")) );
    CPPUNIT_ASSERT(loc2.getLocaleCode() == UNITED_STATES);
    CPPUNIT_ASSERT(loc2.getNativeName() == String(_T("English (United States)")));
    CPPUNIT_ASSERT(loc2.getEnglishName() == String(_T("English (United States)")));
    CPPUNIT_ASSERT(loc2.getDisplayName() == String(_T("IDS_UNITED_STATES_LOCALE_NAME")));
    CPPUNIT_ASSERT(loc2.getDisplayName(&loc) == String(_T("IDS_CHINA_LOCALE_NAME"))
            || loc2.getDisplayName(&loc) == String(_T("IDS_UNITED_STATES_LOCALE_NAME")));

    Locale loc3(TAIWAN);
    //printf("**%s**\n",loc3.getNativeName().getCStr());
    CPPUNIT_ASSERT(loc3.toString() == String(_T("zh_TW_CN")) );
    CPPUNIT_ASSERT(loc3.getCountry() == String(_T("CN")) );
    CPPUNIT_ASSERT(loc3.getLanguage() == String(_T("zh")) );
    CPPUNIT_ASSERT(loc3.getRegion() == String(_T("TW")) );
    CPPUNIT_ASSERT(loc3.getLocaleCode() == TAIWAN );
    //CPPUNIT_ASSERT(loc3.getNativeName() == String(_T("\x7e41\x9a44\x4e2d\x6587 (\x81fa\x7063)")));
    CPPUNIT_ASSERT(loc3.getEnglishName() == String(_T("Chinese (Taiwan)")));
    CPPUNIT_ASSERT(loc3.getDisplayName() == String(_T("IDS_TAIWAN_LOCALE_NAME")));
}

void
LocaleTestCase::testGetLocale(void) {
    const Locale *curLocale = Locale::getCurrentLocale();
    CPPUNIT_ASSERT(curLocale != NULL);
    //current locale should be china
    CPPUNIT_ASSERT(curLocale->getLocaleCode() == CHINA);

    const Locale *usLocale = Locale::getUSLocale();
    CPPUNIT_ASSERT(usLocale != NULL);
    CPPUNIT_ASSERT(usLocale->getLocaleCode() == UNITED_STATES);

    const Locale *chnLocale = Locale::getChinaLocale();
    CPPUNIT_ASSERT(chnLocale != NULL);
    CPPUNIT_ASSERT(chnLocale->getLocaleCode() == CHINA);

}


void
LocaleTestCase::testGetAllLocale(void) {
    vector<const Locale*> allLocales = vector<const Locale*>();
    Locale::getAllLocales(allLocales);
    for(vector<const Locale*>::iterator it = allLocales.begin()
            ;it != allLocales.end()
            ;++it) {
        CPPUNIT_ASSERT((*it)->getLocaleCode());
    }
}

void
LocaleTestCase::testSetCurrentLocale() {
    //assume currentLocale is CHINA
    const Locale *prevCurloc= Locale::getCurrentLocale();
    //Locale usLoc = Locale(UNITED_STATES);
    const Locale *usLoc = Locale::getUSLocale();
    //Locale::setCurrentLocale( const_cast<const Locale*>(&usLoc));
    Locale::setCurrentLocale( usLoc);
    const Locale *nextCurloc = Locale::getCurrentLocale();
    CPPUNIT_ASSERT(prevCurloc != nextCurloc);
    CPPUNIT_ASSERT(prevCurloc->getLocaleCode() != nextCurloc->getLocaleCode());
    //put CHINA back or it will caused some issue
    Locale::setCurrentLocale(prevCurloc);
}

void
LocaleTestCase::testFindLocale() {
    const Locale *chnLoc = Locale::findLocale(CHINA);
    CPPUNIT_ASSERT(chnLoc != NULL);
    CPPUNIT_ASSERT(chnLoc->getLocaleCode() == CHINA);

    const Locale *usLoc = Locale::findLocale(UNITED_STATES);
    CPPUNIT_ASSERT(usLoc != NULL);
    CPPUNIT_ASSERT(usLoc->getLocaleCode() == UNITED_STATES);

    const Locale *hkLoc = Locale::findLocale(HONG_KONG);
    CPPUNIT_ASSERT(hkLoc != NULL);
    CPPUNIT_ASSERT(hkLoc->getLocaleCode() == HONG_KONG);
}


void
LocaleTestCase::testSetSystemDefaultLocale() {
    //assume default is CHINA
    const Locale *defloc = Locale::getCurrentLocale();
    const Locale *usloc = Locale::findLocale(UNITED_STATES);
    Locale::setSystemDefaultLocale(usloc);
    CPPUNIT_ASSERT(defloc->getLocaleCode() != Locale::getCurrentLocale()->getLocaleCode());
    CPPUNIT_ASSERT(Locale::getCurrentLocale()->getLocaleCode() == UNITED_STATES);
    Locale::setSystemDefaultLocale(defloc);
}

void
LocaleTestCase::testIsOfficialLanguage() {
    Locale loc = Locale(CHINA, "en", true);
    const Locale *chnLoc = Locale::getChinaLocale();
    CPPUNIT_ASSERT(loc.getLanguage() == "en");
    CPPUNIT_ASSERT(loc.isOfficialLanguage() == true);
    CPPUNIT_ASSERT(const_cast<Locale*>(chnLoc)->isOfficialLanguage() == true);
    Locale loc2 = Locale(CHINA, "zh", true);
    CPPUNIT_ASSERT(loc2.isOfficialLanguage() == true);
}
