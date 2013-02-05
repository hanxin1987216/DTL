#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "filetc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( FileTestCase );

#define TEST_FILE_NAME		_T("file.test")
#define TEST_FILE_NAME1	_T("file.test1")
#define TEST_FILE_NAME2	_T("file.test2")
#define TEST_FILE_NAME3	_T("file.test3")

#define TEST_FILE_CONTENT "This text is for testing purpose."

#ifdef __WINDOWS__
#	define TEST_FILE_CONENT_LEN  33
#else
#	define TEST_FILE_CONENT_LEN  37
#endif


void 
FileTestCase::setUp (void)
{
	FileOutputStream fout (TEST_FILE_NAME, CREATE_MODE);	
	fout.write ((const unsigned char*) TEST_FILE_CONTENT, TEST_FILE_CONENT_LEN);
	FileOutputStream fout1 (TEST_FILE_NAME1, CREATE_MODE);	
}
	
void 
FileTestCase::tearDown (void)
{
	File file(TEST_FILE_NAME);
	file.remove ();	
	
	File file1(TEST_FILE_NAME1);
	file1.remove ();	
}

// protected
void 
FileTestCase::ctors (void)
{	
	File (TEST_FILE_NAME);
#ifdef __WINDOWS__
	CPPUNIT_ASSERT_THROW (File (_T("   ")), ArgumentException);
#endif
}

// protected
void 
FileTestCase::getLength (void)
{
	File file (TEST_FILE_NAME);
	CPPUNIT_ASSERT ((file.getLength () == TEST_FILE_CONENT_LEN));
	
	File file1 (TEST_FILE_NAME1);
	CPPUNIT_ASSERT ((file1.getLength () == 0));	
	
	File file2 (TEST_FILE_NAME2);
	CPPUNIT_ASSERT ((file2.getLength () == 0));
}

// protected
void 
FileTestCase::isReadonly (void)
{
	File file(TEST_FILE_NAME);
	CPPUNIT_ASSERT ((file.isReadonly () == false));
	
	File file1 (TEST_FILE_NAME1);
	CPPUNIT_ASSERT ((file1.isReadonly () == false));	
	
	File file2 (TEST_FILE_NAME2);
	CPPUNIT_ASSERT ((file2.isReadonly () == false));
}


// protected
void 
FileTestCase::remove (void)
{
	File file(_T("test_remove"));
	file.create ();

	CPPUNIT_ASSERT (file.exists () == true);
	
	file.remove ();
	CPPUNIT_ASSERT (file.exists () == false);

		
	// 第二次删除抛异常
	CPPUNIT_ASSERT_THROW (file.remove (), Exception);		
}

// protected
void 
FileTestCase::exists (void)
{
	File file(TEST_FILE_NAME);	
	CPPUNIT_ASSERT (file.exists () == true);
	
	File file1(TEST_FILE_NAME1);	
	CPPUNIT_ASSERT (file1.exists () == true);
	
	File file2(TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.exists () == false);
}

// protected
void 
FileTestCase::getName (void)
{
	File file(TEST_FILE_NAME);	
	CPPUNIT_ASSERT (file.getName () == TEST_FILE_NAME);
	
	File file1(TEST_FILE_NAME1);	
	CPPUNIT_ASSERT (file1.getName () == TEST_FILE_NAME1);
	
	File file2(TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getName () == TEST_FILE_NAME2);
}

// protected
void 
FileTestCase::getFullName (void)
{
#ifdef __WINDOWS__
	File file(TEST_FILE_NAME);	
	CPPUNIT_ASSERT (file.getFullName () == Path::combine (Path::getCurrentModulePath (), TEST_FILE_NAME));
	
	File file1(TEST_FILE_NAME1);	
	CPPUNIT_ASSERT (file1.getFullName () == Path::combine (Path::getCurrentModulePath (), TEST_FILE_NAME1));
	
	File file2(TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getFullName () == Path::combine (Path::getCurrentModulePath (), TEST_FILE_NAME2));
	
	File file3(_T("D:\\test.txt"));
	CPPUNIT_ASSERT (file3.getFullName () == _T("D:\\test.txt"));
	
	File file4(_T("mydir\\test.txt"));
	CPPUNIT_ASSERT (file4.getFullName () == Path::combine (Path::getCurrentModulePath (), _T("mydir\\test.txt")));
#else
	File file(TEST_FILE_NAME);	
	CPPUNIT_ASSERT (file.getFullName () == _T("/mnt/win/dtl/unittest/cpp/io/file.test"));
	
	File file1(TEST_FILE_NAME1);	
	CPPUNIT_ASSERT (file1.getFullName () == _T("/mnt/win/dtl/unittest/cpp/io/file.test1"));
	
	File file2(TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getFullName () == _T("/mnt/win/dtl/unittest/cpp/io/file.test2"));
	
	File file3(_T("/mnt/test.txt"));
	CPPUNIT_ASSERT (file3.getFullName () == _T("/mnt/test.txt"));
	
	File file4(_T("mydir/test.txt"));
	CPPUNIT_ASSERT (file4.getFullName () == _T("/mnt/win/dtl/unittest/cpp/io/mydir/test.txt"));
#endif
}

