/***************************************************************************************************
jsontextwriter.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	jsontextwriter 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-21
 ****************************************************************/

#include "jsontextwritertc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(JsonTextWriterTestCase);

void
JsonTextWriterTestCase::setUp(void) 
{
}
void
JsonTextWriterTestCase::tearDown(void)
{	
}

void 
JsonTextWriterTestCase::testStartArray(void)
{	
 	JsonTextWriter jsontextwrite;
	
	jsontextwrite.StartArray("array");
	jsontextwrite.WriteElement ("array[0]", 0);
	jsontextwrite.WriteElement ("array[1]", 1);
	jsontextwrite.WriteElement ("array[2]", 2);
	jsontextwrite.EndArray();
	
	cJSON *json = cJSON_Parse(jsontextwrite.getJsonStr ().getCStr());
	
	string str1 = cJSON_Print(cJSON_GetArrayItem(json, 0));
	string str2 = cJSON_Print(cJSON_GetArrayItem(json, 1));
	string str3 = cJSON_Print(cJSON_GetArrayItem(json, 2));
	
	CPPUNIT_ASSERT((str1.compare("0") == 0) 
		 		 &&(str2.compare("1") == 0)
				 &&(str3.compare("2") == 0)
				); 
}

void 
JsonTextWriterTestCase::testStartObject(void)
{
	JsonTextWriter jsontextwrite;
	
	jsontextwrite.StartObject("object");
	jsontextwrite.WriteElement("int1", 3);
	jsontextwrite.WriteElement("int2", 4);
	jsontextwrite.WriteElement("int3", 5);
	jsontextwrite.EndObject();
	
	cJSON *json = cJSON_Parse(jsontextwrite.getJsonStr ().getCStr());
	string str1 = cJSON_Print(cJSON_GetObjectItem(json, "int1"));
	string str2 = cJSON_Print(cJSON_GetObjectItem(json, "int2"));
	string str3 = cJSON_Print(cJSON_GetObjectItem(json, "int3"));
	
	CPPUNIT_ASSERT((str1.compare("3") == 0) 
		 		 &&(str2.compare("4") == 0)
				 &&(str3.compare("5") == 0)
				);
}

void 
JsonTextWriterTestCase::testWriteElement(void)
{
	JsonTextWriter jsontextwrite;
	
	jsontextwrite.StartObject("object");
	jsontextwrite.WriteElement("str_", "value");
	jsontextwrite.WriteElement("int_", 123);
	jsontextwrite.WriteElement("bool_", true);
	jsontextwrite.WriteNull("NULL_");
	jsontextwrite.EndObject();
	
	cJSON *json = cJSON_Parse(jsontextwrite.getJsonStr ().getCStr());
	string str_value  = cJSON_Print(cJSON_GetObjectItem(json, "str_"));
	string int_value  = cJSON_Print(cJSON_GetObjectItem(json, "int_"));
	string bool_value = cJSON_Print(cJSON_GetObjectItem(json, "bool_"));
	
	CPPUNIT_ASSERT((str_value.compare("\"value\"") == 0) 
		 		 &&(int_value.compare("123") == 0)
				 &&(bool_value.compare("true") == 0)
				);
}













