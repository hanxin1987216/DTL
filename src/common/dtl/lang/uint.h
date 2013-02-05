/***************************************************************************************************
int.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes:
	#Unint: Represents a 64-bit signed int type.

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_UINT_H__
#define __DTL_UINT_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT UInt
{
public:
	UInt (void);
	~UInt (void);

// static contant
public:
	/**
	 * The contant represents the largest value of an int type. 
	 */
	static const unsigned int MAX_VALUE;
	
	/**
	 * The contant represents the smallest value of an int type. 
	 */
	static const unsigned int MIN_VALUE;		

// static method
public:
	/** 
	 * Returns a string representing the specified integer.  
	 *
	 * @param i 	The unsigned integer to get its string.
	 * @return The string representation of the specified integer.
	 */
	static String toString (unsigned int i)
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
	static unsigned int getValue (const String& s);
	
}; // End class Int


#endif // __DTL_INT_H__
