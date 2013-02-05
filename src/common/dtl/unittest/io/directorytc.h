/***************************************************************************************************
directorytc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Directory 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-19
***************************************************************************************************/
#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <cppunit/tester.h>


class DirectoryTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (DirectoryTestCase);

		CPPUNIT_TEST_DESCRIPTION (testExists, _T("测试Directory, exists"));	
		CPPUNIT_TEST_DESCRIPTION (testGetName, _T("测试Directory, getName是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testCreate, _T("测试Directory, create是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testCreateSubDirectory, _T("测试Directory, createSubDirectory是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testList, _T("测试Directory, list是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testListDirs, _T("测试Directory, listDirs是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testListFiles, _T("测试Directory, listFiles是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetParent, _T("测试Directory, listFiles是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsRoot, _T("测试Directory, isRoot是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testRemove, _T("测试Directory, remove, removeTree是否正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
    void testExists(void);
    void testGetName(void);
    void testCreate(void);
    void testCreateSubDirectory(void);
    void testList(void);
    void testListDirs(void);
    void testListFiles(void);
    void testGetParent(void);
    void testIsRoot(void);
    void testRemove(void);

private:
}; // End class DirectoryTestCase

#endif // __DIRECTORY_H__

