/***************************************************************************************************
locale.cpp:	
	C++ Foundation Library header files
	Copyright (c) DateTome Software Inc.(2012)

Purpose:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-02-07
	
	This library is free software; you can redistribute it and/or modify it under the terms of the 
 	GNU Lesser General Public License as published by the Free Software Foundation; either version 
 	2 of the License, or (at your option) any later version.  	
***************************************************************************************************/

#include "../prec.h"
#include "../mono_base/uglify.h"
#include "../mono_base/localemap.h"

#include "exception.h"
#include "lock.h"

#include <algorithm>
#include <map>


#include "locale.h"
	
struct LANGLocaleMap 
{
	int lcid;
	
	int locale;	
};

#define LLMAP_NUM		169


static const LANGLocaleMap llMap [LLMAP_NUM + 1] = {
	{0x0001, SAUDI_ARABIA},
	{0x0002, BULGARIA},
	{0x0003, CATALONIAN}, // Catalan?
	{0x0004, CHINA},
	{0x0005, CZECH},
	{0x0006, DENMARK},
	{0x0007, GERMANY},
	{0x0008, GREECE},
	{0x0009, UNITED_STATES},
	{0x000A, SPAIN},
	{0x000B, FINLAND},
	{0x000C, FRANCE},
	{0x000D, ISRAEL},
	{0x000E, HUNGARY},
	{0x000F, ICELAND},
	{0x0010, ITALY},
	{0x0011, JAPAN},
	{0x0012, KOREA},
	{0x0013, NETHERLANDS},
	{0x0014, NORWAY},
	{0x0015, POLAND},
	{0x0016, PORTUGAL},
	{0x0018, ROMANIA},
	{0x0019, RUSSIAN},
	{0x001A, CROATIA},
	{0x001B, SLOVAKIA},
	{0x001C, ALBANIA},
	{0x001D, SWEDEN},
	{0x001E, THAILAND},
	{0x001F, TURKEY},
	{0x0021, INDONESIA},
	{0x0022, UKRAINE},
	{0x0023, BYELORUSSIA},
	{0x0024, SLOVENIA},
	{0x0025, ESTONIA},
	{0x0026, LATVIA},
	{0x0027, LITHUANIA},
	{0x0029, IRAN},
	{0x002A, VIET_NAM},
	{0x002B, ARMENIA},
	{0x002D, SPAIN},
	{0x002F, MACEDONIA},
	{0x0036, SOUTH_AFRICA},
	{0x0038, FAEROE_ISLANDS},
	{0x0039, INDIA},
	{0x0041, KENYA},
	{0x0047, INDIA},
	{0x0049, INDIA},
	{0x004A, INDIA},
	{0x004B, INDIA},
	{0x004E, INDIA},
	{0x0056, SPAIN},
	{0x0057, INDIA},
	{0x0401, SAUDI_ARABIA},
	{0x0402, BULGARIA},
	{0x0403, CATALONIAN}, // Catalan?
	{0x0404, TAIWAN},
	{0x0405, CZECH},	
	{0x0406, DENMARK},
	{0x0407, GERMANY},
	{0x0408, GREECE},
	{0x0409, UNITED_STATES},
	{0x040B, FINLAND},
	{0x040C, FRANCE},
	{0x040D, ISRAEL},
	{0x040E, HUNGARY},
	{0x040F, ICELAND},
	{0x0410, ITALY},
	{0x0411, JAPAN},
	{0x0412, KOREA},
	{0x0413, NETHERLANDS},
	{0x0414, NORWAY},
	{0x0415, POLAND},
	{0x0416, BRAZIL},
	{0x0418, ROMANIA},
	{0x0419, RUSSIAN},
	{0x041A, CROATIA},
	{0x041B, SLOVAKIA},
	{0x041C, ALBANIA},
	{0x041D, SWEDEN},
	{0x041E, THAILAND},
	{0x041F, TURKEY},
	{0x0421, INDONESIA},
	{0x0422, UKRAINE},
	{0x0423, BYELORUSSIA},
	{0x0424, SLOVENIA},
	{0x0425, ESTONIA},
	{0x0426, LATVIA},
	{0x0427, LITHUANIA},
	{0x0429, IRAN},
	{0x042A, VIET_NAM},
	{0x042B, ARMENIA},	
	{0x042D, SPAIN},
	{0x042F, MACEDONIA},
	{0x0436, SOUTH_AFRICA},
	{0x0438, FAEROE_ISLANDS},
	{0x0439, INDIA},
	{0x0441, KENYA},
	{0x0447, INDIA},
	{0x0449, INDIA},
	{0x044A, INDIA},
	{0x044B, INDIA},
	{0x044E, INDIA},
	{0x0456, SPAIN},
	{0x0457, INDIA},
	{0x0801, IRAQ},
	{0x0804, CHINA},
	{0x0807, SWITZERLAND},
	{0x0809, UNITED_KINGDOM},
	{0x080A, MEXICO},
	{0x080C, BELGIUM},
	{0x0810, SWITZERLAND},
	{0x0813, BELGIUM},
	{0x0814, NORWAY},
	{0x0816, PORTUGAL},
	{0x081D, SWEDEN},
	{0x0C01, EGYPT},
	{0x0C04, HONG_KONG},
	{0x0C07, AUSTRIA},
	{0x0C09, AUSTRALIA},
	{0x0C0A, SPAIN},
	{0x0C0C, CANADA},
	{0x1001, LIBYAN},
	{0x1004, SINGAPORE},
	{0x1007, LUXEMBOURG},
	{0x1009, CANADA},
	{0x100A, GUATEMALA},
	{0x100C, SWITZERLAND},
	{0x1401, ALGERIA},
	{0x1404, MACAO},
	{0x1407, LIECHTENSTEIN},
	{0x1409, NEW_ZEALAND},
	{0x140A, COSTA_RICA},
	{0x140C, LUXEMBOURG},
	{0x1801, MOROCCO},
	{0x1809, IRELAND},
	{0x180A, PANAMA},
	{0x180C, MONACO},
	{0x1C01, TUNISIA},
	{0x1C09, SOUTH_AFRICA},
	{0x1C0A, DOMINICAN},
	{0x2001, OMAN},
	{0x2009, JAMAICA},
	{0x200A, VENEZUELA},
	{0x2401, YEMEN},
	{0x240A, COLOMBIA},
	{0x2801, SYRIAN_ARAB_REPUBLIC},
	{0x2809, BELIZE},
	{0x280A, PERU},
	{0x2C01, JORDAN},
	{0x2C09, TRINIDAD_TOBAGO},
	{0x2C0A, ARGENTINA},
	{0x3001, LEBANON},
	{0x3009, ZIMBABWE},
	{0x300A, ECUADOR},
	{0x3401, KUWAIT},
	{0x3409, PHILIPPINES},
	{0x340A, CHILE},
	{0x3801, UNITED_ARAB_EMIRATES},
	{0x380A, URUGUAY},
	{0x3C01, BAHRAIN},
	{0x3C0A, PARAGUAY},
	{0x4001, QATAR},
	{0x400A, BOLIVIA},
	{0x440A, EL_SALVADOR},
	{0x480A, HONDURAS},
	{0x4C0A, NICARAGUA},
	{0x500A, PUERTO_RICO},
	{0x7C04, TAIWAN},
	{0, 0}
};

