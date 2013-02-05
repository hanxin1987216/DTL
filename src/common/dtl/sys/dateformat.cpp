/***************************************************************************************************
dateformat.cpp:	
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


#include "../lang/char.h"
#include "../lang/string.h"
#include "../io/comdef.h"

#include "date.h"
#include "timezone.h"
#include "exception.h"
#include "locale.h"
#include "dateformat.h"

#include <assert.h>

//
// We use the ISO 3166 country code to index the tables of SimpleDateFormat
// such as pattern talbe, month table, etc.
// The link is: http://userpage.chemie.fu-berlin.de/diverse/doc/ISO_3166.html
//
static const unsigned char pattern_table_map[900] =
{
//   0   1   2   3   4   5   6	 7	 8	 9	10  11	12	13	14	15	16	17	18	19
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 20
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 40
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 60
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 80
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 100
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 120
	0xFF, 0xFF, 0xFF, 0xFF,  5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 140
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  1, 0xFF,  2, 0xFF, // 160
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 180
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 200
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 220
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 240
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 260
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 280
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 300
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 320
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 340
	0xFF, 0xFF, 0xFF, 0xFF,  3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 360
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 380
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 400
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 420
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 440
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 460
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 480
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 500
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 520
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 540
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 560
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 580
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 600
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 620
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 640
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 660
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 680
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 700
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 820
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 6, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, // 840
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 860
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 880
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 900
};

enum PatternStringIndex 
{
	SHORT_TIME,
	LONG_TIME,
	SHORT_DATE,
	LONG_DATE,
	MONTH_DAY,
	YEAR_MONTH
};

enum TimeIndicatorStringIndex
{
	AM_INDEX,
	PM_INDEX
};

struct DateStringLocator
{
	// short time format.long time format.short date format
	// long date format.month day format. year month format
	unsigned short patternIndex;
	
	unsigned short fullWeekIndex;
	
	unsigned short abbWeekIndex;
	
	unsigned short fullMonthIndex;
	
	unsigned short abbMonthIndex;
	
	// AM,PM
	unsigned short timeIndicatorIndex;
};

const DateStringLocator dateLocator[] = 
{
	{1,		19,		26,		47,		59,		83}, // US
	{7,		33,		33,		71,		71,		85}, // CHINA
	{13,	40,		40,		71,		71,		85}, // TAIWAN
	{13,	40,		40,		71,		71,		85}, // HONGKONG
	{13,	40,		40,		71,		71,		85}, // MACAO
	{1,		19,		26,		47,		59,		83}, // CANADA
	{87,	19,		26,		47,		59,		83}, // UNITED_KINGDOM
};

const wchar_t* dateStringTable[] = 
{
	L"\0",					// 0

	// USA Date Pattern
	L"HH:mm",				// 1
	L"HH:mm:ss",			// 2
	L"MM/dd/yyyy",			// 3
	L"E, MMMM dd, yyyy",	// 4
	L"MMMM dd",				// 5
	L"yyyy MMMM",			// 6
	
	// CHINA Date Pattern
	L"HH:mm",				// 7
	L"HH:mm:ss",			// 8
	L"yyyy-M-d",			// 9
	L"yyyy'\x5e74'M'\x6708'd'\x65e5'",				// 10
	L"MMMMd'\x65e5'",			// 11
	L"yyyy'\x5e74'MMMM", 			// 12

	// TAIWAN Date Pattern
	L"HH:mm",			// 13
	L"HH:mm:ss",			// 14
	L"yyyy-M-d",			// 15
	L"yyyy'\x5e74'M'\x6708'd'\x65e5'",			// 16
	L"MMMMd'\x65e5'",			// 17
	L"yyyy'\x5e74'MMMM", 			// 18
	
	// English full week name
	L"Sunday",			// 19
	L"Monday",			// 20
	L"Tuesday",			// 21
	L"Wednesday",			// 22
	L"Thursday",			// 23
	L"Friday",			// 24
	L"Saturday", 			// 25

	// English abb week name
	L"Sun",			// 26
	L"Mon",			// 27
	L"Tue",			// 28
	L"Wed",			// 29
	L"Thu",			// 30
	L"Fri",			// 31
	L"Sat", 		// 32

	// Simplified Chinese full & abb week name
	L"\x661f\x671f\x5929",			// 33
	L"\x661f\x671f\x4e00",			// 34
	L"\x661f\x671f\x4e8c",			// 35
	L"\x661f\x671f\x4e09",			// 36
	L"\x661f\x671f\x56db",			// 37
	L"\x661f\x671f\x4e94",			// 38
	L"\x661f\x671f\x516d",			// 39
	
	// Tratiditional Chinese full & abb week name
	L"\x661f\x671f\x5929",			// 40
	L"\x661f\x671f\x4e00",			// 41
	L"\x661f\x671f\x4e8c",			// 42
	L"\x661f\x671f\x4e09",			// 43
	L"\x661f\x671f\x56db",			// 44
	L"\x661f\x671f\x4e94",			// 45
	L"\x661f\x671f\x516d",			// 46
	
	// English full month name
	L"January",			// 47
	L"February",			// 48
	L"March",			// 49
	L"April",			// 50
	L"May",			// 51
	L"June",			// 52
	L"July",			// 53
	L"August",			// 54
	L"September",			// 55
	L"October",			// 56
	L"November",			// 57
	L"December", 			// 58

	// English abb month name
	L"Jan",			// 59
	L"Feb",			// 60
	L"Mar",			// 61
	L"Apr",			// 62
	L"May",			// 63,
	L"Jun",			// 64
	L"Jul",			// 65
	L"Aug",			// 66
	L"Sep",			// 67
	L"Oct",			// 68
	L"Nov",			// 69
	L"Dec",			// 70

	// Simplified & Traditional Chinese full & abb month name
	L"\x4e00\x6708",			// 71
	L"\x4e8c\x6708",			// 72
	L"\x4e09\x6708",			// 73
	L"\x56db\x6708",			// 74
	L"\x4e94\x6708",			// 75
	L"\x516d\x6708",			// 76
	L"\x4e03\x6708",			// 77
	L"\x516b\x6708",			// 78
	L"\x4e5d\x6708",			// 79
	L"\x5341\x6708",			// 80
	L"\x5341\x4e00\x6708",			// 81
	L"\x5341\x4e8c\x6708", 			// 82
	
	// English time indicator
	L"AM",			// 83
	L"PM", 			// 84
	
	// Simplified & Traditional Chinese time indicator
	L"\x4e0a\x5348",			// 85
	L"\x4e0b\x5348" 			// 86	
	
	// UK date Pattern
	L"HH:mm",				// 87
	L"HH:mm:ss",			// 88
	L"dd/MM/yyyy",			// 89
	L"E, dd MMMM, yyyy",	// 90
	L"dd MMMM",				// 91
	L"yyyy MMMM",			// 92
};

inline
const DateStringLocator* getDateLocator (const Locale* locale)
{	
	int index = pattern_table_map[locale->getLocaleCode ()];
	
	if( index == 0xFF) {
		locale = Locale::getUSLocale ();
		index = pattern_table_map[locale->getLocaleCode ()];
	}

	return dateLocator + index;	
}

/**
 * The difference with class LocaleDateFormat not only this
 * class format string use the current locale, but also the 
 *	formatted time will uses the local time.
 */
