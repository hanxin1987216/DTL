// Unit Test code for class cpp::lang::Int

#ifndef __FILETC_H__
#define __FILETC_H__

#include <cppunit/tester.h>

class FileTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (FileTestCase);
		CPPUNIT_TEST (ctors);
		CPPUNIT_TEST (getLength);	
		CPPUNIT_TEST (isReadonly);
		CPPUNIT_TEST (remove);	
		CPPUNIT_TEST (exists);
		CPPUNIT_TEST (getName);
		CPPUNIT_TEST (getFullName);
		CPPUNIT_TEST (refresh);
		CPPUNIT_TEST (getLastModified);
		CPPUNIT_TEST (getCreationTime);
		CPPUNIT_TEST (getLastAccess);
		CPPUNIT_TEST (getFileAttrs);
		CPPUNIT_TEST (rename);
		CPPUNIT_TEST (create);
		CPPUNIT_TEST (truncate);
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);
	void tearDown (void);
	
protected:
	void ctors (void);
	void getLength (void);
	void isReadonly (void);
	void remove (void);	
	void exists (void);
	void getName (void);
	void getFullName (void);
	void refresh (void);
	void getLastModified (void);
	void getCreationTime (void);
	void getLastAccess (void);
	void getFileAttrs (void);
	void rename (void);
	void create (void);
	void truncate (void);
}; // End class FileTestCase


#endif // __FILETC_H__