/**
 * Table to store the locale data. The data includes country code(ISO-3166), 
 * 	region code(ISO-3166), language code(ISO-639). If the data is null that means
 * 	we still not implemented for this locale.
 *
 * <p> A locale data consists with: 
 *			TWO-LETTERS country code \0
 *			TWO-LETTERS region code  \0
 *			two-letters language code \0
 *			Full english name with format "Language ([Region, ]Country)" \0
 *			Full native name with format "Language ([Region, ]Country)"
 */
static const wchar_t* globalLocaleData [LOCALE_CODE_MAX] = 
{
// 	0		1		2		3		4		5		6		7		8		9
	0,		0,		0,		0,		0,		0,		0,		0,	
	L"AL\0\0sq\0Albanian (People's Socialist Republic of Albania)\0shqipe (Shqip\xc3\xabria)",		0,			// 10
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 20
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 30
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 40
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 50
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 60
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 70
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 80
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 90
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 100
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 110
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 120
	0,		0,		0,		0,		
	L"CA\0\0en\0English (Canada)\0English (Canada)",		
	0,		0,		0,		0,		0,			// 130
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 140
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 150
	0,		0,		0,		0,		0,		0,		
	L"CN\0\0zh\0Chinese (People's Republic of China)\0\x7b80\x4f53\x4e2d\x6587 (\x4e2d\x534e\x4eba\x6c11\x5171\x548c\x56fd)",
	0,		
	L"CN\0TW\0zh\0Chinese (Taiwan)\0\x7e41\x9ad4\x4e2d\x6587 (\x81fa\x7063)",		0,			// 160
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 170
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 180
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 190
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 200
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 210
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 220
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 230
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 240
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 250
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 260
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 270
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 280
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 290
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 300
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 310
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 320
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 330
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 340
	0,		0,		0,		0,		
	L"CN\0HK\0zh\0Chinese (Hong Kong S.A.R. PRC)\0\x7e41\x9ad4\x4e2d\x6587 (\x4e2d\x570b\x9999\x6e2f)",
	0,		0,		0,		0,		0,			// 350
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 360
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 370
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 380
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 390
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 400
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 410
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 420
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 430
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 440
	0,		0,		0,		0,		0,		0,		
	L"CN\0MO\0zh\0Chinese (Macao S.A.R. PRC)\0\x7e41\x9ad4\x4e2d\x6587 (\x4e2d\x570b\x6fb3\x9580)",		
	0,		0,		0,			// 450
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 460
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 470
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 480
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 490
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 500	
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 510
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 520
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 530
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 540
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 550
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 560
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 570
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 580
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 590
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 600
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 610
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 620
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 630
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 640
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 650
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 660
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 670
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 680
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 690
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 700
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 710
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 720
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 730
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 740
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 750
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 760
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 770
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 780
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 790
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 800
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 810
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 820
	0,		0,		0,		0,		0,		0,		
	L"GB\0\0en\0English (United Kingdom)\0English (United Kingdom)",
	0,		0,		0,			// 830
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 840
	L"US\0\0en\0English (United States)\0English (United States)",		
	0,		0,		0,		0,		0,		0,		0,		0,		0,			// 850
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 860
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 870
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 880
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 890
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,			// 900
};

