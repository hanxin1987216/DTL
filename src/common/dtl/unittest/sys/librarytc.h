/***************************************************************************************************
tc_library.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: LibraryTest

Author:
	Huang.Xianming

Creating Time:
	2012-04-25
***************************************************************************************************/

#ifndef __LIBRARY_TEST_HEADER__
#define __LIBRARY_TEST_HEADER__ 3000001

#if PRAGMA_ONCE
	#pragam once
#endif	//PRAGMA_ONCE


#include <cppunit/tester.h>

class LibraryTest
	: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(LibraryTest);
		CPPUNIT_TEST(testLoad);
		CPPUNIT_TEST(testUnload);
		CPPUNIT_TEST(testLoadSymbol);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testLoad(void);
	void testUnload(void);
	void testLoadSymbol(void);

};


#endif		//__LIBRARY_TEST_HEADER__
