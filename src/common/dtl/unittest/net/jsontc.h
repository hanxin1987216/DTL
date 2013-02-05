/***************************************************************************************************
jsontc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	jsontc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-20
 ****************************************************************/
#ifndef __JSON_TC_H__
#define __JSON_TC_H__

#include <cppunit/tester.h>

class JsonTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (JsonTestCase);

		CPPUNIT_TEST_DESCRIPTION(testcJSON_Print, _T("测试cJSON_Print, 测试cJSON_Print方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testcJSON_GetArraySize, _T("测试cJSON_GetArraySize, 测试cJSON_GetArraySize方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testcJSON_GetArrayItem, _T("测试cJSON_GetArrayItem, 测试cJSON_GetArrayItem方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testcJSON_GetObjectItem, _T("测试cJSON_GetObjectItem, 测试cJSON_GetObjectItem方法正确性"));

	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testcJSON_Print(void);
	void testcJSON_GetArraySize(void);
	void testcJSON_GetArrayItem(void);
	void testcJSON_GetObjectItem(void);


private:

};

#endif //end  __JSON_TC_H__
