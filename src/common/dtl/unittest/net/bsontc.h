/***************************************************************************************************
bsontc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	bsontc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-19
 ****************************************************************/
#ifndef __BSON_TC_H__
#define __BSON_TC_H__

#include <cppunit/tester.h>
//#include <dtl/net/bson.h>

class BsonTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (BsonTestCase);

		CPPUNIT_TEST_DESCRIPTION(testBson_init, _T("测试bson_init, 测试bson_init方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_find, _T("测试bson_find, 测试bson_find方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_iterator_int, _T("测试bson_iterator_int, 测试bson_iterator_int方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_iterator_string, _T("测试bson_iterator_string, 测试bson_iterator_string方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_iterator_bool, _T("测试bson_iterator_bool, 测试bson_iterator_bool方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_append_start_array, _T("测试bson_append_start_array, 测试bson_append_start_array方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testBson_append_start_object, _T("测试bson_append_start_object, 测试bson_append_start_object方法正确性"));
			
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testBson_init(void);
	void testBson_find(void);
	void testBson_iterator_int(void);
	void testBson_iterator_string(void);
	void testBson_iterator_bool(void);
	void testBson_append_start_array(void);
	void testBson_append_start_object(void);

private:

};

#endif //end  __BSON_TC_H__
