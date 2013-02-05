/***************************************************************************************************
dateformat.h:	
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

#ifndef __DTL_SYS_DATEFORMAT_H__
#define __DTL_SYS_DATEFORMAT_H__

#include "date.h"

#if PRAGMA_ONCE
#pragma once
#endif

#include "../lang/string.h"
	

/**
time string format pattern			description
<pre>
 H							Hour in 24-hour format (0–23),Single-digit hours will not have a leading zero. 
 HH							Hour in 24-hour format (00–23)
 h							Hour in 12-hour format (0-12),Single-digit hours will not have a leading zero. 
 hh							Hour in 12-hour format (00–12) 
 m							Minute as decimal number (0–59),Single-digit hours will not have a leading zero. 
 mm							Minute as decimal number (00–59) 
 s							Second as decimal number (0–59),Single-digit hours will not have a leading zero.  
 ss							Second as decimal number (00–59)
 y							Year without century, as decimal number (0–99).If the year without the century is less than 10, the year is displayed with no leading zero.
 yy							Year without century, as decimal number (00–99)
 yyyy						Year with century, as decimal number 
 M							Month as decimal number (1-12).Single-digit months will not have a leading zero.
 MM							Month as decimal number (01-12).
 MMM						The abbreviated name of the month
 MMMM						The full name of the month
 d							Day of month as decimal number (1–31),Single-digit days will not have a leading zero.
 dd							Day of month as decimal number (01–31)
 e							The abbreviated name of the day of the week
 E							The full name of the day of the week
 w							Weekday as decimal number (0 – 6; Sunday is 0) 
 W							Week of year as decimal number, with Monday as first day of week (00 – 53)
 p							Current locale's A.M./P.M. indicator for 12-hour clock 
 g							Era abbreviated name
 G							Era full name
 z							Time zone abbreviated name
 zz							Time zone abbreviated name tailed with the full time zone offset ("+" or "-" followed by the hour and minutes). 
 Z							Time zone full name
 ZZ							Time zone abbreviated name tailed with the full time zone offset ("+" or "-" followed by the hour and minutes). 
 O							Time zone offset ("+" or "-" followed by the hour like "+0800"   China.
 'str'						Where str is any string. Displays the character literally. To display the ' character, use ''.
 </pre>
 */

class DTL_DLLEXPORT DateFormat
{
// Ctors and dtor
public:
 	/**
 	 *
 	 */
	DateFormat (void);
	
	/**
 	 *
 	 */
	virtual ~DateFormat (void);

// static members
public:
	/**
 	 *
 	 */
	// Local date format instance
	static const DateFormat* getLocalInstance (void); 
	
	/**
 	 *
 	 */
	static void delLocalInstance (void);

private:
	static DateFormat* _localInst;

// Public members
public:
	/**
 	 *
 	 */
	virtual String format (const Date* date, int pattern) const = 0;
	
	/**
 	 *
 	 */
	virtual String formatTime (const Date* date, int pattern) const = 0;
	
	/**
 	 *
 	 */
	virtual String formatDay (const Date* date, int pattern) const = 0;

	/**
 	 *
 	 */					   
	virtual String format (const Date* date, 
						   const String& pattern) const = 0;
						   
	/**
 	 *
 	 */
	// @throw FormatException if the string is unexpected
	virtual int64 parse (const String& str) const = 0;		
	
	/**
 	 *
 	 */					   
	virtual int64 parse (const String& str, const String& pattern) const = 0;
	
	/**
 	 *
 	 */					   
	virtual String getFormatPattern (FullDatePattern pattern) = 0;

	/**
 	 *
 	 */					   
	virtual String getFormatPattern (DatePattern pattern) = 0;

	/**
 	 *
 	 */					   
	virtual String getFormatPattern (TimePattern pattern) = 0;

protected:		
	/**
 	 *
 	 */					   
	virtual String doFormat (const Locale* locale,
							 const Date* date, 
						   	 const String& pattern) const;
						   
	virtual bool doParse (const Locale* locale,
						  const String& str, 
						  const String& pattern, 
						  int64& time /* OUT */) const;

}; // End class DateFormat	




class DTL_DLLEXPORT LocaleDateFormat : public DateFormat
{
public:	// Ctors and dtor

 	/**
 	 *
 	 */
	LocaleDateFormat (const Locale* locale);	

// Overriden methods
public:
	/**
 	 *
 	 */
	virtual String format (const Date* date, int pattern) const;
	
	/**
 	 *
 	 */
	virtual String formatTime (const Date* date, int pattern) const;
	
	/**
 	 *
 	 */
	virtual String formatDay (const Date* date, int pattern) const;

	/**
 	 *
 	 */					   
	virtual String format (const Date* date, 
						   const String& pattern) const;
						   
	/**
 	 *
 	 * @throw FormatException if the string is unexpected
 	 */
	virtual int64 parse (const String& str) const;	
	
	/**
 	 *
 	 */					   
	virtual int64 parse (const String& str, const String& ptn) const;

	/**
 	 *
 	 */					   
	virtual String getFormatPattern (FullDatePattern pattern);

	/**
 	 *
 	 */					   
	virtual String getFormatPattern (DatePattern pattern);

	/**
 	 *
 	 */					   
	virtual String getFormatPattern (TimePattern pattern);

private:
	const Locale* _locale;
	
}; // End class LocaleDateFormat

#endif // __DTL_SYS_DATEFORMAT_H__