class SimpleDateFormat : public DateFormat
{
public:
	virtual String format (const Date* date, int pattern) const;
	virtual String formatTime (const Date* date, int pattern) const;
	virtual String formatDay (const Date* date, int pattern) const;
	virtual String format (const Date* date, const String& pattern) const;
	
	virtual int64 parse (const String& str) const;

	virtual int64 parse (const String& str, const String& pattern) const;
	virtual String getFormatPattern (FullDatePattern pattern);
	virtual String getFormatPattern (DatePattern pattern);
	virtual String getFormatPattern (TimePattern pattern);

}; // End class SimpleDataFormat

enum PatternKind 
{
	PK_TIME,
	PK_DATE,
	PK_FULL
};	

//
// Current resource routines
//
static String getLocalePattern (const Locale* locale, 
								PatternKind kind, 
								int pattern);
								
static const wchar_t* getTimeIndicator (const Locale* locale, 
										bool is_am);
										
static const wchar_t* getLocaleWeekDay (const Locale* locale, 
										unsigned int day, 
										bool is_abb);
										
static const wchar_t* getLocaleMonth (const Locale* locale, 
									  unsigned int month, 
									  bool is_abb);
	
static bool timeToTimeExprWin32 (const int64& epoch, struct DateTimeExpr* te);

// number of microseconds per second 
const unsigned int usecPerSec = 1000000;

#define INTEGER_BUF_LEN			16

/**
 * a structure similar to ANSI struct tm with the following differences:
 *  - tm_usec isn't an ANSI field
 *  - tm_gmtoff isn't an ANSI field (it's a bsdism)
 */
struct DateTimeExpr 
{
    // microseconds past tm_sec 
    unsigned int tm_usec;
    // (0-61) seconds past tm_min 
    unsigned int tm_sec;
    // (0-59) minutes past tm_hour 
    unsigned int tm_min;
    // (0-23) hours past midnight 
    unsigned int tm_hour;
    // (1-31) day of the month 
    unsigned int tm_mday;
    // (0-11) month of the year 
    unsigned int tm_mon;
    // year  
    int tm_year;
    // (0-6) days since sunday 
    unsigned int tm_wday;
    // (0-365) days since jan 1 
    unsigned int tm_yday;
    // daylight saving time 
    unsigned int tm_isdst;
    // seconds east of UTC 
    unsigned int tm_gmtoff;

	DateTimeExpr (const int64& time)
	{
		timeToTimeExprWin32 (time, this);
	}
};

static int 
count_repeat (const tchar_t* fmt, size_t size, size_t p, tchar_t ch)
{
	size_t i = p + 1;
	while ((i < size) && (fmt [i] == ch)) 
		++i;
	
	return (int) (i - p);
}

static void 
result_pad (String& output, unsigned int digits, bool padding)
{
	tchar_t buf[INTEGER_BUF_LEN];
	int len;

	if (padding)
		len = t_snwprintf (buf, INTEGER_BUF_LEN, _T("0%u"), digits);
	else
		len = t_snwprintf (buf, INTEGER_BUF_LEN, _T("%u"), digits);

	if (len != -1)
		output.append (buf, len);
}

