/***************************************************************************************************
httpsockettc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: HttpSocketTest

Author:
	Huang.Xianming

Creating Time:
	2012-04-24
***************************************************************************************************/

#ifndef __HTTP_SOCKET_TEST_H__
#define __HTTP_SOCKET_TEST_H__ 10000001

#if PRAGMA_ONCE
#	pragma once
#endif //PRAGMA_ONCE


#include <cppunit/tester.h>




class HttpSocketTest
	:public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE(HttpSocketTest);
	CPPUNIT_TEST(testPost);
	CPPUNIT_TEST(testGet);
CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);
	
protected:
	void testPost(void);
	void testGet(void);
};








#endif	//__HTTP_SOCKET_TEST_H__