const wchar_t* toNullChar (const wchar_t* ptr)
{
	while (*ptr != 0)
		ptr++;
		
	return ptr;
}

inline const wchar_t* 
getCountryCode (LocaleCode code)
{
	// The country code always be the first characters at the locale code data.
	return globalLocaleData[code];
}

inline void
getRegionCode (LocaleCode code, String& region)
{
	const wchar_t* localeCode = globalLocaleData[code];
	
	if (localeCode != 0) {
		const wchar_t* beginRegionCode = toNullChar (localeCode);
		const wchar_t* endRegionCode = toNullChar (++beginRegionCode);
		
		if (endRegionCode > beginRegionCode) {
#ifdef __WINDOWS__
			region.assign (beginRegionCode, endRegionCode - beginRegionCode);
#else
			glong wsize = 0;
	#if (__SIZEOF_WCHAR__ == 4)
			gunichar2* unichar2BeginRegionCode = g_ucs4_to_utf16 ((gunichar*)beginRegionCode, -1, NULL, NULL, NULL);
			gchar* charBeginRegionCode = g_utf16_to_utf8 (unichar2BeginRegionCode, -1, NULL, &wsize, NULL);
			g_free (unichar2BeginRegionCode);
	#else
			gchar* charBeginRegionCode = g_utf16_to_utf8 ((gunichar2*) beginRegionCode, -1, NULL, &wsize, NULL);
	#endif
			region.assign (charBeginRegionCode, (size_t)wsize);
			g_free (charBeginRegionCode);
#endif
		}
	}
}

