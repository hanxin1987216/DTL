/***************************************************************************************************
int64.cpp:	
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
#include "int64.h"
#include "../sys/exception.h"


const int64 Int64::MAX_VALUE = __INT64_C(0x7FFFFFFFFFFFFFFF);
const int64 Int64::MIN_VALUE = __INT64_C(0x8000000000000000);

// public ctor
Int64::Int64 (void)
{
	// Do nothing
}

// public dtor
Int64::~Int64 (void)
{
	// Do nothing
}

// public static 
int64 
Int64::getValue (const String& s)
{
	if (s.isEmpty () == true)
		THROW ("Int64 getvalue param str is null");
	
	// _wtoi() cannot get the zero value, so check it before calling.
	const tchar_t* ptr = s.getCStr ();
	size_t len = s.getLength ();
	size_t i = 0;
	for (; i < len; ++i)
		if (ptr[i] != '0')
			break;
			
	if (i == len)
		return 0;

#ifdef __WINDOWS__
	int64 value = ::_wtoi64 (ptr);	
#elif defined(__HPPA__) && defined(__HPPA_V1__)
	tchar_t* endptr;
	long_double num = strtold(ptr, &endptr);
	
	int64 value = (*(long double*) &num);
#else
	tchar_t* endptr;
	int64 value = strtoll(ptr, &endptr, 10);
#endif
	if (value == 0) {
		String msg = "convert string to int64 error";
#ifdef __WINDOWS__
		THROW (msg);
#else
		THROW (msg);
#endif
	}

	return value;
}
