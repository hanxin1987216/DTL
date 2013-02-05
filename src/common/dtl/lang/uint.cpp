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
#include "string.h"
#include "../sys/exception.h"

#include "uint.h"
	
const unsigned int UInt::MAX_VALUE = 0xFFFFFFFF;
const unsigned int UInt::MIN_VALUE = 0x00000000;		

// public ctor
UInt::UInt (void)
{
	// Do nothing
}

// public dtor
UInt::~UInt (void)
{
	// Do nothing
}

// public static 
unsigned int 
UInt::getValue (const String& s)
{
	// TODO: pls reimplement it.
	if (s.isEmpty () == true)
		THROW ("param is null");
	
	const tchar_t* ptr = s.getCStr ();
	size_t len = s.getLength ();
	size_t i = 0;
	for (; i < len; ++i)////假如*ptr不为0，break
		if (ptr[i] != '0')
			break;
			
	if (i == len)/////假如*ptr为0，return 0
		return 0;

#ifdef __WINDOWS__
	unsigned value = 0;
	//
	// TODO: Windows版本暂不兼容
	//
	THROW ("Windows is not supported UInt::getValue!");
	
#else
	tchar_t* endptr;
	unsigned int value = strtoul(s.getCStr(), &endptr, 10);///以十进制输出
#endif
	if (value == 0) {
		String msg ("UInt getValue error");
#ifdef __WINDOWS__
		THROW (msg);
#else
		THROW (msg);
#endif
	}

	return value;
}