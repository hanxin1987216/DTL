/***************************************************************************************************
exceptiontc.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Exception 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-15
***************************************************************************************************/
#ifndef __EXCEPTION_TC_H__
#define __EXCEPTION_TC_H__

#include <cppunit/tester.h>


class ExceptionTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (ExceptionTestCase);

		CPPUNIT_TEST_DESCRIPTION (testGetMessage, _T("测试Exception, getMessage返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testToString, _T("测试Exception, toString返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetAdditionalInfo, _T("测试Exception, getAdditionalInfo返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testToFullString, _T("测试Exception, toFullString返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testClone, _T("测试Exception, clone返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetBaseException, _T("测试Exception, getBaseException返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetErrorId, _T("测试Exception, getErrorId返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testErrorProvider, _T("测试Exception, setErrorProvider, getErrorProvider返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testGetCause, _T("测试Exception, getCause返回是否正确"));	
		CPPUNIT_TEST_DESCRIPTION (testOperatorAssign, _T("测试Exception, getCause返回是否正确"));	

	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);
	
	void tearDown (void);
	
protected:
    void testGetMessage(void);
    void testToString(void);
    void testGetAdditionalInfo(void);
    void testToFullString(void);
    void testClone(void);
    void testGetBaseException(void);
    void testGetErrorId(void);
    void testErrorProvider(void);
    void testGetCause(void);
    void testOperatorAssign(void);
private:
}; // End class ExceptionTestCase

#endif // __EXCEPTION_TC_H__

