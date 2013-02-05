/***************************************************************************************************
char.h:	
	C++ Foundation Library header files
	Copyright (c) DateTome Software Inc.(2012)

Purpose:

Author:
	º«ÐÀ (han.xin@datatom.com)

Creating Time:
	2012-02-07
	
	This library is free software; you can redistribute it and/or modify it under the terms of the 
 	GNU Lesser General Public License as published by the Free Software Foundation; either version 
 	2 of the License, or (at your option) any later version.  	
***************************************************************************************************/

#ifndef __DTL_LANG_CHAR_H__
#define __DTL_LANG_CHAR_H__

#include "string.h"

#if PRAGMA_ONCE
#	pragma once
#endif


/**
 * Character category constant for the Unicode specification.
 * The file and its description about Unicode specification are available 
 *	from the Unicode Consortium at:
 * <a href="http://www.unicode.org">http://www.unicode.org</a> 	 
 */
enum CharCategory
{
	// Letter
	/** General category "Lu" in the Unicode specification. */
	UPPER_LETTER				=  0, // Upper case letter
	
	/** General category "Ll" in the Unicode specification. */
	LOWER_LETTER				=  1, // lower case letter
	
	/** General category "Lt" in the Unicode specification. */
	TITLE_LETTER				=  2, // title case letter
	
	/** General category "Lm" in the Unicode specification. */
	MODIFIER_LETTER				=  3, // modifier letter
	
	/** General category "Lo" in the Unicode specification. */
	OTHER_LETTER				=  4, // Other letter
	
	// Number
	
	/** General category "Nd" in the Unicode specification. */
	DIGIT_NUMBER				=  8, // Decimal digit number
	
	/** General category "Nl" in the Unicode specification. */
	LETTER_NUMBER				=  9, // Letter number
	
	/** General category "No" in the Unicode specification. */
	OTHER_NUMBER				= 10,
	
	// Separator
	
	/** General category "Zs" in the Unicode specification. */
	SPACE_SEPARATOR				= 11,
	
	/** General category "Zl" in the Unicode specification. */
	LINE_SEPARATOR				= 12,
	
	/** General category "Zp" in the Unicode specification. */
	PARAGRAPH_SEPARATOR		    = 13, // Paragraph separator
		
	/** General category "Cc" in the Unicode specification. */
	CONTROL						= 14,
	
	/** General category "Cf" in the Unicode specification. */
	FORMAT						= 15,
	
	/** General category "Cs" in the Unicode specification. */
	SURROGATE					= 16,
	
	/** General category "Co" in the Unicode specification. */
	PRIVATE_USE					= 17,

	// Punctuation
	
	/** General category "Pc" in the Unicode specification. */
	CONNECTOR_PUNCTUATION		= 18,
	
	/** General category "Pd" in the Unicode specification. */
	DASH_PUNCTUATION		    = 19,
	
	/** General category "Ps" in the Unicode specification. */
	START_PUNCTUATION        	= 20,
	
	/** General category "Pe" in the Unicode specification. */
	END_PUNCTUATION        	= 21,
	
	/** General category "Pi" in the Unicode specification. */
	INITIAL_QUOTE_PUNCTUATION	= 22,
	
	/** General category "Pf" in the Unicode specification. */
	FINAL_QUOTE_PUNCTUATION		= 23,
	
	/** General category "Po" in the Unicode specification. */
	OTHER_PUNCTUATION        	= 24,

	// Symbol
	
	/** General category "Sm" in the Unicode specification. */
	MATH_SYMBOL		        	= 25,
	
	/** General category "Sc" in the Unicode specification. */
	M_CURRENCY_SYMBOL				= 26,
	
	/** General category "Sk" in the Unicode specification. */
	MODIFIER_SYMBOL	        	= 27,
	
	/** General category "So" in the Unicode specification. */
	OTHER_SYMBOL			    = 28,
		
	/** General category "Cn" in the Unicode specification. */
	OTHER_NOT_ASSIGNED			= 29,
};

/**
 * This class represents a UNICODE character that is 
 *	charset-dependent and platform-dependent.
 */
class DTL_DLLEXPORT Char
{
public:
	Char (void);
	~Char (void);

// static contant
public:
	/**
	 * The contant represents the largest value of a character. 
	 */
	static const wchar_t MAX_VALUE;
	
	/**
	 * The contant represents the smallest value of a character. 
	 */
	static const wchar_t MIN_VALUE;
	
// static method
public:
	/**
	 * Determines if the specified character is white space in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is white space, otherwise false.
	 */
	static bool isWhiteSpace (wchar_t ch);
	
	/**
	 * Determines if the specified character is a digit in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a digit, otherwise false.
	 */
	static bool isDigit (wchar_t ch);
	
	/**
	 * Determines if the specified character is a letter in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a letter, otherwise false.
	 */
	static bool isLetter (wchar_t ch);

	/**
	 * Determines if the specified character is lower case in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is lower case, otherwise false.
	 */
	static bool isLower (wchar_t ch);
	
	/**
	 * Determines if the specified character is upper case in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is upper case, otherwise false.
	 */
	static bool isUpper (wchar_t ch);
	
	/**
	 * Determines if the specified character is a number in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a number, otherwise false.
	 */
	static bool isNumber (wchar_t ch);
	
	/**
	 * Determines if the specified character is a punctuation in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a punctuation, otherwise false.
	 */
	static bool isPunctuation (wchar_t ch);
	
	/**
	 * Determines if the specified character is a seperator in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a seperator, otherwise false.
	 */
	static bool isSeperator (wchar_t ch);
	
	/**
	 * Determines if the specified character is a symbol in Unicode specification.
	 *
	 * @param ch 	The character to be checked.
	 * @return true if the character is a symbol, otherwise false.
	 */
	static bool isSymbol (wchar_t ch);	

#ifdef __WINDOWS__	
	/** 
	 * Returns a string representing the specified character.  
	 *
	 * @param ch 	The wide character to get its string.
	 * @return The string representation of the specified character.
	 */
	static String toString (wchar_t ch)
	{
		return String (ch, 1);
	}
#else
	/** 
	 * Returns a string representing the specified character.  
	 *
	 * @param ch 	The UTF8 character to get its string.
	 * @return The string representation of the specified character.
	 */
	static String toString (tchar_t ch)
	{
		return String (ch);
	}

	/** 
	 * Returns a string representing the specified character.  
	 *
	 * @param ch 	The wide character to get its string.
	 * @return The string representation of the specified character.
	 */
	static String toString (wchar_t ch)
	{
		wchar_t wchar[2] = {ch, '\0'};

		char* chChar = convertWcharToChar (wchar);
		String tempStr (chChar);
		g_free (chChar);
		return tempStr;
	}
#endif
	
	/**
	 * Converts the character to its uppercase equivalent.
 	 *
 	 * @param ch 	The character to be converted.
 	 * @return  The uppercase equivalent of the character, if any;
 	 *			otherwise, the character itself.
 	 */
 	static wchar_t toUpper (wchar_t ch);
	
	/**
	 * Converts the character to its lowercase equivalent.
 	 *
 	 * @param ch 	The character to be converted.
 	 * @return 	The lowercase equivalent of the character, if any;
 	 *			otherwise, the character itself.
 	 */
	static wchar_t toLower (wchar_t ch);
	
}; // End class Char


#endif // __DTL_LANG_CHAR_H__