static void 
systemTimeToTimeExpr (DateTimeExpr* te, const SYSTEMTIME *tm)
{
    static const int dayoffset[12] =
    {0, 31, 59, 90, 120, 151, 182, 212, 243, 273, 304, 334};

    /* 
	 * Note; the caller is responsible for filling in detailed tm_usec,
     * tm_gmtoff and tm_isdst data when applicable.
     */
    te->tm_usec = tm->wMilliseconds * 1000;
    te->tm_sec  = tm->wSecond;
    te->tm_min  = tm->wMinute;
    te->tm_hour = tm->wHour;
    te->tm_mday = tm->wDay;
    te->tm_mon  = tm->wMonth;
    te->tm_year = tm->wYear;
    te->tm_wday = tm->wDayOfWeek;
    te->tm_yday = dayoffset[te->tm_mon] + (tm->wDay - 1);
    te->tm_isdst = 0;
    te->tm_gmtoff = 0;

    /* 
	 * If this is a leap year, and we're past the 28th of Feb. (the
     * 58th day after Jan. 1), we'll increment our tm_yday by one.
     */
	if (Date::isLeapYear (tm->wYear) && (te->tm_yday > 58))
        te->tm_yday++;
}

static bool 
timeToTimeExprWin32 (const int64& epoch, DateTimeExpr* te)
{
	SYSTEMTIME st;
    FILETIME ft;

	// Convert epoch to FILETIME
	timeToFileTime (&ft, epoch);

    if (::FileTimeToSystemTime (&ft, &st) == FALSE)
		return false;

    systemTimeToTimeExpr (te, &st);
    te->tm_usec = (unsigned int) (epoch % usecPerSec);

	//TODO: gmt offset and is dst out of my way 
    //te->tm_gmtoff = (unsigned int)time_sec(epoch) - (unsigned int)time_sec(epoch);
	te->tm_gmtoff = 0;
    /*
	 * To compute the dst flag, we compare the expected 
     * local (standard) timezone bias to the delta.
     * [Note, in war time or double daylight time the
     * resulting tm_isdst is, desireably, 2 hours]
     */
    //te->tm_isdst = (te->tm_gmtoff / 3600) - (-(tz.Bias + tz.StandardBias) / 60);
	te->tm_isdst = 0;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// class DateFormat

DateFormat::DateFormat(void)
{
}

DateFormat::~DateFormat(void)
{
}

// private static 
DateFormat* DateFormat::_localInst = 0;

// public static 
const DateFormat* 
DateFormat::getLocalInstance (void)
{
	if (DateFormat::_localInst == 0) {
		DateFormat::_localInst = new SimpleDateFormat;		
	}

	return DateFormat::_localInst;
}

// public static 
void
DateFormat::delLocalInstance (void)
{
	if (DateFormat::_localInst != 0) {
		delete DateFormat::_localInst;
		DateFormat::_localInst = 0;
	}
}

// protected virtual 
String 
DateFormat::doFormat (const Locale* locale,
					  const Date* date, 
					  const String& pattern) const
{
	// the length of the format is usually a good guess of the number
	// of chars in the result. Might save us a few bytes sometimes
	// Add + 10 for cases like mmmm dddd
	String result;
	size_t size = pattern.getLength ();
	result.reserve (size + 10);

	size_t i = 0;
	const tchar_t* patternStr = pattern.getCStr ();	

	DateTimeExpr dte (date->time ());	

	while (i < size) {
		int tokLen = 0;
		tchar_t ch = patternStr [i];

		switch (ch) {
		//
		// Time Formats
		//
		case _T('h'):
		{
			// hour, [1, 12]
			tokLen = count_repeat (patternStr, size, i, ch);

			unsigned int hr = dte.tm_hour % 12;
			if (hr == 0)
				hr = 12;

			result_pad (result, hr, 
						tokLen == 1 ? false : hr > 9 ? false : true);
			break;
		}
		case _T('H'):
			// hour, [0, 23]
			tokLen = count_repeat (patternStr, size, i, ch);
			result_pad (result, dte.tm_hour, 
						tokLen == 1 ? false : (dte.tm_hour > 9 ? false : true));
			break;

		case _T('m'):
			// minute, [0, 59]
			tokLen = count_repeat (patternStr, size, i, ch);
			result_pad (result, dte.tm_min, 
				tokLen == 1 ? false : dte.tm_min > 9 ? false : true);
			break;

		case _T('s'):
			// second [0, 29]
			tokLen = count_repeat (patternStr, size, i, ch);
			result_pad (result, dte.tm_sec, 
						tokLen == 1 ? false : dte.tm_sec > 9 ? false : true);
			break;

		case _T('p'):
		{
			// AM/PM. 
			tokLen = 1;
#ifdef __WINDOWS__
			result.append (getTimeIndicator (locale, 
											 dte.tm_hour < 12));
#else
			const wchar_t* timeIndicator = getTimeIndicator (locale, dte.tm_hour < 12);
			char* charTimeIndicator = convertWcharToChar (timeIndicator);
			result.append (charTimeIndicator);
			g_free ((gchar*)charTimeIndicator);
#endif
			break;
		}
		case _T('z'):
			// timezone
		case _T('Z'):
			assert (false); // pls impl.
			break;

		//
		// Date tokens
		//
		case _T('d'):
			// day. d(dd) = day of month 
			tokLen = count_repeat (patternStr, size, i, ch);
			result_pad (result, dte.tm_mday, 
						tokLen == 1 ? false : dte.tm_mday > 9 ? false : true);
			break;

		case _T('e'):
		{
			tokLen = 1;
#ifdef __WINDOWS__
			result.append (getLocaleWeekDay (locale, 
											 dte.tm_wday, 
											 true));
#else
			const wchar_t* localeWeekDay = getLocaleWeekDay (locale, dte.tm_wday, true);
			char* charLocaleWeekDay = convertWcharToChar (localeWeekDay);
			result.append (charLocaleWeekDay);
			g_free ((gchar*)charLocaleWeekDay);
#endif
			break;
		}

		case _T('E'):
		{
			tokLen = 1;
#ifdef __WINDOWS__
			result.append (getLocaleWeekDay (locale, 
											 dte.tm_wday, 
											 false));
#else
			const wchar_t* localeWeekDay = getLocaleWeekDay (locale, dte.tm_wday, false);
			char* charLocaleWeekDay = convertWcharToChar (localeWeekDay);
			result.append (charLocaleWeekDay);
			g_free ((gchar*)charLocaleWeekDay);
#endif
			break;
		}

		case _T('w'):
			tokLen = 1;
			result_pad (result, dte.tm_wday, false);
			break;

		case _T('W'):
			assert (false); // TODO:
			break;

		case _T('M'):
		{
			// Month.m(m?) = month # (with leading 0 if two mm)
			// mmm = 3 letter name
			// mmmm+ = full name
			tokLen = count_repeat (patternStr, size, i, ch);
			int month = dte.tm_mon;

			if (tokLen == 1)
				result_pad (result, month, false);
			else if (tokLen == 2)
				result_pad (result, month, month > 9 ? false : true);
			else if (tokLen == 3) {
#ifdef __WINDOWS__
				result.append (getLocaleMonth (locale,
												month, 
												true));
#else
			const wchar_t* localeMonth = getLocaleMonth (locale, month, true);
			char* charLocaleMonth = convertWcharToChar (localeMonth);
			result.append (charLocaleMonth);
			g_free ((gchar*)charLocaleMonth);
#endif
			}
			else {
#ifdef __WINDOWS__
			result.append (getLocaleMonth (locale,
												month, 
												false));
#else
			const wchar_t* localeMonth = getLocaleMonth (locale, month, false);
			char* charLocaleMonth = convertWcharToChar (localeMonth);
			result.append (charLocaleMonth);
			g_free ((gchar*)charLocaleMonth);
#endif
			}

			break;
		}

		case _T('y'):
		{
			// Year. y(y?) = two digit year, with leading 0 if yy
			// yyy+ full year, if yyy and yr < 1000, displayed as three digits
			tokLen = count_repeat (patternStr, size, i, ch);

			int year = tokLen > 2 ? dte.tm_year : dte.tm_year % 100;
			if (tokLen == 1)
				result_pad (result, year, false);
			else if (tokLen == 2)
				result_pad (result, year, (year < 10));
			else
				result_pad (result, year, false);
			break;
		}

		case ('g'):
		case ('G'):
			// Era name
			assert (false);
			break;

		case ('O'):
		{
			int hourOffset = (int) (TimeZone::getCurrentTimeZone ()->getUTCOffset (
															date) / Date::ticksPerHour);
			
			// Time zone offset 
			if (hourOffset >= 0) { // +0000
				result.append ('+', 1);
				result_pad (result, hourOffset, (hourOffset < 10));
			}
			else {
				result.append ('-', 1);
				result_pad (result, -hourOffset, (hourOffset > -10));
			}
			
			result.append ('0', 2);
			tokLen = 1;
			break;
		}
			
		//
		// Other
		//
		case '\'':
		{
			// literal
			size_t l = i + 1;
			while (true) {
				wchar_t c = patternStr[l++];

				if (c == '\'') {
					if (patternStr[l] != '\'') // Peek next to check double ''
						break;
					else 
						l++; // skip it
				}

				result.append (c, 1);
			}
			
			tokLen = (int) (l - i);
			break;
		}
		
		default:
			// catch all unkown token
			result.append (ch, 1);
			tokLen = 1;
			break;
		}

		i += tokLen;
	}

	return result;
}

#define		NO_DIGIT		num_parsed = -1; return 0

static int // return the number
parse_number (const tchar_t* str, // string to retrieve the number
			  size_t count, // the remaining count of the string
			  int digits, // the digit count
			  bool leadingzero, // the leading has zero or not
			  bool next_not_digit,
			  int& num_parsed // retrieve the parsed character number
			  )
{
	int number = 0, i;

	// Parse the real digit count
	if (!leadingzero) {
		int real_digits = 0;
		for (i = 0; (size_t) i < count && i < digits; i++) {
			if (!Char::isDigit (str[i]))
				break;

			real_digits++;
		}

		digits = real_digits;
	}

	// no enough 
	if (count < (size_t) digits) {
		NO_DIGIT;
	}

	if (count > (size_t) digits && next_not_digit && Char::isDigit (str[digits])) {
		// More digits left over 
		NO_DIGIT;
	}

	for (i = 0; i < digits; i++) {
		wchar_t c = str[i];
		if (!Char::isDigit (c)) {
			NO_DIGIT;
		}

		number = number * 10 + (unsigned int) (c - '0');
	}

	// successfully
	num_parsed = digits;
	return number;
}

// protected virtual 
bool 
DateFormat::doParse (const Locale* locale,
					 const String& str, 
					 const String& pattern,
					 int64& time /* OUT */) const
{
	int day = -1;
	//int dayofweek = -1;
	int month = -1; 
	int year = -1;
	int hour = -1;
	int minute = -1;
	int second = -1;

	const tchar_t* ptn = pattern.getCStr ();
	const tchar_t* chars = str.getCStr ();
	const tchar_t* end_chars = chars + str.getLength ();

	size_t len = pattern.getLength ();
	size_t pos = 0, num = 0;
	int ampm = -1;

	while (pos + num < len) {
		if (chars == end_chars)
			break;

		if (chars[pos] == '\'') {
			// string literal, compare the literal is the expected.
			num = 1;
			while (pos + num < len) {
				if (chars[pos + num] == '\'')
					break;

				if (chars == end_chars)
					return false;

				if (*chars != ptn[pos + num])
					return false;
				
				chars++;
				num++;
			}
			if (pos + num > len)
				return false;

			//
			// has skip the string literal successfully, reset the pos and num
			//
			pos += num + 1;
			num = 0;
			continue;
		} 
		else if (Char::isWhiteSpace (*chars)) {
			chars++;

			// Compare the the pattern whether or not be whitespace
			if (Char::isWhiteSpace (ptn[pos])) {
				pos++;
				continue;
			}

			// skip the remaining whitespace
			int ws = 0;
			size_t slen = end_chars - chars;
			while ((size_t) ws < slen) {
				if (Char::isWhiteSpace (chars [ws]))
					ws++;
				else
					break;
			}
			
			chars += ws;
		} //END if

		//
		// Skip the repeated formatted character, use the last character, 
		// @num record the repeated character count
		//
		if ((pos + num + 1 < len) && (ptn[pos + num + 1] == ptn[pos + num])) {
			num++; 
			continue;
		}

		int num_parsed = 0;
		bool next_not_digit; // keep the next character whether or not be a digit character

		// Check next character
		if (pos + num + 1 < len) {
			wchar_t next_char = ptn[pos + num + 1];
			
			next_not_digit = !(next_char == 'd' ||
							   next_char == 'M' ||
							   next_char == 'y' ||
							   next_char == 'h' ||
							   next_char == 'H' ||
							   next_char == 'm' ||
							   next_char == 's' ||
							   //next_char == 'z' ||
							   next_char == '\'' ||
							   Char::isDigit (next_char));
		} 
		else {
			next_not_digit = true;
		} //END if
				
		switch (ptn[pos])
		{
		case 'd': // day
			if (day != -1)
				return false; // has get
			if (num == 0)
				day = parse_number (chars, 
									end_chars - chars, 
									2, 
									false, 
									next_not_digit, 
									num_parsed);
			else if (num == 1)
				day = parse_number (chars, 
									end_chars - chars,
									2, 
									true, 
									next_not_digit, 
									num_parsed);
			break;

		case 'M': // month
			if (month != -1)
				return false; // has get
			if (num == 0)
				month = parse_number (chars, 
									  end_chars - chars,
									  2, 
									  false, 
									  next_not_digit, 
									  num_parsed);
			else if (num == 1)
				month = parse_number (chars,
									  end_chars - chars, 
									  2, 
									  true, 
									  next_not_digit, 
									  num_parsed);
			else {
				// TODO:
			}
			break;

		case 'y': // Year
			if (year != -1)
				return false;

			if (num == 0) {
				year = parse_number (chars, 
									 end_chars - chars, 
									 2,
									 false, 
									 next_not_digit, 
									 num_parsed);
			} 
			else if (num < 3) {
				year = parse_number (chars,
									 end_chars - chars,
									 2, 
									 true, 
									 next_not_digit, 
									 num_parsed);
			} 
			else {
				year = parse_number (chars, 
									 end_chars - chars,
									 4, 
									 false, 
									 next_not_digit, 
									 num_parsed);

				// TODO:
				/*if ((year >= 1000) && (num_parsed == 4) && (!longYear) && (s.Length > 4)) {
					int np = 0;
					int ly = parse_number (s, 5, false, sloppy_parsing, next_not_digit, out np);
					longYear = (ly > 9999);
				}*/

				num = 3;
			}

			//FIXME: We should do use dfi.Calendat.TwoDigitYearMax
			if (num_parsed <= 2)
				year += (year < 30) ? 2000 : 1900;
            break;

		case 'h': // hour
			if (hour != -1)
				return false;

			if (num == 0)
				hour = parse_number (chars,
									 end_chars - chars, 
									 2, 
									 false, 
									 next_not_digit, 
									 num_parsed);
			else {
				hour = parse_number (chars,
									 end_chars - chars,
									 2, 
									 true, 
									 next_not_digit, 
									 num_parsed);
				num = 1;
			}

			if (hour >= 12)
				return false;

			break;

		case 'H': // Hour
			if ((hour != -1) || (ampm >= 0))
				return false;

			if (num == 0)
				hour = parse_number (chars,
									 end_chars - chars,
									 2, 
									 false, 
									 next_not_digit, 
									 num_parsed);
			else
			{
				hour = parse_number (chars, 
									 end_chars - chars,
									 2, 
									 true, 
									 next_not_digit, 
									 num_parsed);
				num = 1;
			}
			if (hour >= 24)
				return false;

			ampm = -2;
			break;

		case 'm': // minute
			if (minute != -1)
				return false;

			if (num == 0)
				minute = parse_number (chars, 
									   end_chars - chars,
									   2, 
									   false, 
									   next_not_digit, 
									   num_parsed);
			else
			{
				minute = parse_number (chars, 
									   end_chars - chars,
									   2, 
									   true, 
									   next_not_digit, 
									   num_parsed);
				num = 1;
			}
			if (minute >= 60)
				return false;
			break;

		case 's':
			if (second != -1)
				return false;

			if (num == 0)
				second = parse_number (chars, 
									   end_chars - chars, 
									   2, 
									   false, 
									   next_not_digit, 
									   num_parsed);
			else
			{
				second = parse_number (chars, 
									   end_chars - chars, 
									   2, 
									   true, 
									   next_not_digit, 
									   num_parsed);
				num = 1;
			}
			if (second >= 60)
				return false;
			break;

		case 'p':
			if (ampm != -1)
				return false;

			if (num == 0)
			{
				// TODO
			}
			else
			{
				// TODO:
				num = 1;
			}
			break;

		case 'z':
			// TODO;
			return false;	
			

		case 'Z':
			if (*chars != 'Z')
				return false;
			// TODO:
			break;

		case '/':
		case ':':
			num_parsed = 1;
			break;

		default:
			if (ptn[pos] == '\'') {
				pos++;
			}					

			if (*chars != ptn[pos]) {
				//TODO:
				return false;
			}

			if (ptn[pos + 1] == '\'') {
				pos++;
			}

			num = 0;
			num_parsed = 1;
			break;
		}

		if (num_parsed < 0)
			return false;

		chars += num_parsed;
		pos += num + 1;
		num = 0;

	} // END while

	
	if (second == -1)
		second = 0;
	if (minute == -1)
		minute = 0;
	if (hour == -1)
		hour = 0;

	Date now;
	if (day == -1)
		day = now.getDay ();
	if (month == -1)
		month = now.getMonth ();
	if (year == -1) //TODO:		
		year = now.getYear ();
	
	if (ampm == 1)
		hour = hour + 12;
	
	// For anything out of range  return false
	if ( year < 1 || year > 9999 || month < 1 || month >12  ||
		 day < 1 || day > (int) daysInMonth (year, month) ||
		 hour < 0 || hour > 23 ||
		 minute < 0 || minute > 59 ||
		 second < 0 || second > 59 )
			return false; 

	Date date (year, month, day, hour, minute, second, 0);
	
	int hourOffset = (int) (TimeZone::getCurrentTimeZone ()->getUTCOffset (&date) / Date::ticksPerHour);
	date.addHours (-hourOffset);

	time = date.time ();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// class SimpleDateFormat

// Public virtual
String 
SimpleDateFormat::format (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (Locale::getCurrentLocale (), 
								   PK_FULL, 
								   pattern);
	
	return format (date, ptn);
}

// Public virtual
String 
SimpleDateFormat::formatTime (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (Locale::getCurrentLocale (), 
								   PK_TIME, 
								   pattern);
	
	return format (date, ptn);
}

// Public virtual
String 
SimpleDateFormat::formatDay (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (Locale::getCurrentLocale (), 
								   PK_DATE, 
								   pattern);
	
	return format (date, ptn);
}

// public virtual 
String 
SimpleDateFormat::format (const Date* date, const String& pattern) const
{
	// Convert the UTC time to the local time.
	int64 localTicks = date->time ();
	
	const TimeZone* tz = TimeZone::getCurrentTimeZone ();
	double hourOffset = ((double)tz->getUTCOffset (date) / (double)Date::ticksPerHour);
	localTicks += int64(hourOffset * Date::ticksPerHour);
	Date localDate (localTicks);
	
	const Locale* curLocale = Locale::getCurrentLocale ();
	return DateFormat::doFormat (curLocale,
								 &localDate, 
								 pattern);
}

// Public virtual
String 
SimpleDateFormat::getFormatPattern (FullDatePattern pattern)
{
	const Locale* curLocale = Locale::getCurrentLocale ();

	return getLocalePattern (curLocale, 
							 PK_FULL, 
							 pattern);
}

// Public virtual
String 
SimpleDateFormat::getFormatPattern (DatePattern pattern)
{
	const Locale* curLocale = Locale::getCurrentLocale ();

	return getLocalePattern (curLocale, 
							 PK_DATE, 
							 pattern);
}

// Public virtual
String 
SimpleDateFormat::getFormatPattern (TimePattern pattern)
{
	const Locale* curLocale = Locale::getCurrentLocale ();

	return getLocalePattern (curLocale, 
							 PK_TIME, 
							 pattern);
}

// Public virtual 
int64 
SimpleDateFormat::parse (const String& str, const String& ptn) const
{
	const Locale* curLocale = Locale::getCurrentLocale ();
	
	int64 time = 0;
	if (doParse (curLocale, str, ptn, time) == true)
		return time;
									
	THROW (_T("IDS_INVALID_DATE_FORMAT"));
}

// Public virtual 
int64 
SimpleDateFormat::parse (const String& str) const
{
	const Locale* curLocale = Locale::getCurrentLocale ();
	
	//TODO: This method only parse for current locale.
	String ptn = getLocalePattern (curLocale, 
								   PK_FULL, 
								   FD_GENERAL_SHORT);

	int64 time = 0;
	if (doParse (curLocale, str, ptn, time) == true) 
			return time;

	ptn = getLocalePattern (curLocale, 
							PK_FULL, 
							FD_GENERAL_LONG);
	if (doParse (curLocale, str, ptn, time) == true)
		return time;
		
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_LONG);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_SHORT);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_MONTH_DAY);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
		
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_YEAR_MONTH);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_TIME, 
							TP_LONG);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_TIME, 
							TP_SHORT);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
							
	THROW (_T("IDS_INVALID_DATE_FORMAT"));
}

