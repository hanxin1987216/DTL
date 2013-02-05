/***************************************************************************************************
toolstc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	toolstc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-19
 ****************************************************************/
#ifndef __TOOLS_TC_H__
#define __TOOLS_TC_H__

#include <cppunit/tester.h>
#include <dtl/net/tools.h>

class ToolsTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (ToolsTestCase);

		CPPUNIT_TEST_DESCRIPTION(testGetFileValue, _T("测试getFileValue, 测试getFileValue方法正确性"));
		CPPUNIT_TEST_DESCRIPTION(testSetFileValue, _T("测试setFileValue, 测试设置FileValue功能"));
		CPPUNIT_TEST_DESCRIPTION(testGetIP, _T("测试getIP, 测试返回查看IP功能"));
		CPPUNIT_TEST_DESCRIPTION(testGetMac, _T("测试getMac, 测试返回查看Mac功能"));
		CPPUNIT_TEST_DESCRIPTION(testGetNetmask, _T("测试getNetmask, 测试返回查看netmask功能"));
		CPPUNIT_TEST_DESCRIPTION(testGetBroadcast, _T("测试getBroadcast, 测试返回查看Broadcast功能"));
		CPPUNIT_TEST_DESCRIPTION(testSetBroadcast, _T("测试setBrodcast, 测试设置Brodcast功能"));
	
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testGetFileValue(void);
	void testSetFileValue(void);
	void testGetIP(void);
	void testGetMac(void);
	void testGetNetmask(void);
	void testGetBroadcast(void);
	void testSetBroadcast(void);
private:

};

#endif //end  __TOOLS_TC_H__
