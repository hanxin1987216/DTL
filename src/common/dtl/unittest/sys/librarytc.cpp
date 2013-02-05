/***************************************************************************************************
librarytc.cpp:	
	C++ Foundation Library source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the defination of classes: LibraryTest

Author:
	Huang.Xianming

Creating Time:
	2012-04-24
***************************************************************************************************/

#include "librarytc.h"


CPPUNIT_TEST_SUITE_REGISTRATION(LibraryTest);

void LibraryTest::setUp()
{
}

void LibraryTest::tearDown()
{
}

void LibraryTest::testLoad()
{
	//
	//	加载用户库
	//
	String strPath(_T("./libcppunit.so"));
	printf("\n\tLoading custom library %s.", strPath.getCStr());
	void *handle = NULL;
	try
	{
		handle = Library::load(strPath);
	}
	catch (const Exception& e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	CPPUNIT_ASSERT(handle != NULL);
	
	
	Library::unload(handle);				//卸载用户库
	handle = NULL;
	
	
	
	//
	//	加载用户库
	//
	strPath.format("./libdtl.so");
	printf("\n\tLoading custom library %s.", strPath.getCStr());
	try
	{
		handle = Library::load(strPath);
	}
	catch (const Exception& e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	CPPUNIT_ASSERT(handle != NULL);
	
	
	Library::unload(handle);				//卸载用户库
	handle = NULL;
	
	
	
	
	//
	//	加载系统库
	//	未通过
	//
	strPath.format("/usr/lib/libstdc++-3-libc6.2-2-2.10.0.so");
	printf("\n\tLoading system library %s", strPath.getCStr());
	try
	{
		handle = Library::load(strPath);
	}
	catch (const Exception& e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	CPPUNIT_ASSERT(handle != NULL);
	
	
	Library::unload(handle);				//卸载库
	handle = NULL;
	
}

void LibraryTest::testUnload()
{
	String strPath(_T("./libcppunit.so"));
	void *handle = Library::load(strPath);
	try
	{
		Library::unload(handle);
	}
	catch (Exception &e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
}

void LibraryTest::testLoadSymbol()
{
	String strPath(_T("./libdtl.so"));
	
	//
	//	加载库
	//
	void *handle = Library::load(strPath);
	
	//
	//	调用全局变量 
	//	整型变量test定义放在library.cpp中
	//
	
	int test;
	try
	{
		printf("\n\tLoading global variable.");
		test = *(int*)Library::loadSymbol(handle, "test");
	}
	catch (const Exception& e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	printf("\n\tTesting variable:\t%d", test);
	CPPUNIT_ASSERT(test == 155);
	
	//
	//	调用全局函数
	//	函数testFun()定义放在library.cpp中
	//	未通过。
	//
	
	int(*testFunction)();
	try
	{
		printf("\n\tLoading function testFun");
		*(void **)(&testFunction) = Library::loadSymbol(handle, "testFun");
	}
	catch (const Exception& e)
	{
		CPPUNIT_ASSERT_THROW_MESSAGE(e.getMessage().getCStr(), e, Exception);
	}
	printf("\n\tTest function returns:\t%d", testFunction());
	
	
	
	//
	//	卸载库
	//
	Library::unload(handle);
}


