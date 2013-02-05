// Unit Test code for class cpp::lang::Int

#ifndef __STREAMWRITERTC_H__
#define __STREAMWRITERTC_H__

#include <cppunit/tester.h>

class StreamWriterTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (StreamWriterTestCase);
	CPPUNIT_TEST (reopen);
	CPPUNIT_TEST (flush);	
	CPPUNIT_TEST (close);
	CPPUNIT_TEST (writeChar);	
	CPPUNIT_TEST (writeChars);
	CPPUNIT_TEST (writeString);
	CPPUNIT_TEST (writeLine);
	CPPUNIT_TEST (writeLines);
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	}
	void tearDown (void)
	{
	}
	
protected:
	void reopen (void);
	void flush (void);
	void close (void);
	void writeChar (void);
	void writeChars (void);
	void writeString (void);
	void writeLine (void);
	void writeLines (void);
}; // End class StreamWriterTestCase


#endif // __STREAMWRITERTC_H__

