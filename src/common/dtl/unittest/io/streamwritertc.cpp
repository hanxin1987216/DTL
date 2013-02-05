#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "streamwritertc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( StreamWriterTestCase );

void
StreamWriterTestCase::reopen (void)
{
	StreamWriter writer ("a.txt");
	writer.close ();
	writer.reopen ();
	writer.writeChar ('c');
	writer.close ();
}

void
StreamWriterTestCase::flush (void)
{
	
}

void
StreamWriterTestCase::close (void)
{
	StreamWriter writer ( "a.txt" , true );
	writer.close (); 
}

void 
StreamWriterTestCase::writeChar (void)
{
	StreamWriter writer ( "a.txt" , true );
	writer.writeChar ( 'a' );
	writer.close();
}

void
StreamWriterTestCase::writeChars (void)
{
	StreamWriter writer ( "a.txt" , true );
	tchar_t * str = "abc";
	writer.writeChars ( str );
	writer.close ();
}

void
StreamWriterTestCase::writeString (void)
{
	StreamWriter writer ("a.txt" , true );
	String str = "cde";
	writer.writeString ( str );
	writer.close ();
	writer.reopen ();
	writer.writeString ( str,'d');
	writer.close ();
}

void
StreamWriterTestCase::writeLine (void)
{	
	StreamWriter writer ("a.txt" , true );
	String str = "women";
	writer.writeLine ( str );
	writer.close ();
}

void
StreamWriterTestCase::writeLines (void)
{
	StreamWriter writer ("a.txt" , true );
	std::vector<String> str;
	str.push_back ( "yan" );
	str.push_back ( "zhi" );
	str.push_back ( "neng" );
	writer.writeLines ( str );
	writer.close ();
}