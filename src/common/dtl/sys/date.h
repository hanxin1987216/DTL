/***************************************************************************************************
int.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	时间转化

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_DATE_H__
#define __DTL_DATE_H__

#if PRAGMA_ONCE
#	pragma once
#endif
#include "timediff.h"

/**
 * This pattern specified the time string output from #Date::toTimeString
 */
enum TimePattern
{
	// Time with hour, minute format, use 24 hours
	// For example, in chinese locale, it is HH::mm
	TP_SHORT,

	// Time with hour, minute and second format, use 24 hours
	// For example, in chinese locale, it is HH::mm::ss
	TP_LONG,
};

/**
 * This pattern specified the date string output from #Date::to_datee_string
 */
enum DatePattern
{
	// Date with year, month. day, time, format
	// For example, in chinese locale, yyyy-MM-dd
	DP_SHORT,

	// Date with year, month. day, time, week, format
	// For example, in chinese locale yyyy年MM月dd日
	DP_LONG,

	// Date with month and day format
	// For example, in chinese locale MM月dd日
	DP_MONTH_DAY,

	// Date with year and month format
	// For example, in chinese locale yyyy年MM月
	DP_YEAR_MONTH
};

/**
 * This pattern specified the full date string output from #Date::toString
 */
enum FullDatePattern
{
	// General full time with short time and date format
	FD_GENERAL_SHORT ,

	// General full time with long time and date format
	FD_GENERAL_LONG,

	// General full time with long time and date format and era
	FD_GENERAL_FULL,
};		


enum Weekday
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,  
};



/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT Date
{
public:
	explicit Date (void)
		: _epoch (Date::getCurrentTime ())
	{
	}

	Date (const int64& epoch)
		: _epoch (epoch)
	{
	}


#ifdef __WINDOWS__
	explicit Date (const SYSTEMTIME& stime);
	explicit Date (const FILETIME& ft);
#endif // __WINDOWS__


	Date (unsigned int year, 
		  unsigned int month, 
		  unsigned int date, 
		  unsigned int hrs = 0, 
		  unsigned int min = 0, 
		  unsigned int sec = 0,
		  unsigned int millisec = 0);
	
// public static
public:
	static const int64 ticksPerHour;
	static const int64 ticksPerDay;
	static const int64 ticksPerMillisecond;
	static const int64 ticksPerMinute;
	static const int64 ticksPerSecond;

	static int64 getCurrentTime (void);
	
	/*
	* Leap year is any year divisible by four, but not by 100 unless also
	* divisible by 400
	* @return true is the year is leap year
	*/
	static bool	isLeapYear (unsigned int y)
	{
		bool leapYear = false;

        if (!(y % 4)) {
            if ((y % 100)) {
                leapYear = true;
            } else if (!(y % 400)) {
                leapYear = true;
            }
        }

        return leapYear;
    }

    /**
	 * Converts the specified string representation of a date and time to 
	 * its #Date equivalent.
	 *
	 * @param str A string containing a date and time to convert. 
	 * @return A #Date equivalent to the date and time contained in str.
	 */
	static Date parse (const String& str);
	
// public methods
public:

	String toString (FullDatePattern pattern) const;
	
	String toTimeString (TimePattern pattern) const;
	
	String toDateString (DatePattern pattern) const;
	
	/**
     * Returns the number of microseconds since January 1, 1970, 00:00:00 GMT
     * represented by this #Date object.
     *
     * @return  the number of microseconds since January 1, 1970, 00:00:00 GMT
     *          represented by this date.
     */
	int64 time (void) const
	{
		return _epoch;
	}

	/**
     * Sets this #Date object to represent a point in time that is 
     * @param epoch milliseconds after January 1, 1970 00:00:00 GMT. 
     *
	 */
	void time (int64 epoch) 
	{
		_epoch = epoch;
	}

	int64 getLocalTime (void) const;
	
	void setLocalTime (int64 epoch);

protected:

	enum 
	{
		YEAR, MONTH, DAY, DAYYEAR, DAYOFWEEK, HOUR, MINUTE, SECOND
	};


public:
	unsigned int getYear (void) const
	{
		return (unsigned int)fromEpoch (YEAR);
	}

	unsigned int getMonth (void) const
	{
		return (unsigned int) fromEpoch (MONTH);
	}

    /**
     * return day of month
     */
	unsigned int getDay (void) const
	{
		return (unsigned int) fromEpoch (DAY);
	}

	Weekday getDayOfWeek (void) const
	{
		return (Weekday) fromEpoch (DAYOFWEEK);
	}

	unsigned int getDayOfYear (void) const
	{
		return (unsigned int) fromEpoch (DAYYEAR);
	}

	unsigned int getHours (void) const
	{
		return (unsigned int) fromEpoch (HOUR);
	}
	
	unsigned int getMinutes (void) const
	{
		return (unsigned int) fromEpoch (MINUTE);
	}
	
	unsigned int getSeconds (void) const
	{
		return (unsigned int) fromEpoch (SECOND);
	}
	
	int64 timeOfDay (void) const
	{
		return (int64) (this->_epoch % ticksPerDay);
	}



	void addDays (int days);
	void addHours (int hours);

	TimeDiff subtract (const Date& date) const
	{
		return TimeDiff (this->_epoch - date._epoch);
	}

	TimeDiff add (const Date& date) const
	{
		return TimeDiff (this->_epoch + date._epoch);
	}


	// Data keep micro-seconds since the Unix epoch (jan. 1, 1970) UTC 
	// Notice the Windows epoch is starting at (Jan. 1, 1601) UTC
protected:

	int fromEpoch (int what) const;

protected:

	int64 _epoch; 

}; // End class Date


#endif // __DTL_DATE_H__
