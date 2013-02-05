/***************************************************************************************************
timezone.h:	
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

#include <dtprec.h>
#include "../prec.h"
#include "../mono_base/uglify.h"

#include "../lang/string.h"
#include "exception.h"
#include "date.h"
#include "timezone.h"

extern const wchar_t* toNullChar (const wchar_t* ptr);

class CurrentTimeZone : public TimeZone
{
	friend class TimeZone;
	
protected:
	CurrentTimeZone (void);
	
// Overriden methods
public:
	virtual int64 getUTCOffset (const Date* date) const;
	virtual bool inDaylightTime (const Date* date) const ;
	
// Data Members
protected:
	// Daylight saving time offset
	int64 _UTCOffsetWithDls;
	
	int64 _UTCOffset;
}; // End class CurrentTimeZone
	
//////////////////////////////////////////////////////////////////////////////////////////////////
// class TimeZone

// private static 
TimeZone* TimeZone::_curTimeZone = 0;

// public static 
const TimeZone* 
TimeZone::getCurrentTimeZone (void)
{
	if (TimeZone::_curTimeZone == 0) {
		TimeZone::_curTimeZone = new CurrentTimeZone;		
	}

	return TimeZone::_curTimeZone;
}


// public virtual dtor
TimeZone::~TimeZone(void)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// class CurrentTimeZone

#ifndef __WINDOWS__
/*
 * Return's the offset from GMT of a local time.
 * 
 *  tm is a local time
 *  t  is the same local time as seconds.
 */
static int 
gmt_offset(struct tm *tm, time_t t)
{
#if defined(HAVE_TM_GMTOFF)
	return tm->tm_gmtoff;
#else
	struct tm g;
	time_t t2;
	g = *gmtime(&t);
	g.tm_isdst = tm->tm_isdst;
	t2 = mktime(&g);
	return (int)difftime(t, t2);
#endif
}
#endif

static bool
loadTimeZoneInfo (unsigned int year, 
			  	  int64& UTCOffset, 
			  	  int64& UTCOffsetWithDls,
			  	  String& std_name)
{
#ifdef __WINDOWS__
	TIME_ZONE_INFORMATION tz_info;
	int tz_id;

	tz_id = ::GetTimeZoneInformation (&tz_info);
	if (tz_id == TIME_ZONE_ID_INVALID)
		return false;

	if ((year <= 1601) || (year > 30827)) {
		// According to MSDN, the MS time functions can't handle dates outside
		// this interval.
		return true;
	}

	std_name = tz_info.StandardName;

	UTCOffset = ((tz_info.Bias + tz_info.StandardBias) * -60000000LL);
	UTCOffsetWithDls = UTCOffset + ((tz_info.DaylightBias - tz_info.StandardBias) * -60000000LL);

	return true;
#else

	struct tm start, tt;
	time_t t;

	long int gmtoff;
	int is_daylight = 0, day;
	char tzone [64];

	memset (&start, 0, sizeof (start));

	start.tm_mday = 1;
	start.tm_year = year-1900;

	t = mktime (&start);

	if ((year < 1970) || (year > 2037) || (t == -1)) {
		t = time (NULL);
		tt = *localtime (&t);
		strftime (tzone, sizeof (tzone), "%Z", &tt);
		std_name = tzone;
		UTCOffset = gmt_offset (&start, t);
		UTCOffsetWithDls = UTCOffset + (tt.tm_isdst * -1000000LL);
		return true;
	}

	gmtoff = gmt_offset (&start, t);

	/* For each day of the year, calculate the tm_gmtoff. */
	for (day = 0; day < 365; day++) {

		t += 3600*24;
		tt = *localtime (&t);

		/* Daylight saving starts or ends here. */
		if (gmt_offset (&tt, t) != gmtoff) {
			struct tm tt1;
			time_t t1;

			/* Try to find the exact hour when daylight saving starts/ends. */
			t1 = t;
			do {
				t1 -= 3600;
				tt1 = *localtime (&t1);
			} while (gmt_offset (&tt1, t1) != gmtoff);

			/* Try to find the exact minute when daylight saving starts/ends. */
			do {
				t1 += 60;
				tt1 = *localtime (&t1);
			} while (gmt_offset (&tt1, t1) == gmtoff);
			t1+=gmtoff;
			strftime (tzone, sizeof (tzone), "%Z", &tt);
			
			/* Write data, if we're already in daylight saving, we're done. */
			if (!is_daylight) {
				std_name = tzone;
				UTCOffset = 0;
				UTCOffsetWithDls = (gint64)t1 * 1000000L;
				return true;
			} else {
				UTCOffset = (gint64)t1 * 1000000L;
				UTCOffsetWithDls = 0;
				is_daylight = 1;
			}

			/* This is only set once when we enter daylight saving. */
			UTCOffset = (gint64)gmtoff * 1000000L;
			UTCOffsetWithDls = (gint64)(gmt_offset (&tt, t) - gmtoff) * 1000000L;
			gmtoff = gmt_offset (&tt, t);
		}
	}

	if (!is_daylight) {
		strftime (tzone, sizeof (tzone), "%Z", &tt);
		std_name = tzone;
		UTCOffset = (gint64)gmtoff * 1000000L;
		UTCOffsetWithDls = 0;
	}

	return true;
#endif
}

// public ctor
CurrentTimeZone::CurrentTimeZone (void)
	: TimeZone ()
	, _UTCOffsetWithDls (0)
	, _UTCOffset (0)
{
	Date now;

	if (!loadTimeZoneInfo (now.getYear (), _UTCOffset, _UTCOffsetWithDls, _displayName))  
		THROW (_T("IDS_FAIL_GET_CUR_TZ"));
}

// public virtual 
int64
CurrentTimeZone::getUTCOffset (const Date* date) const
{
	if (inDaylightTime (date))
		return _UTCOffsetWithDls;
	else
		return _UTCOffset;
}

// public virtual 
bool 
CurrentTimeZone::inDaylightTime (const Date* date) const
{
	// TODO: 
	return false;//(date_offset (date->time ()) != _UTCOffset);
}



