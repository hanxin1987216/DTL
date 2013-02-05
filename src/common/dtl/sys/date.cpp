/***************************************************************************************************
date.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	时间转化类

Author:
	韩欣 （han.xin@datatom.com）

Creating Time:
	2011-10-10
***************************************************************************************************/

#include "../prec.h"
#include "../mono_base/uglify.h"

#include "exception.h"
#include "../io/comdef.h"
#include "locale.h"
#include "dateformat.h"
#include "timediff.h"
#include "timezone.h"

#include "date.h"
#include "locale.h"

#ifndef __WINDOWS__
#include <sys/time.h>
#include <time.h>
#endif

#include <iostream>
using namespace std;


// 基础计年 1970年
#define BASIC_YEAR		1970

const int64 Date::ticksPerHour = __INT64_C(3600000000);
const int64 Date::ticksPerDay = __INT64_C(86400000000);
const int64 Date::ticksPerMillisecond = __INT64_C(1000);
const int64 Date::ticksPerMinute = __INT64_C(60000000);
const int64 Date::ticksPerSecond = __INT64_C(1000000);

static const unsigned int dayoffset[12] = {
	0, 31, 59, 90, 120, 151, 182, 212, 243, 273, 304, 334
};



static unsigned int 
absoluteDays (unsigned int year, unsigned int month, unsigned int day)////求公元0年后的总天数
{
	unsigned int temp = 0, m = 0;
	while (++m < month)
		temp += daysInMonth (year, m);

	return ((day - 1) + temp + (365 * (year - 1)) + ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400));
}



/*
 * Magic number to convert a time which is relative to
 * Jan 1, 1970 into a value which is relative to Jan 1, 0001.
 */
#define	EPOCH_ADJUST	((unsigned int64)62135596800LL)




//////////////////////////////////////////////////////////////////////////////////////////////////
// class #Date

// public static 
int64 
Date::getCurrentTime (void)
{
#ifdef __WINDOWS__
	SYSTEMTIME st;
	FILETIME ft;
	
	::GetSystemTime (&st);
	
	
	//TODO, IF CALL FAILURE.
	::SystemTimeToFileTime (&st, &ft);

	int64 epoch;
	fileTimeToTime (&epoch, &ft);
	return epoch;
#else
	struct timeval tv;
	int64 res = 0;

	if (gettimeofday (&tv, NULL) == 0)////获取时间, 精确到微秒
		res = ((int64)tv.tv_sec * 1000000 + tv.tv_usec);

	return res;
#endif
}



#ifdef __WINDOWS__
// public ctor
Date::Date (const SYSTEMTIME& stime)
	: _epoch (0)
{
	FILETIME ftime;
	if (!::SystemTimeToFileTime (&stime, &ftime)) {
		SystemErrorHandler* handler = SystemErrorHandler::getInstance ();
		unsigned int errId = ::GetLastError ();
		String errMsg = handler->toString (errId);
		THROW_BY_HANDLER (errMsg, errId, handler);
	}

	fileTimeToTime (&_epoch, &ftime);
}

Date::Date (const FILETIME& ft)
	: _epoch (0)
{
	fileTimeToTime (&_epoch, &ft);
}

#endif //__WINDOWS__




#define TICKS_PER_MILLISECOND		1000L
#define TICKS_PER_SECOND			1000000L
#define TICKS_PER_MINUTE			60000000L
#define TICKS_PER_HOUR				3600000000LL
#define TICKS_PER_DAY				86400000000LL

// public ctor
Date::Date (unsigned int year, 
			unsigned int month, 
			unsigned int date, 
			unsigned int hrs/* = 0 */, 
			unsigned int min/* = 0 */, 
			unsigned int sec/* = 0 */,
			unsigned int millisec /* = 0 */)
	: _epoch (0)
{
	if (year < 1 || year > 9999 || 
		month < 1 || month >12  ||
		date < 1 || date > daysInMonth (year, month) ||
		hrs < 0 || hrs > 23 ||
		min < 0 || min > 59 ||
		sec < 0 || sec > 59 ) {
			THROW ("IDS_UNKNOWN_DATE");
	}

#ifdef __WINDOWS__ 
	SYSTEMTIME st;
	st.wYear = year;
	st.wMonth = month;
	st.wDay = date;
	st.wHour = hrs;
	st.wMinute = min;
	st.wSecond = sec;
	st.wMilliseconds = millisec;

	FILETIME ft;
	::SystemTimeToFileTime (&st, &ft);
	fileTimeToTime (&_epoch, &ft);
#else
	unsigned int day = absoluteDays (year, month, date);
	_epoch = TICKS_PER_DAY * day + 
			 TICKS_PER_HOUR * hrs +
			 TICKS_PER_MINUTE * min +
			 TICKS_PER_SECOND * sec +
			 TICKS_PER_MILLISECOND * millisec;



	// Minus a Magic number which is relative to
 	// Jan 1, 1970 into a value which is relative to Jan 1, 0001.
	_epoch = _epoch - (EPOCH_ADJUST * TICKS_PER_SECOND);
#endif
}



// public 
String 
Date::toString (FullDatePattern pattern) const
{
	const DateFormat* fmter = DateFormat::getLocalInstance ();
	return fmter->format (this, pattern);

}

// public
void 
Date::addDays (int days)
{
	int64 ticks = days * ticksPerDay;
	_epoch += ticks;
}

// public
void 
Date::addHours (int hours)
{
	int64 ticks = hours * ticksPerHour;
	_epoch += ticks;
}



// public 
String 
Date::toTimeString (TimePattern pattern) const
{
	const DateFormat* fmter = DateFormat::getLocalInstance ();
	return fmter->formatTime (this, pattern);
}

// public 
String 
Date::toDateString (DatePattern pattern) const
{
	const DateFormat* fmter = DateFormat::getLocalInstance ();
	return fmter->formatDay (this, pattern);
}



// public static 
Date 
Date::parse (const String& str)
{
	const DateFormat* fmter = DateFormat::getLocalInstance ();

	return Date (fmter->parse (str));
}




static const unsigned int dp400 = 146097;
static const unsigned int dp100 = 36524;
static const unsigned int dp4 = 1461;

// protected
int 
Date::fromEpoch (int what) const
{
	SYSTEMTIME st;
	FILETIME ft;

	// Convert epoch to FILETIME
	timeToFileTime (&ft, _epoch);

    if (::FileTimeToSystemTime (&ft, &st) == false)
		return 0;

	switch (what) {
	case YEAR:
		return st.wYear;

	case MONTH:
		return st.wMonth;

	case DAY:
		return st.wDay;

	case DAYYEAR:
	{
		int days = dayoffset[st.wMonth - 1] + st.wDay;
		if (Date::isLeapYear (st.wYear - 1900) && (days > 58))
			days++;

		return days;
	}

	case DAYOFWEEK:
		return st.wDayOfWeek;

	case HOUR:
		return st.wHour;

	case MINUTE:
		return st.wMinute;

	case SECOND:
		return st.wSecond;
	}

	return 0;	
}


// public
int64 
Date::getLocalTime (void) const
{
	int64 epoch = _epoch;
	const TimeZone* cur_tz = TimeZone::getCurrentTimeZone ();

	return (epoch + cur_tz->getUTCOffset (this));
}



// public
void 
Date::setLocalTime (int64 epoch) 
{
	const TimeZone* cur_tz = TimeZone::getCurrentTimeZone ();
	Date date(epoch);

	_epoch = epoch - cur_tz->getUTCOffset (&date);
}