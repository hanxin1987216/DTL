/***************************************************************************************************
base64tc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Base64 ≤‚ ‘

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-20
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "base64tc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( Base64TestCase );

void
Base64TestCase::encode (void)
{
	unsigned char in[] = "abc23";
	size_t inLen = 5;
	unsigned char out[15] = {0};
	CPPUNIT_ASSERT ( Base64::encode(in, inLen, out,true) == true);
	CPPUNIT_ASSERT ( String ((tchar_t*)out) == String ("YWJjMjM=") );
}

void
Base64TestCase::decode (void)
{
	unsigned char in[] = "YWJjMjM=";
	size_t inLen = 8;
	unsigned char out[15] = {0};
	CPPUNIT_ASSERT( Base64::decode(in,inLen,out) == true );
	CPPUNIT_ASSERT( String ((tchar_t*)out) == String ("abc23") );
}
