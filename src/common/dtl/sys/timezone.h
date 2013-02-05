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

#ifndef __DTL_SYS_TIMEZONE_H__
#define __DTL_SYS_TIMEZONE_H__

#if PRAGMA_ONCE
#pragma once
#endif

#include "../lang/string.h"

/**
 * class TimeZone represents a time zone that abtains the offset of UTC.
 *
 * To get the UTC offset for the current application, firstly get the current
 *	time zone object by calling static method getCurrentTimeZone().
 */
class DTL_DLLEXPORT TimeZone
{
public:
	TimeZone(void)
	{
	}

	virtual ~TimeZone(void);

// Static methods
public:
	static const TimeZone* getCurrentTimeZone (void);


private:
	static TimeZone* _curTimeZone;

// Public methods
public:
	/**
	 *  Returns the offset of this time zone from UTC at the specified date.
	 */
	virtual int64 getUTCOffset (const Date* date) const = 0;

	/**
     * Queries if the given date is in daylight saving time.
     *
     * @return true if daylight saving time is in effective at the
     * given date; false otherwise.
     */
    virtual bool inDaylightTime (const Date* date) const = 0;
  
  	String getDisplayName (void) const
  	{
  		return _displayName;
  	}
  	
protected:
	String _displayName;  
}; // End class TimeZone	


#endif // __DTL_SYS_TIMEZONE_H__
