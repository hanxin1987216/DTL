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

#include "../prec.h"
#include "../mono_base/uglify.h"
#include "catagroy_data.h"


#include "char.h"
#include <wctype.h>


/////////////////////////////////////////////////////////////////////////////////////////////////
// class #Char

const wchar_t Char::MAX_VALUE = 0xFFFF;
const wchar_t Char::MIN_VALUE = 0x0000;

Char::Char (void)
{
}

Char::~Char (void)
{
}

// public static 
bool 
Char::isWhiteSpace (wchar_t ch)
{
	if (category_data [ch] == (unsigned char) SPACE_SEPARATOR)
		return true;
	
	switch (ch) {
		case (wchar_t) 0x9:
		case (wchar_t) 0x0a:
		case (wchar_t) 0x0b:
		case (wchar_t) 0x0c:
		case (wchar_t) 0x0d:
	#ifdef __UNICODE__
		case (wchar_t) 0x85: // NEL 
		case (wchar_t) 0x2028: // Line Separator
		case (wchar_t) 0x2029: // Paragraph Separator	
	#endif
			return true;

		default:
			return false;
	}
}

// public static 
bool 
Char::isDigit (wchar_t ch)
{
	return (category_data [ch] == (unsigned char) DIGIT_NUMBER);
}

// public static 
bool 
Char::isLetter (wchar_t ch)
{
	CharCategory category = (CharCategory)category_data [ch];

	switch (category) {
		case UPPER_LETTER:
		case LOWER_LETTER:
		case TITLE_LETTER:
		case MODIFIER_LETTER:
		case OTHER_LETTER:
			return true;

		default:
			return false;
	}
}

// public static 
bool 
Char::isLower (wchar_t ch)
{
	return (category_data [ch] == (unsigned char) LOWER_LETTER);
}

// public static 
bool 
Char::isUpper (wchar_t ch)
{
	return (category_data [ch] == (unsigned char) UPPER_LETTER);
}

// public static 
bool 
Char::isNumber (wchar_t ch)
{
	CharCategory category = (CharCategory) category_data [ch];

	switch (category) {
		case DIGIT_NUMBER:
		case LETTER_NUMBER:
		case OTHER_NUMBER:
			return true;

		default:
			return false;
	}
}

// public static 
bool 
Char::isPunctuation (wchar_t ch)
{
	CharCategory category = (CharCategory) category_data [ch];

	switch (category) {
		case CONNECTOR_PUNCTUATION:
		case DASH_PUNCTUATION:
		case START_PUNCTUATION:
		case END_PUNCTUATION:
		case INITIAL_QUOTE_PUNCTUATION:
		case FINAL_QUOTE_PUNCTUATION:
		case OTHER_PUNCTUATION:
			return true;

		default:
			return false;
	}
}

// public static 
bool 
Char::isSeperator (wchar_t ch)
{
	CharCategory category = (CharCategory) category_data [ch];

	switch (category) {
		case SPACE_SEPARATOR:
		case LINE_SEPARATOR:
		case PARAGRAPH_SEPARATOR:
			return true;

		default:
			return false;
	}
}

// public static 
bool 
Char::isSymbol (wchar_t ch)
{
	CharCategory category = (CharCategory) category_data [ch];

	switch (category) {
		case MATH_SYMBOL:
		case M_CURRENCY_SYMBOL:
		case MODIFIER_SYMBOL:
		case OTHER_SYMBOL:
			return true;

		default:
			return false;
	}
}

// public static 
wchar_t 
Char::toUpper (wchar_t ch)
{
	return (wchar_t) ::towupper (ch);
}

// public static 
wchar_t 
Char::toLower (wchar_t ch)
{
	return (wchar_t) ::towlower (ch);
}
