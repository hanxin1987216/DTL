/***************************************************************************************************
pathtc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Path 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-15
***************************************************************************************************/
#ifndef __PATH_TC_H__
#define __PATH_TC_H__

#include <cppunit/tester.h>


class PathTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (PathTestCase);

		CPPUNIT_TEST_DESCRIPTION (testConst, _T("测试Path, static const values"));	
		CPPUNIT_TEST_DESCRIPTION (testCombine, _T("测试Path, combine 是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testMakeFullPath, _T("测试Path, makeFullPath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsAbsolutePath, _T("测试Path, isAbsolutePath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetCurrentPath, _T("测试Path, getCurrentPath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetDirectoryName, _T("测试Path, getDirectoryName是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetFileName, _T("测试Path, getFileName是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetPathRoot, _T("测试Path, getPathRoot是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testChangeExtension, _T("测试Path, testChangeExtension是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testAddExtension, _T("测试Path, testAddExtension是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetExtensionName, _T("测试Path, testGetExtensionName是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsValidPath, _T("测试Path, testIsValidPath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetCurrentModulePath, _T("测试Path, testGetCurrentModulePath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testEqual, _T("测试Path, testEqual是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testIsParentPath, _T("测试Path, testIsParentPath是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetInvalidPathChars, _T("测试Path, testGetInvalidPathChars是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetSeparatorChars, _T("测试Path, testGetSeparatorChars是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testAdaptSep, _T("测试Path, testAdaptSep是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testSplit, _T("测试Path, testSplit是否正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);

	
	void tearDown (void);
	
protected:
    void testConst(void);
    void testCombine(void);
    void testMakeFullPath(void);
    void testIsAbsolutePath(void);
    void testGetCurrentPath(void);
    void testGetDirectoryName(void);
    void testGetFileName(void);
    void testGetPathRoot(void);
    void testChangeExtension(void);
    void testAddExtension(void);
    void testGetExtensionName(void);
    void testIsValidPath(void);
    void testGetCurrentModulePath(void);
    void testEqual(void);
    void testIsParentPath(void);
    void testGetInvalidPathChars(void);
    void testGetSeparatorChars(void);
    void testAdaptSep(void);
    void testSplit(void);
private:
}; // End class PathTestCase

#endif // __PATH_TC_H__