// protected
void 
FileTestCase::refresh (void)
{
	File file(TEST_FILE_NAME);
	File file1(TEST_FILE_NAME);
	
	CPPUNIT_ASSERT (file.isReadonly () == false);
	CPPUNIT_ASSERT (file1.isReadonly () == false);
	
	file.setReadonly (true);
	CPPUNIT_ASSERT (file.isReadonly () == true);
	CPPUNIT_ASSERT (file1.isReadonly () == false);
	
	file1.refresh ();
	CPPUNIT_ASSERT (file1.isReadonly () == true);
	
	file.setReadonly (false); // restore.
}

// protected
void 
FileTestCase::getLastModified (void)
{
	File file (TEST_FILE_NAME);
#ifdef __WINDOWS__

	file.setLastModified (1234);	
	CPPUNIT_ASSERT (file.getLastModified () == 1234);
#else
	//file.setLastModified (12340000000LL);	
	//CPPUNIT_ASSERT (file.getLastModified () == 12340000000LL);
#endif	
	File file2 (TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getLastModified () == 0);	
}

// protected
void 
FileTestCase::getCreationTime (void)
{
	File file (TEST_FILE_NAME);
#ifdef __WINDOWS__
	file.setCreationTime (1234);	
	CPPUNIT_ASSERT (file.getCreationTime () == 1234);
#else
	// in linux, can not set file creation time.
	/*file.setCreationTime (12340000000LL);	
	CPPUNIT_ASSERT (file.getCreationTime () == 12340000000LL);*/
#endif	
	File file2 (TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getCreationTime () == 0);	
}

// protected
void 
FileTestCase::getLastAccess (void)
{
	File file (TEST_FILE_NAME);
#ifdef __WINDOWS__
	file.setLastAccess (1234);	
	CPPUNIT_ASSERT (file.getLastAccess () == 1234);
#else
	//file.setLastAccess (12340000000LL);	
	//CPPUNIT_ASSERT (file.getLastAccess () == 12340000000LL);
#endif	
	File file2 (TEST_FILE_NAME2);	
	CPPUNIT_ASSERT (file2.getLastAccess () == 0);	
}

// protected
void 
FileTestCase::getFileAttrs (void)
{
	File file (TEST_FILE_NAME);
	CPPUNIT_ASSERT (file.getFileAttrs () == ARCHIVE);
	
	File file1 (TEST_FILE_NAME1);
	CPPUNIT_ASSERT (file1.getFileAttrs () == ARCHIVE);
	
	File file2 (TEST_FILE_NAME2);
	CPPUNIT_ASSERT (file2.getFileAttrs () == INVALID_FILE);	
}

void
FileTestCase::rename (void)
{
	File file(TEST_FILE_NAME);	
	
	File file2(TEST_FILE_NAME3);
	
	file.rename (TEST_FILE_NAME3);
	CPPUNIT_ASSERT (file.getName () == TEST_FILE_NAME3);
	CPPUNIT_ASSERT (file.getFullName () == Path::makeFullPath (TEST_FILE_NAME3));
	CPPUNIT_ASSERT (file.exists () == true);
	
	file2.refresh ();
	CPPUNIT_ASSERT (file2.exists () == true);
	
	file2.remove ();
}

void 
FileTestCase::create (void)
{
	File file2(TEST_FILE_NAME3);
	if (file2.exists ())
		file2.remove ();
	
	file2.create ();
	CPPUNIT_ASSERT (file2.exists () == true);

	file2.remove ();
}

void 
FileTestCase::truncate (void)
{
	File file (TEST_FILE_NAME);
	File file1 (TEST_FILE_NAME1);
	File file2 (TEST_FILE_NAME3);
	
	CPPUNIT_ASSERT (file.truncate (10) == 10);	
	CPPUNIT_ASSERT (file.getLength () == 10);	
	
	CPPUNIT_ASSERT (file1.truncate (10) == 0);
	CPPUNIT_ASSERT (file1.getLength () == 0);
	
	CPPUNIT_ASSERT (file2.truncate (10) == 0);
	CPPUNIT_ASSERT (file2.getLength () == 0);
}
