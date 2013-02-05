/***************************************************************************************************
bsontc.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	bsontc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-19
 ****************************************************************/

#include "bsontc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BsonTestCase);

void
BsonTestCase::setUp(void) 
{
}
void
BsonTestCase::tearDown(void)
{	
}

void 
BsonTestCase::testBson_init(void)
{	
	//经过bson_init后，使用bson_size应为5
	bson a;
	bson_init(&a);
	bson_finish(&a);
	
	CPPUNIT_ASSERT(bson_size(&a) == 5); 
	
	bson_destroy (&a);
}

void 
BsonTestCase::testBson_find(void)
{	
	//测试Bson_find的返回值类型
	bson a;
	bson_init(&a);
	bson_iterator it;
	bson_append_string (&a, "name", "yangbing");
	bson_append_bool(&a, "boolortrue", true);
	bson_append_binary (&a, "data", BSON_BIN_BINARY, 0, 0);
	bson_finish (&a);
	
	CPPUNIT_ASSERT(bson_find(&it, &a, "name") == BSON_STRING); 
	CPPUNIT_ASSERT(bson_find(&it, &a, "boolortrue") == BSON_BOOL); 
	CPPUNIT_ASSERT(bson_find(&it, &a, "data") == BSON_BINDATA); 
	
	bson_destroy (&a);
}

void 
BsonTestCase::testBson_iterator_int(void)
{
	//测试testBson_iterator_int返回值是否正确
	bson a;
	bson_init(&a);
	bson_iterator it;
	bson_append_int(&a, "name", 32);
	bson_finish (&a);
	
	const char *data = bson_data(&a);
	bson_iterator_from_buffer (&it, data);
	bson_find(&it, &a, "name");
	
	CPPUNIT_ASSERT(bson_iterator_int(&it) == 32); 
}

 void 
 BsonTestCase::testBson_iterator_string(void)
 {
	//测试testBson_iterator_string和字符串比较
	bson a;
	bson_init(&a);
	bson_iterator it;
	bson_append_string(&a, "name", "yangbing");
	bson_finish (&a);
	
	const char *data = bson_data(&a);
	bson_iterator_from_buffer (&it, data);
	bson_find(&it, &a, "name");
	String str = bson_iterator_string(&it);
	
	CPPUNIT_ASSERT(str.compare("yangbing") == 0); 
}

void 
BsonTestCase::testBson_iterator_bool(void)
{
	//测试testBson_iterator_bool和bson_bool_t类型相比较
	bson a;
	bson_init(&a);
	bson_iterator it;
	bson_append_bool(&a, "bool", true);
	bson_finish (&a);
	
	const char *data = bson_data(&a);
	bson_iterator_from_buffer (&it, data);
	bson_find(&it, &a, "bool");
	
	bson_bool_t bool_t = bson_iterator_bool(&it);
	CPPUNIT_ASSERT(bool_t == true); 
}

void 
BsonTestCase::testBson_append_start_array(void)
{
	//测试bson a中的arry的第一个字段arry[0] == 2
	bson a;
	bson_init(&a);
	bson_iterator it, it_sub;;
	
	bson_append_start_array(&a, "arry");
	bson_append_int(&a, "arry[0]", 2);
	bson_append_int(&a, "arry[1]", 3);
	bson_append_finish_array(&a);
	bson_finish (&a);
	
	const char *data = bson_data(&a);
	bson_iterator_from_buffer (&it, data);
	bson_find(&it, &a, "arry");
	bson_iterator_subiterator(&it, &it_sub);
	bson_iterator_next(&it_sub);
	
	CPPUNIT_ASSERT(bson_iterator_int(&it_sub) == 2);
}

void 
BsonTestCase::testBson_append_start_object(void)
{
	//测试bson a中的object的第一个字段object_1 == 9
	bson a;
	bson_init(&a);
	bson_iterator it, it_sub;;
	
	bson_append_start_object(&a, "object");
	bson_append_int(&a, "object_1", 9);
	bson_append_int(&a, "object_2", 8);
	bson_append_finish_object(&a);
	bson_finish (&a);
	
	const char *data = bson_data(&a);
	bson_iterator_from_buffer (&it, data);
	bson_find(&it, &a, "object");
	bson_iterator_subiterator(&it, &it_sub);
	bson_iterator_next(&it_sub);
	
	CPPUNIT_ASSERT(bson_iterator_int(&it_sub) == 9);
}


