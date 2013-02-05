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

#include "../prec.h"
#include "int.h"
#include "../sys/exception.h"
	
const int Int::MAX_VALUE = 0x7FFFFFFF;
const int Int::MIN_VALUE = 0x80000000;
const int Int::INFINITE_VALUE = -1;

// public ctor
Int::Int (void)
{
	// Do nothing
}

// public dtor
Int::~Int (void)
{
	// Do nothing
}

// public static 
int 
Int::getValue (const String& s)
{
	// TODO: pls reimplement it.
	if (s.isEmpty () == true)
		THROW ("param is null");
	
	// _wtoi() cannot get the zero value, so check it before calling.
	const tchar_t* ptr = s.getCStr ();
	size_t len = s.getLength ();
	size_t i = 0;
	for (; i < len; ++i)////假如*ptr不为0，break
		if (ptr[i] != '0')
			break;
			
	if (i == len)/////假如*ptr为0，return 0
		return 0;

#ifdef __WINDOWS__
	int value = ::_wtoi (ptr);	
#else
	tchar_t* endptr;
	int value = strtol(s.getCStr(), &endptr, 10);///以十进制输出
#endif
	if (value == 0) {
		String msg ("Int getValue error");
#ifdef __WINDOWS__
		THROW (msg);
#else
		THROW (msg);
#endif
	}

	return value;
}

// public static 
bool 
Int::isInteger (const tchar_t* chars, size_t length)
{	

	
	if (chars == NULL || length == 0)
		return false;
		
	size_t i = 0;
	while (i < length) {
		if (isdigit(chars[i]) == false)
			return false;
			
		++i;
	}
		
		
	return true;
}
