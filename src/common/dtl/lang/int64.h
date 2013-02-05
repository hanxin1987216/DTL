/***************************************************************************************************
int64.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:
	#Int64: Represents a 64-bit signed int type.

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL__INT64_H__
#define __DTL__INT64_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "string.h"

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT Int64
{
public:
	Int64 (void);
	~Int64 (void);

// static contant
public:
	/**
	 * The contant represents the largest value of an int type. 
	 */
	static const int64 MAX_VALUE;
	
	/**
	 * The contant represents the smallest value of an int type. 
	 */
	static const int64 MIN_VALUE;
// static method
public:
	/** 
	 * Returns a string representing the specified integer.  
	 *
	 * @param i	The integer to get its string.
	 * @return The string representation of the specified integer.
	 */
	static String toString (int64 i)
	{
		return String::toString (i);
	}	
	
	/**
	 * Returns the integer value of the string. The radix of the string
	 *	is based 10.
	 *
	 * @param s		The string to be parsed.
	 * @throw FormatException if the string doesn't contain a parsable 
	 *		  integer or be empty string.
	 * @return The integer value represented by the string.
	 */
	static int64 getValue (const String& s);
	
	
}; // End class Int64

#endif // __DTL__INT64_H__
