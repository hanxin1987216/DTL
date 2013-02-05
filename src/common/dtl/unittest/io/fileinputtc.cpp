/***************************************************************************************************
fileinputtc.cpp:	
	Copyright (c) Datatom Software, Inc.(2004 - 2009), All rights reserved

Purpose:
	 Unit Test code for class cpp::io::FileInputStream


Author:
	hanxin
Creating Time:
	2008.5.21
***************************************************************************************************/

#include <dtprec.h>
#include <dtl/dtl.h>
#include <cppunit/tester.h>
#include "fileinputtc.h"


CPPUNIT_TEST_SUITE_REGISTRATION( FileInputStreamTestCase );

#define TEST_FILE_NAME _T("fin_test")
#define TEST_FILE_NAME1 _T("fin_test1")

void FileInputStreamTestCase::setUp (void)
{
	FileOutputStream out (TEST_FILE_NAME, CREATE_NEW_MODE);
	const char* str = "Test line 1\r\nTest line 2\r\nTest line 3";
	out.write ((const unsigned char*)str, strlen (str));
}
	
void FileInputStreamTestCase::tearDown (void)
{
	File file (TEST_FILE_NAME);
	file.remove ();
}
	
// protected
void 
FileInputStreamTestCase::ctors (void)
{	
	FileInputStream fin (TEST_FILE_NAME);
	
	File file (TEST_FILE_NAME);
	
	FileInputStream fin2(TEST_FILE_NAME, READ_SHARE);
	CPPUNIT_ASSERT_THROW (FileInputStream (TEST_FILE_NAME, WRITE_SHARE), Exception);
	fin2.close ();
	fin.close ();
	
	FileInputStream fin3(TEST_FILE_NAME, NONE_SHARE);
	CPPUNIT_ASSERT_THROW (FileInputStream (TEST_FILE_NAME, READ_SHARE), Exception);
	
}


// protected
void 
FileInputStreamTestCase::getFileName (void)
{
	FileInputStream fin (TEST_FILE_NAME);
	CPPUNIT_ASSERT (fin.getFileName () == String (TEST_FILE_NAME));
	
	fin.close ();
}



// protected
void 
FileInputStreamTestCase::read (void)
{
	FileInputStream fin (TEST_FILE_NAME);
	
	int byte = fin.read ();
	CPPUNIT_ASSERT ( (char)byte == 'T');
	byte = fin.read ();
	CPPUNIT_ASSERT ((char)byte == 'e');
	
	unsigned char readBuf[11];
	CPPUNIT_ASSERT (fin.read(readBuf, 10) == 10);
	readBuf[10] = 0;
	CPPUNIT_ASSERT (strncmp ((char*) readBuf, "st line 1\r", 10) == 0);
	
	CPPUNIT_ASSERT (fin.read(readBuf, 4) == 4);
	CPPUNIT_ASSERT (strncmp ((char*) readBuf, "\nTes", 4) == 0);
	
	CPPUNIT_ASSERT_THROW (fin.read (0, 0), Exception);
	
	CPPUNIT_ASSERT ((char)fin.read () == 't');
	CPPUNIT_ASSERT (fin.read(readBuf, 0) == 0);
	CPPUNIT_ASSERT (fin.read(readBuf, 10) == 10);
	CPPUNIT_ASSERT (fin.read(readBuf, 4) == 4);
	CPPUNIT_ASSERT (fin.read(readBuf, 10) == 6);
	CPPUNIT_ASSERT (fin.read(readBuf, 4) == -1);
	CPPUNIT_ASSERT (fin.read() == -1);

	fin.close ();
}

// protected
void 
FileInputStreamTestCase::seek (void)
{
	FileInputStream fin (TEST_FILE_NAME);	
	
	CPPUNIT_ASSERT_THROW (fin.seek (-1, BEGIN_ORIGIN), Exception);
	CPPUNIT_ASSERT (fin.seek (3, BEGIN_ORIGIN) == 3);
	CPPUNIT_ASSERT (fin.seek (21, BEGIN_ORIGIN) == 21);	
	CPPUNIT_ASSERT (fin.seek (38, BEGIN_ORIGIN) == 38);
	
	CPPUNIT_ASSERT (fin.seek (-7, CURRENT_ORIGIN) == 31);
	CPPUNIT_ASSERT (fin.seek (2, CURRENT_ORIGIN) == 33);
	CPPUNIT_ASSERT_THROW (fin.seek (-73, CURRENT_ORIGIN), Exception);
	CPPUNIT_ASSERT (fin.seek (24, CURRENT_ORIGIN) == 57);
	CPPUNIT_ASSERT (fin.seek (24, CURRENT_ORIGIN) == 81);
	
	CPPUNIT_ASSERT_THROW (fin.seek (-46, END_ORIGIN), Exception);
	CPPUNIT_ASSERT (fin.seek (-2, END_ORIGIN) == 35);	
	CPPUNIT_ASSERT (fin.seek (4, END_ORIGIN) == 41);
		
	fin.close ();

}

// protected
void 
FileInputStreamTestCase::close (void)
{
	FileInputStream fin (TEST_FILE_NAME);
	CPPUNIT_ASSERT ((char)fin.read () == 'T');
	fin.close ();	

}

// protected
void 
FileInputStreamTestCase::available (void)
{
	FileInputStream fin (TEST_FILE_NAME);
	
	CPPUNIT_ASSERT (fin.available () == 37);
	fin.read ();
	CPPUNIT_ASSERT (fin.available () == 36);
	fin.read ();
	CPPUNIT_ASSERT (fin.available () == 35);
	
	unsigned char readBuf[4];
	fin.read(readBuf, 4);
	CPPUNIT_ASSERT (fin.available () == 31);
	
	fin.read(readBuf, 2);
	CPPUNIT_ASSERT (fin.available () == 29);
	
	fin.close ();	
}

