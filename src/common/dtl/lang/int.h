/***************************************************************************************************
int.h:	
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

#ifndef __DTL_INT_H__
#define __DTL_INT_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "string.h"

/**
 * This class represents a 32-bit signed int type.
 */
class DTL_DLLEXPORT Int
{
public:
	Int (void);
	~Int (void);

// static contant
public:
	/**
	 * The contant represents the largest value of an int type. 
	 */
	static const int MAX_VALUE;
	
	/**
	 * The contant represents the smallest value of an int type. 
	 */
	static const int MIN_VALUE;

	/**
	 * The constant represents the an infinite interval when wait.
	 */
	static const int INFINITE_VALUE;

// static method
public:
	/** 
	 * Returns a string representing the specified integer.  
	 *
	 * @param i	The integer to get its string.
	 * @return The string representation of the specified integer.
	 */
	static String toString (int i)
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
	static int getValue (const String& s);
	
	/**
	 * Determines the string whether or not be an integer.
	 * The empty string always return false.
	 *
	 * @param s		The string to check.
	 *
	 * @return false If the string contains any other character not be [0-9],
	 * 		   true if the string is a integer.
	 */
	static bool isInteger (const String& s)
	{
		
		return isInteger (s.getCStr (),
							   s.getLength ());

							   

	}
	
	/**
	 * Determines the C-style string whether or not be an integer.
	 * The empty or null string always return false.
	 *
	 * @param chars	The C-style string to check.
	 *
	 * @return false If the string contains any other character not be [0-9],
	 * 		   true if the string is a integer.
	 */
	static bool isInteger (const tchar_t* chars)
	{
		
#ifdef __UNICODE__			
		return chars ? isInteger (chars, t_strlen (chars)) : false;
#else
		return chars ? isInteger (chars, ::strlen (chars)) : false;
#endif


	}
	
	/**
	 * Determines the string whether or not be an integer.
	 * The empty string always return false.
	 *
	 * @param chars		The C-style string to check.
	 * @param length	The length of the C-style string.
	 * 
	 * @return false If the string contains any other character not be [0-9],
	 * 		   true if the string is a integer.
	 */
	static bool isInteger (const tchar_t* chars, size_t length);
	
}; // End class Int


#endif // __DTL_INT_H__
