#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "int64tc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( Int64TestCase );

void
Int64TestCase::toString (void)
{
	String str;
	str = Int64::toString ( (int64)6 );
	CPPUNIT_ASSERT ( str == String ("6") );

	str = Int64::toString ( (int64)556 );
	CPPUNIT_ASSERT ( str == String ("556") );

	str = Int64::toString ( (int64)0xaa6 );
	CPPUNIT_ASSERT ( str == String ("2726") );

	str = Int64::toString ( (int64)0776 );
	CPPUNIT_ASSERT ( str == String ("510") );

	str = Int64::toString ( (int64)0000 );/////输出0
	CPPUNIT_ASSERT ( str == String ("0") );

	str = Int64::toString ( (int64)0006 );/////输出6
	CPPUNIT_ASSERT ( str == String ("6") );

	str = Int64::toString ( (int64)'a' );
	CPPUNIT_ASSERT ( str == String ("97") );

	str = Int64::toString (1234);
	CPPUNIT_ASSERT ( str == String ("1234") );

	str = Int64::toString ( (int64)-456 );
	CPPUNIT_ASSERT ( str == String ("-456") );
	
	str = Int64::toString ( (int64)0x8000000000000000 );
	CPPUNIT_ASSERT ( str == String ("-9223372036854775808") );
	
	str = Int64::toString ( (int64)Int64::MAX_VALUE );
	CPPUNIT_ASSERT ( str == String ("9223372036854775807" ) );
}


void 
Int64TestCase::getValue (void)
{
	String str ( "123456789" );
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 123456789 );

	str = "0123789";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 123789 );

	str = "   123456555";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 123456555 );

	str = "    12";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 12 );

	str = "1   2";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 1 );
	
	str = "";
	CPPUNIT_ASSERT_THROW ( Int64::getValue ( str ),Exception );
	
	str = "12   ";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == 12 );

	str = "-12";
	CPPUNIT_ASSERT ( Int64::getValue ( str ) == -12 );
}