inline const wchar_t*
getOfficialLanguage (LocaleCode code)
{
	const wchar_t* localeCode = globalLocaleData[code];
	
	if (localeCode != 0) {
		// Skip country, region code
		const wchar_t* beginLangCode = toNullChar (localeCode);
		beginLangCode = toNullChar (++beginLangCode);

		return ++beginLangCode;
	}
	
	return 0;
}

static void
initCountryAndRegion (LocaleCode code, String& country, String& region)
{
	if (code >= LOCALE_CODE_MAX)
		 THROW (_T("IDS_LOCAL_CODE_OFR"));
		
	const wchar_t* cntr = getCountryCode (code);
	if (cntr == 0) {
		String msg;
		msg.format (_T("IDS_LOCAL_NOT_IMPL"), code);
		
		THROW (msg);
	}
	else {
#ifdef __WINDOWS__
		country = cntr;
#else
		char* charCntr = convertWcharToChar (cntr);
		country = charCntr;
		g_free ((gchar*)charCntr);
#endif
	}
	
	getRegionCode (code, region);
}


struct LLComparor : public std::binary_function <LANGLocaleMap, int, bool>
{
	bool operator() (const LANGLocaleMap& ll, int lcid) const
	{
		return (ll.lcid < lcid);
	}
};

static ThreadMutexLock cachedLocalesEvtLocker;
static std::map<LocaleCode, const Locale*> cachedLocales;

static void 
AddToTempLocales (const Locale* locale)
{
	typedef std::pair<LocaleCode, const Locale*> cachedEntry;
	
	cachedEntry value(locale->getLocaleCode (), locale);
	
	cachedLocalesEvtLocker.lock ();	
	cachedLocales.insert (value);	
	cachedLocalesEvtLocker.unlock ();
}

static const Locale*
findCachedLocale (LocaleCode code)
{
	typedef std::map<LocaleCode, const Locale*>::iterator iterator;
	
	cachedLocalesEvtLocker.lock ();	
	iterator it = cachedLocales.find (code);	
	cachedLocalesEvtLocker.unlock ();
	
	if (it == cachedLocales.end ())
		return 0; // NULL means not found.
		
	return it->second;
}

