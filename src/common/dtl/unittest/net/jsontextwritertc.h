/***************************************************************************************************
jsontextwriter.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	jsontextwriter 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-21
 ****************************************************************/
#ifndef __JSONTEXTWRITER_TC_H__
#define __JSONTEXTWRITER_TC_H__

#include <cppunit/tester.h>

class JsonTextWriterTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (JsonTextWriterTestCase);

		CPPUNIT_TEST_DESCRIPTION(testStartArray, _T("测试StartArray, 测试StartArray方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testStartObject, _T("测试StartObject, 测试StartObject方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testWriteElement, _T("测试WriteElement, 测试WriteElement方法正确性"));

	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testStartArray(void);
	void testStartObject(void);
	void testWriteElement(void);


private:

};

#endif //end  __JSONTEXTWRITER_TC_H__
