/***************************************************************************************************
fileoutputtc.cpp:	
	Copyright (c) Datatom Software, Inc.(2004 - 2009), All rights reserved

Purpose:
	 Unit Test code for class cpp::io::FileOutputStream


Author:
	hanxin
Creating Time:
	2008.5.21
***************************************************************************************************/

#include <dtprec.h>
#include <cppunit/tester.h>
#include "fileoutputtc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( FileOutputStreamTestCase );

#define TEST_FILE_NAME _T("fout_test")
#define TEST_FILE_NAME1 _T("fout_test1")

// protected
void 
FileOutputStreamTestCase::setUp (void)
{
}

// protected
void 
FileOutputStreamTestCase::tearDown (void)
{	
	File file (TEST_FILE_NAME);
	if (file.exists ())
		file.remove ();
}

// protected
void 
FileOutputStreamTestCase::ctors (void)
{		

	File f1 (TEST_FILE_NAME);
	if (f1.exists () == false)
		f1.create ();

	// open mode
	FileOutputStream fout (TEST_FILE_NAME, OPEN_MODE);
	fout.close ();
	

	// open or create mode
	File file (TEST_FILE_NAME);
	FileOutputStream fout1 (file, OPEN_OR_CREATE_MODE);
	fout1.close ();
	

	// read_share
	FileOutputStream fout2(TEST_FILE_NAME, CREATE_MODE, READ_SHARE);
	fout2.close ();	
}

// protected
void 
FileOutputStreamTestCase::write (void)
{
	File f (TEST_FILE_NAME);
	if (f.exists ())
		f.remove ();

	FileOutputStream out (TEST_FILE_NAME, CREATE_NEW_MODE);
	const char* str = "Test line 1\r\nTest line 2\r\nTest line 3";
	out.write ((const unsigned char*)str, strlen (str));	
	out.close ();


	File ff (TEST_FILE_NAME);
	CPPUNIT_ASSERT (ff.getLength () == strlen (str));


	File filer (TEST_FILE_NAME1);
	if (filer.exists ())
		filer.remove ();

	FileOutputStream fout5(TEST_FILE_NAME1, APPEND_MODE);
	String s2 = "test line";
	fout5.write ((unsigned char*)s2.getCStr (), s2.getLength ());
	File filetest (TEST_FILE_NAME1);
	CPPUNIT_ASSERT (filetest.getLength () == s2.getLength ());
	fout5.close ();
	
}

// protected
void 
FileOutputStreamTestCase::seek (void)
{
	File ff (TEST_FILE_NAME);
	if (ff.exists () == false)
		ff.create ();

	FileOutputStream fout (TEST_FILE_NAME, OPEN_MODE);	
	String ss = "dflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdja sd";
	fout.write ((unsigned char *)ss.getCStr (), ss.getLength ());
	fout.flush ();
	
	CPPUNIT_ASSERT_THROW (fout.seek (-1, BEGIN_ORIGIN), Exception);
	CPPUNIT_ASSERT (fout.seek (3, BEGIN_ORIGIN) == 3);
	CPPUNIT_ASSERT (fout.seek (21, BEGIN_ORIGIN) == 21);	
	CPPUNIT_ASSERT (fout.seek (38, BEGIN_ORIGIN) == 38);
	
	CPPUNIT_ASSERT (fout.seek (-7, CURRENT_ORIGIN) == 31);
	CPPUNIT_ASSERT (fout.seek (2, CURRENT_ORIGIN) == 33);
	CPPUNIT_ASSERT_THROW (fout.seek (-73, CURRENT_ORIGIN), Exception);
	CPPUNIT_ASSERT (fout.seek (24, CURRENT_ORIGIN) == 57);
	CPPUNIT_ASSERT (fout.seek (24, CURRENT_ORIGIN) == 81);
		
	fout.close ();
}

// protected
void 
FileOutputStreamTestCase::close (void)
{
	File ff (TEST_FILE_NAME);
	if (ff.exists () == false)
		ff.create ();

	FileOutputStream fout (TEST_FILE_NAME, OPEN_MODE);
	CPPUNIT_ASSERT (fout.seek (1, BEGIN_ORIGIN) == 1);
	fout.close ();	
	
}

// protected
void 
FileOutputStreamTestCase::flush (void)
{
	File file (_T("testflush"));	
	if (file.exists ())
		file.remove ();
	
	FileOutputStream fout (_T("testflush"), CREATE_NEW_MODE);

	fout.write ((unsigned char*)"1", 1);
	fout.flush ();
	CPPUNIT_ASSERT (file.getLength () == 1);	


	fout.close ();
	file.remove ();
}


// protected
void 
FileOutputStreamTestCase::getCurrentOffset (void)
{

	File ff (TEST_FILE_NAME);
	if (ff.exists () == false)
		ff.create ();

	FileOutputStream fout (TEST_FILE_NAME, OPEN_MODE);	
	String ss = "dflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdjadflajdkjasldjfaksldjfsalkdjalksdja sd";
	fout.write ((unsigned char *)ss.getCStr (), ss.getLength ());
	fout.flush ();

	fout.seek (3, BEGIN_ORIGIN) ;

	CPPUNIT_ASSERT (fout.getCurrentOffset ()== 3);

	fout.seek (3, CURRENT_ORIGIN) ;
	CPPUNIT_ASSERT (fout.getCurrentOffset ()== 6);

	fout.seek (-2, CURRENT_ORIGIN) ;
	CPPUNIT_ASSERT (fout.getCurrentOffset ()== 4);

}