static String
getLocaleResString (LocaleCode code)
{
	String localeRes;

	switch (code)
	{
	case ALBANIA:
		localeRes = _T("IDS_ALBANIA_LOCALE_NAME");
		break;

	case CHINA:
		localeRes = _T("IDS_CHINA_LOCALE_NAME");
		break;

	case TAIWAN:
		localeRes = _T("IDS_TAIWAN_LOCALE_NAME");
		break;

	case HONG_KONG:
		localeRes = _T("IDS_HONG_KONG_LOCALE_NAME");
		break;

	case MACAO:
		localeRes = _T("IDS_MACAO_LOCALE_NAME");
		break;

	case CANADA:
		localeRes = _T("IDS_CANADA_LOCALE_NAME");
		break;
	
	case UNITED_KINGDOM:
		localeRes = _T("IDS_UNITED_KINGDOM_LOCALE_NAME");
		break;
	
	case UNITED_STATES:
		localeRes = _T("IDS_UNITED_STATES_LOCALE_NAME");
		break;

	default:
		THROW (_T("IDS_INVALID_LOCALE_CODE"));
	}

	return localeRes;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// class Locale

// private static 
const Locale* Locale::_curLocale = 0;

// public
Locale::Locale (LocaleCode code)
	: _lang ()
	, _country ()
	, _region ()
	, _code (code)
	, _isOfficialLang (true)
{
	initCountryAndRegion (code, _country, _region);
	
#ifdef __WINDOWS__
	_lang = getOfficialLanguage (code);	
#else
	char* lang = convertWcharToChar (getOfficialLanguage (code));	
	_lang = lang;
	g_free (lang);
#endif
}

// public
Locale::Locale(LocaleCode code, const String& lang, bool isOfficalLang)
	: _lang (lang)
	, _country ()
	, _region ()
	, _code (code)
	, _isOfficialLang (isOfficalLang)
{
	initCountryAndRegion (code, _country, _region);	
}

// public
String 
Locale::toString (void) const
{
	const String& lang = _lang;
	const String& country = _country;
	const String& region = _region;
	
	if (lang.isEmpty () && country.isEmpty ())
      return String::EMPTY;
	else if (country.isEmpty () && region.isEmpty ())
      return lang;

    String result = lang;
    
    if (!region.isEmpty ()) {
      result += ('_');
	  result += region;
	}
		
    result+= ('_');
	result += country;	

    return result;
}

// public
String
Locale::getNativeName (void) const
{
	const wchar_t* localeData = globalLocaleData [_code];
	
	if (localeData == 0)
		THROW (_T("IDS_FAIL_GET_NAIVE_DATA"));
		
	// Skip country code, region code, language code, English full name
	localeData = toNullChar (localeData);
	localeData = toNullChar (++localeData);
	localeData = toNullChar (++localeData);
	localeData = toNullChar (++localeData);		

	++localeData;
#ifdef __WINDOWS__
	String result (localeData);
#else
	char* charLocaleData = convertWcharToChar (localeData);
	String result (charLocaleData);
	g_free (charLocaleData);
#endif	

	return result;
}

// public
String
Locale::getEnglishName (void) const
{
	const wchar_t* localeData = globalLocaleData [_code];
	
	if (localeData == 0)
		THROW (_T("IDS_FAIL_GET_NAIVE_DATA"));
		
	// Skip country code, region code, language code
	localeData = toNullChar (localeData);
	localeData = toNullChar (++localeData);
	localeData = toNullChar (++localeData);	

	++localeData;
#ifdef __WINDOWS__
	String result (localeData);
#else
	char* charLocaleData = convertWcharToChar (localeData);
	String result (charLocaleData);
	g_free (charLocaleData);
#endif	

	return result;
}

// public
String 
Locale::getDisplayName (void) const
{
	//IResourceLoader* loader = getLocaleLoader ();

	//return loader->loadString (getLocaleResString (_code));	


	// TODO
	return getLocaleResString (_code);
}

// public
String
Locale::getDisplayName (const Locale* where) const
{
	if (where == 0)
		THROW (_T("The specified locale object is null."));
	
	return getLocaleResString (_code);
	/*
	try {
		return getLocaleLoader ()->loadString (getLocaleResString (_code));	
	}
	catch (ResourceException&) {
		return getDisplayName ();
	}

	*/
}

// public static 
const Locale* 
Locale::getCurrentLocale (void)
{	
	if (Locale::_curLocale == 0) {
		int li = ::GetUserDefaultLangID();		
		
		const LANGLocaleMap* llMapEnd = llMap + LLMAP_NUM;
		const LANGLocaleMap* llPtr = std::lower_bound (llMap, 
													   llMapEnd, 
													   li, 
													   LLComparor ()); 

		LocaleCode code;
		if (llPtr == llMapEnd || llPtr->lcid != li)
			code = UNITED_STATES; // Not found, uses United States.
		else {
			code = (LocaleCode) llPtr->locale;
			if (globalLocaleData [code] == 0)
				code = UNITED_STATES; // CFL doesn't implement the locale.
		}
		
		const Locale* locale = findCachedLocale (code);
		if (locale == 0) {
			locale = new Locale (code);
			AddToTempLocales (locale);
		}

		Locale::_curLocale = locale;	
	}

	return Locale::_curLocale;
}

// public static 
void 
Locale::setCurrentLocale (const Locale* locale)
{
	if (locale == 0)
		THROW (_T("The locale object is null."));
		
	Locale::_curLocale = locale;
}

// public static
void 
Locale::setSystemDefaultLocale (const Locale* locale)
{
	if (locale == 0)
		THROW (_T("The locale object is null."));
		
	Locale::_curLocale = locale;

	// TODO: 更新系统locale
	THROW ("not Implement");
}

// public static 
const Locale* 
Locale::findLocale (LocaleCode code)
{
	const Locale* locale = findCachedLocale (code);
	if (locale == 0) {
		// Not found.		
		locale = new Locale(code);
		AddToTempLocales (locale);
	}
	
	return locale;
}

// public static
void 
Locale::getAllLocales (vector<const Locale*>& locales)
{
	THROW ("getAllLocales not Implement");
}
