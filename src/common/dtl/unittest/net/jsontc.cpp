/***************************************************************************************************
jsontc.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	jsontc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-20
 ****************************************************************/

#include "jsontc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(JsonTestCase);

void
JsonTestCase::setUp(void) 
{
}
void
JsonTestCase::tearDown(void)
{	
}

void 
JsonTestCase::testcJSON_Print(void)
{	
 	//创建一个object，设置key=number，value=100，cJSON_Print打印出结果应为“100”
	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "number", 100);
	string str = cJSON_Print(cJSON_GetObjectItem(root, "number"));
	
	CPPUNIT_ASSERT(str.compare("100") == 0);
}

void 
JsonTestCase::testcJSON_GetArraySize(void)
{
	//创建一个array使用cJSON_GetArraySize，返回值应为4
	cJSON *array;
	array = cJSON_CreateArray();
	
	cJSON_AddItemToArray(array, cJSON_CreateNumber(10));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(20));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(30));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(40));
	
	CPPUNIT_ASSERT(cJSON_GetArraySize(array) == 4); 
}

void 
JsonTestCase::testcJSON_GetArrayItem(void)
{
	//创建一个array使用cJSON_GetArrayItem，返回值应为“20”
	cJSON *array;
	array = cJSON_CreateArray();
	
	cJSON_AddItemToArray(array, cJSON_CreateNumber(10));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(20));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(30));
	cJSON_AddItemToArray(array, cJSON_CreateNumber(40));
	
	string str = cJSON_Print(cJSON_GetArrayItem(array, 1));
	//字符串20比较
	CPPUNIT_ASSERT(str.compare("20") == 0);
}

void 
JsonTestCase::testcJSON_GetObjectItem(void)
{
	//创建一个object使用cJSON_GetObjectItem，返回值应为“200”
	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "code", 200);
	string str = cJSON_Print(cJSON_GetObjectItem(root, "code"));
	//与字符串200相比较
	CPPUNIT_ASSERT(str.compare("200") == 0);
}





