/***************************************************************************************************
rc4tc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	rc4 测试

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-116
***************************************************************************************************/
#ifndef __RC4_TC_H__
#define __RC4_TC_H__

#include <cppunit/tester.h>


class Rc4TestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (Rc4TestCase);

		CPPUNIT_TEST_DESCRIPTION (encode,_T("测试RC4,encode 对数据进行编码") );	
		CPPUNIT_TEST_DESCRIPTION (decode,_T("测试RC4,decode 对数据进行解码") );	

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
}; // End class Rc4TestCase

#endif // __RC4_TC_H__

