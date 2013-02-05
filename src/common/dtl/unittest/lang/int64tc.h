// Unit Test code for class cpp::lang::Int

#ifndef __INT64TC_H__
#define __INT64TC_H__

#include <cppunit/tester.h>


class Int64TestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (Int64TestCase);

		CPPUNIT_TEST_DESCRIPTION (toString,_T("测试int64 toString 把int64型的整数转换为字符串"));	
		CPPUNIT_TEST_DESCRIPTION (getValue,_T("测试int64  getValue 取得int64的具体值"));
		
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	}
	
	void tearDown (void)
	{
	}
	
protected:
	void toString (void);
	void getValue (void);
	
}; // End class IntTestCase

#endif // __INTTC_H__

