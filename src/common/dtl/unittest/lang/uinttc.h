// Unit Test code for class cpp::lang::Int

#ifndef __UINTTC_H__
#define __UINTTC_H__

#include <cppunit/tester.h>


class UIntTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (UIntTestCase);

		CPPUNIT_TEST_DESCRIPTION (toString,_T("测试uint toString 把uint型的数转换为字符串"));	
		
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
	
}; // End class IntTestCase

#endif // __INTTC_H__

