/***************************************************************************************************
toolstc.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	toolstc 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-19
 ****************************************************************/

#include "toolstc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ToolsTestCase);

#define FILE_PATH	"/tmp/toolstcTestFile"
	
#define STR_NAME_1	"aa"
#define STR_NAME_2	"22"
#define STR_NAME_3	"**"
#define STR_NAME_4	"dddd"

#define STR_VALUE_1	"aaaaa"
#define STR_VALUE_2	"22222"
#define STR_VALUE_3	"*****"
#define STR_VALUE_4	"ddddd"

void
ToolsTestCase::setUp(void)
{
	InitDTLibrary ();
 	File file(FILE_PATH);
	file.create();
	StreamWriter streamwriter(FILE_PATH, true);
	streamwriter.writeString("aa=aaaaa\n");
	streamwriter.writeString("22=22222\n");
	streamwriter.writeString("**=*****\n");
	streamwriter.writeString("dddd=ddddd\n");
}

void
ToolsTestCase::tearDown(void) 
{
 	File file(FILE_PATH);
	file.remove();
}

void
ToolsTestCase::testGetFileValue(void)
{
	vector<String> vector;

	//测试FILE_PATH文件的STR_NAME的值是否是STR_VALUE
	Tools::getFileValue(STR_NAME_1, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_1); 
 	
	Tools::getFileValue(STR_NAME_2, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_2); 
	
 	Tools::getFileValue(STR_NAME_3, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_3);
	
	Tools::getFileValue(STR_NAME_4, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_4);
}  

void 
ToolsTestCase::testSetFileValue(void)
{
 	vector<String> vector;
		
	//将STR_NAME_1和2的STR_VALUE互换，3和4亦是如此，检查其正确性
	Tools::setFileValue(STR_NAME_1, STR_VALUE_2, FILE_PATH, 1);
	Tools::getFileValue(STR_NAME_1, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_2); 
	
	Tools::setFileValue(STR_NAME_2, STR_VALUE_1, FILE_PATH, 1);
	Tools::getFileValue(STR_NAME_2, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_1); 
	
	Tools::setFileValue(STR_NAME_3, STR_VALUE_4, FILE_PATH, 1);
	Tools::getFileValue(STR_NAME_3, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_4); 
	
	Tools::setFileValue(STR_NAME_4, STR_VALUE_3, FILE_PATH, 1);
	Tools::getFileValue(STR_NAME_4, vector, FILE_PATH);
	CPPUNIT_ASSERT(vector[0] == STR_VALUE_3);
	
	//将FileValue还原
	Tools::setFileValue(STR_NAME_1, STR_VALUE_1, FILE_PATH, 1);
	Tools::setFileValue(STR_NAME_2, STR_VALUE_2, FILE_PATH, 1);
	Tools::setFileValue(STR_NAME_3, STR_VALUE_3, FILE_PATH, 1);
	Tools::setFileValue(STR_NAME_4, STR_VALUE_4, FILE_PATH, 1); 
}

void 
ToolsTestCase::testGetIP(void)
{
	String ip_str;
	unsigned int symbol_sum = 0;
	
	Tools::getIp("eth0", ip_str);	
	//ip地址一定大于7位小于15位
	CPPUNIT_ASSERT(ip_str.getLength() >= 7 && ip_str.getLength() <= 15);
	for (int i = 0; i < ip_str.getLength(); i++) {
		if (ip_str[i] == '.') {
			symbol_sum++;
		} 
	}
	//ip地址一定有3个'.'
	CPPUNIT_ASSERT(symbol_sum == 3);
}

void
ToolsTestCase::testGetMac(void)
{
	String mac_str;
	unsigned int symbol_sum = 0;
	//mac地址一定等于17位
	Tools::getMac("eth0", mac_str);
	CPPUNIT_ASSERT(mac_str.getLength() == 17);
	for (int i = 0; i < mac_str.getLength(); i++) {
		if (mac_str[i] == '-') {
		symbol_sum++;
		} 
	}
	//mac地址一定有3个'-'
	CPPUNIT_ASSERT(symbol_sum == 5);
}

void
ToolsTestCase::testGetNetmask(void)
{
	String netmask_str;
	unsigned int symbol_sum = 0;
	
	Tools::getNetmask("eth0", netmask_str);
	//netmask地址一定大于7位小于15位
	CPPUNIT_ASSERT(netmask_str.getLength() >= 7 && netmask_str.getLength() <= 15);
	for (int i = 0; i < netmask_str.getLength(); i++) {
		if (netmask_str[i] == '.') {
			symbol_sum++;
		} 
	}
	//netmask地址一定有3个'.'
	CPPUNIT_ASSERT(symbol_sum == 3);
}

void
ToolsTestCase::testGetBroadcast(void)
{
	String broadcast_str;
	unsigned int symbol_sum = 0;
	
	Tools::getBroadcast("eth0", broadcast_str);
	//broadcast地址一定大于7位小于15位
	CPPUNIT_ASSERT(broadcast_str.getLength() >= 7 && broadcast_str.getLength() <= 15);
	for (int i = 0; i < broadcast_str.getLength(); i++) {
		if (broadcast_str[i] == '.') {
			symbol_sum++;
		} 
	}
	//broadcast地址一定有3个'.'
	CPPUNIT_ASSERT(symbol_sum == 3);
}

void
ToolsTestCase::testSetBroadcast(void)
{
	//设置Broadcast
	String set_broadcast_str;
	
	Tools::setBrodcast("192.168.1.1", set_broadcast_str);
	CPPUNIT_ASSERT(set_broadcast_str == "192.168.1.255");
}