#ifndef __WINDOWS__
static String 
getFmtPatternsChar (const wchar_t* wchar)
{
	char* charFmtPattern = convertWcharToChar (wchar);
	String result (charFmtPattern);
	g_free (charFmtPattern);
	return result;
}
#endif

static String 
getLocalePattern (const Locale* locale, 
				  PatternKind kind, 
				  int pattern)
{
	const DateStringLocator* locator = getDateLocator (locale);

	const wchar_t** fmtPatterns = (const wchar_t**) (dateStringTable + 
														locator->patternIndex);
	switch (kind) {
	case PK_TIME:
		if (pattern == TP_SHORT)
#ifdef __WINDOWS__
			return fmtPatterns[SHORT_TIME];
#else
			return getFmtPatternsChar (fmtPatterns[SHORT_TIME]);
#endif
		else if (pattern == TP_LONG)
#ifdef __WINDOWS__
			return fmtPatterns[LONG_TIME];
#else
			return getFmtPatternsChar (fmtPatterns[LONG_TIME]);
#endif
		else 
			assert (false);
		break;

	case PK_DATE:
		switch (pattern) {
		case DP_SHORT:
#ifdef __WINDOWS__
			return fmtPatterns[SHORT_DATE];
#else
			return getFmtPatternsChar (fmtPatterns[SHORT_DATE]);
#endif

		case DP_LONG:
#ifdef __WINDOWS__
			return fmtPatterns[LONG_DATE];
#else
			return getFmtPatternsChar (fmtPatterns[LONG_DATE]);
#endif

		case DP_MONTH_DAY:
#ifdef __WINDOWS__
			return fmtPatterns[MONTH_DAY];
#else
			return getFmtPatternsChar (fmtPatterns[MONTH_DAY]);
#endif

		case DP_YEAR_MONTH:
#ifdef __WINDOWS__
			return fmtPatterns[YEAR_MONTH];
#else
			return getFmtPatternsChar (fmtPatterns[YEAR_MONTH]);
#endif
		}
		assert (false);
		break;

	case PK_FULL:
		{
		if (pattern > FD_GENERAL_FULL)
			assert (false); // still not impl.

		if (pattern == FD_GENERAL_SHORT) {
#ifdef __WINDOWS__
			String fullPattern = fmtPatterns[SHORT_DATE];
			fullPattern.append (_T(' '), 1);
			fullPattern.append (fmtPatterns[SHORT_TIME]);

			return fullPattern;
#else
			const wchar_t* portFmtPattern = fmtPatterns[SHORT_DATE];
			char* fpattern = convertWcharToChar (portFmtPattern);
			String fullPattern (fpattern);
			g_free (fpattern);

			fullPattern.append (_T(' '), 1);
			fpattern = convertWcharToChar (fmtPatterns[SHORT_TIME]);
			fullPattern.append (fpattern);
			g_free (fpattern);
			
			return fullPattern;
#endif
		}
		else if (pattern == FD_GENERAL_LONG) {
#ifdef __WINDOWS__
			String fullPattern = fmtPatterns[LONG_DATE];
			fullPattern.append (_T(' '), 1);
			fullPattern.append (fmtPatterns[LONG_TIME]);

			return fullPattern;
#else
			const wchar_t* portFmtPattern = fmtPatterns[LONG_DATE];
			char* fpattern = convertWcharToChar (portFmtPattern);
			String fullPattern (fpattern);
			g_free (fpattern);

			fullPattern.append (_T(' '), 1);

			fpattern = convertWcharToChar (fmtPatterns[LONG_TIME]);
			fullPattern.append (fpattern);
			g_free (fpattern);
			
			return fullPattern;
#endif
		}
		else if (pattern == FD_GENERAL_FULL) {
#ifdef __WINDOWS__
			String fullPattern = fmtPatterns[LONG_DATE];
			fullPattern.append (_T(' '), 1);
			
			//
			// The G format still not implement, by AnyBackup ask replace
			// has used this format. In fact, it is meaningless to show the era.
			// so we commented out the format.
			// @hhf  2004-7-21
			//
			//full_pattern.append (_T(" G ")); //append era pattern

			fullPattern.append (fmtPatterns[LONG_TIME]);

			return fullPattern;
#else
			const wchar_t* portFmtPattern = fmtPatterns[LONG_DATE];
			char* fpattern = convertWcharToChar (portFmtPattern);
			String fullPattern (fpattern);
			g_free (fpattern);

			fullPattern.append (_T(' '), 1);
			fpattern = convertWcharToChar (fmtPatterns[LONG_TIME]);
			fullPattern.append (fpattern);
			g_free (fpattern);

			return fullPattern;
#endif
		}
		
		assert (false);
		}
	}

	return String::EMPTY;
}

