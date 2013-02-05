/***************************************************************************************************
base64tc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Base64 测试

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-20
***************************************************************************************************/
#ifndef __BASE64_TC_H__
#define __BASE64_TC_H__

#include <cppunit/tester.h>


class Base64TestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (Base64TestCase);

		CPPUNIT_TEST_DESCRIPTION (encode,_T("测试Base64,encode 对数据进行编码") );	
		CPPUNIT_TEST_DESCRIPTION (decode,_T("测试Base64,decode 对数据进行解码") );	


	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	
	}
	
	void tearDown (void)
	{
	
	}
	
protected:

	void encode (void);
	void decode (void);

private:
}; // End class Base64TestCase

#endif // __Base64_TC_H__

