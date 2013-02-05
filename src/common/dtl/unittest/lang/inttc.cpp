#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "inttc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( IntTestCase );


void
IntTestCase::isInteger (void)
{
	CPPUNIT_ASSERT (Int::isInteger (_T("1234")) == true);
	
	String str;
	CPPUNIT_ASSERT (Int::isInteger (str) == false);
	
	str = _T("abcd");
	CPPUNIT_ASSERT (Int::isInteger (str) == false);
	
	str = _T("32a");
	CPPUNIT_ASSERT (Int::isInteger (str) == false);
	
	str = _T("9098890");
	CPPUNIT_ASSERT (Int::isInteger (str) == true);
	
	CPPUNIT_ASSERT (Int::isInteger (_T("123a"), 3) == true);
	CPPUNIT_ASSERT (Int::isInteger (_T("12346"), 2) == true);
	CPPUNIT_ASSERT (Int::isInteger (_T(""), 0) == false);
	CPPUNIT_ASSERT (Int::isInteger (_T("a"), 1) == false);
	
	CPPUNIT_ASSERT (Int::isInteger (0, 1) == false);
	CPPUNIT_ASSERT (Int::isInteger (0) == false);
}

void
IntTestCase::getValue (void)
{
    String str ( "123456789" );
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 123456789  );

	str = "0123789";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 123789  );

	str = " 123456555";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 123456555 );

	str = "    12";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 12 );

	str = "1   2";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 1 );

	str = "12   ";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 12 );

	str = "3ds34";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 3 );
	
	str = " -2 ";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == -2 );
	
	str = " -1 ";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == -1 );
	
	str = " 23";
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 23 );
	
	str = "012" ;
	CPPUNIT_ASSERT ( Int::getValue ( str ) == 12 );
}

void
IntTestCase::toString (void)
{
	String str;
	str = Int::toString ( 6 );
	CPPUNIT_ASSERT (  str  == String ("6")  );

	str = Int::toString ( 556 );
	CPPUNIT_ASSERT (  str  == String ("556")  );

	str = Int::toString ( 0x16 );
	CPPUNIT_ASSERT (  str  == String ("22")  );

	str = Int::toString ( 011);
	CPPUNIT_ASSERT (  str  == String ("9")  );

	str = Int::toString ( 0000 );
	CPPUNIT_ASSERT (  str  == String ("0")  );

	str = Int::toString ( 0006 );
	CPPUNIT_ASSERT (  str  == String ("6")  );

	str = Int::toString ( 'a' );
	CPPUNIT_ASSERT (  str  == String ("97")  );

	str = Int::toString ( 1234);
	CPPUNIT_ASSERT (  str  == String ("1234")  );
	
	str = Int::toString ( -2 );
	CPPUNIT_ASSERT (  str  == String ("-2")  );

	str = Int::toString ( -1 );
	CPPUNIT_ASSERT (  str  == String ("-1")  );
}