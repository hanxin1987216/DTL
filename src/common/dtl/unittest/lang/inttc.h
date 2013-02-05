// Unit Test code for class cpp::lang::Int

#ifndef __INTTC_H__
#define __INTTC_H__

#include <cppunit/tester.h>


class IntTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (IntTestCase);

		CPPUNIT_TEST_DESCRIPTION (isInteger, _T("测试Int isInteger 判断整形是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (getValue,_T("测试Int getValue 取整形的具体值"));
		CPPUNIT_TEST_DESCRIPTION (toString,_T("测试Int toString 把整形数以字符串的形式输出"));
		
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void)
	{
	}
	
	void tearDown (void)
	{
	}
	
protected:
	void isInteger (void);
	void getValue (void);
	void toString (void);
}; // End class IntTestCase

#endif // __INTTC_H__