static const wchar_t*
getTimeIndicator (const Locale* locale, bool is_am)
{
	const DateStringLocator* locator = getDateLocator (locale);

	const wchar_t** timeIndicators = (const wchar_t**) dateStringTable + 
														locator->timeIndicatorIndex;

	int index = is_am ? AM_INDEX : PM_INDEX;
	return timeIndicators[index];
}

static const wchar_t* 
getLocaleWeekDay (const Locale* locale, 
				  unsigned int day /* 0 - 6 */, 
				  bool is_abb)
{
	const DateStringLocator* locator = getDateLocator (locale);	

	const wchar_t** weekDays;
	if (is_abb) {
		weekDays = (const wchar_t**) dateStringTable + 
										locator->abbWeekIndex;
	}
	else {
		weekDays = (const wchar_t**) dateStringTable + 
										locator->fullWeekIndex;
	}
	
	return weekDays[day];
}

// private static 
const wchar_t* 
getLocaleMonth (const Locale* locale,
			    unsigned int month /* 1 - 12 */, 
				bool is_abb)
{
	const DateStringLocator* locator = getDateLocator (locale);	

	const wchar_t** months;

	if (is_abb) 
		months = (const wchar_t**) dateStringTable + 
										locator->abbMonthIndex;
	else
		months = (const wchar_t**) dateStringTable + 
										locator->fullMonthIndex;
		
	return months [month - 1];
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// class LocaleDateFormat

// public ctor
LocaleDateFormat::LocaleDateFormat (const Locale* locale)
	: DateFormat ()
	, _locale (locale)
{
	if (locale == 0) 
		THROW (_T("The locale object is null."));
}

// public virtual 
String 
LocaleDateFormat::format (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (_locale, 
								   PK_FULL, 
								   pattern);
	
	return doFormat (_locale, date, ptn);
}
		
// public virtual 
String 
LocaleDateFormat::formatTime (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (_locale,
								   PK_TIME, 
								   pattern);
	
	return doFormat (_locale, date, ptn);
}

// public virtual 
String 
LocaleDateFormat::formatDay (const Date* date, int pattern) const
{
	String ptn = getLocalePattern (_locale,
								   PK_DATE, 
								   pattern);
	
	return doFormat (_locale, date, ptn);
}
	
// public virtual 
String 
LocaleDateFormat::format (const Date* date, 
						  const String& pattern) const
{	
	return DateFormat::doFormat (_locale,
								 date, 
								 pattern);
}
		
// Public virtual
String 
LocaleDateFormat::getFormatPattern (FullDatePattern pattern)
{
	const Locale* curLocale = _locale;

	return getLocalePattern (curLocale, 
							 PK_FULL, 
							 pattern);
}

// Public virtual
String 
LocaleDateFormat::getFormatPattern (DatePattern pattern)
{
	const Locale* curLocale = _locale;

	return getLocalePattern (curLocale, 
							 PK_DATE, 
							 pattern);
}

// Public virtual
String 
LocaleDateFormat::getFormatPattern (TimePattern pattern)
{
	const Locale* curLocale = _locale;

	return getLocalePattern (curLocale, 
							 PK_TIME, 
							 pattern);
}

// Public virtual 
int64 
LocaleDateFormat::parse (const String& str, const String& ptn) const
{
	const Locale* curLocale = _locale;
	
	int64 time = 0;
	if (doParse (curLocale, str, ptn, time) == true)
		return time;
									
	THROW (_T("IDS_INVALID_DATE_FORMAT"));
}

// public virtual 
int64 
LocaleDateFormat::parse (const String& str) const
{
	const Locale* curLocale = _locale;
	
	//TODO: This method only parse for current locale.
	String ptn = getLocalePattern (curLocale, 
								   PK_FULL, 
								   FD_GENERAL_SHORT);

	int64 time = 0;
	if (doParse (curLocale, str, ptn, time) == true)
		return time;
		
	ptn = getLocalePattern (curLocale, 
							PK_FULL, 
							FD_GENERAL_LONG);
	if (doParse (curLocale, str, ptn, time) == true)
		return time;
		
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_LONG);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_SHORT);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_MONTH_DAY);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
		
	ptn = getLocalePattern (curLocale, 
							PK_DATE, 
							DP_YEAR_MONTH);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_TIME, 
							TP_LONG);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
	
	ptn = getLocalePattern (curLocale, 
							PK_TIME, 
							TP_SHORT);
	if (doParse (curLocale, str, ptn, time) == true) 
		return time;
							
	THROW (_T("IDS_INVALID_DATE_FORMAT"));
}
