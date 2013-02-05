/***************************************************************************************************
md5tc.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	MD5 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-18
 ****************************************************************/

#include "md5tc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Md5TestCase);

#define STR_1_FOR_MD5 "E807F1FCF82D132F9BB018CA6738A19F"
#define STR_2_FOR_MD5 "92B9CCCC0B98C3A0B8D0DF25A421C0E3"
#define STR_3_FOR_MD5 "30A4E38230885E27D1BB3FD0713DFA7D"
#define STR_4_FOR_MD5 "C8B7D3270DD521C86838B22EC80306FA"
#define STR_5_FOR_MD5 "B6B9DDF09D11BE9410956FAD6A7B86A1"
#define STR_6_FOR_MD5 "628631F07321B22D8C176C200C855E1B"
#define STR_7_FOR_MD5 "713F592BD537F7725D491A03E837D64A"
#define STR_8_FOR_MD5 "7330F56E9E640E19A22963260C85D374"
#define STR_9_FOR_MD5 "7B5E9F11055E2A529701B05C301A6632"

#define BUF_SIZE 32

void
Md5TestCase::setUp(void) {}

void
Md5TestCase::tearDown(void) {}

void 
Md5TestCase::testMd5(void)
{
	unsigned char output_buf[BUF_SIZE];
	memset(output_buf, 0, BUF_SIZE);
	
	//数字
	String str1 = "1234567890";
	MD5Hash md5_1;
	md5_1.update((const unsigned char*)str1.getCStr(), str1.getLength());
	md5_1.final(output_buf);
	CPPUNIT_ASSERT (md5_1.toString(output_buf) == STR_1_FOR_MD5); 
	
	//小写字母
	String str2 = "abcdefghijk";
	MD5Hash md5_2;
	md5_2.update((const unsigned char*)str2.getCStr(), str2.getLength());
	md5_2.final(output_buf);
	CPPUNIT_ASSERT (md5_2.toString(output_buf) == STR_2_FOR_MD5); 
	
	//大写字母
	String str3 = "ABCDEFGHIJK";
	MD5Hash md5_3;
	md5_3.update((const unsigned char*)str3.getCStr(), str3.getLength());
	md5_3.final(output_buf);
	CPPUNIT_ASSERT (md5_3.toString(output_buf) == STR_3_FOR_MD5); 
	
	//特殊符号字母
	String str4 = "!@#$%^&*)(";
	MD5Hash md5_4;
	md5_4.update((const unsigned char*)str4.getCStr(), str4.getLength());
	md5_4.final(output_buf);
	CPPUNIT_ASSERT (md5_4.toString(output_buf) == STR_4_FOR_MD5); 
	
	//中文
	String str5 = "今天是九一八";
	MD5Hash md5_5;
	md5_5.update((const unsigned char*)str5.getCStr(), str5.getLength());
	md5_5.final(output_buf);
	CPPUNIT_ASSERT (md5_5.toString(output_buf) == STR_5_FOR_MD5);
	
	//空格---3个空格
	String str6 = "   ";
	MD5Hash md5_6;
	md5_6.update((const unsigned char*)str6.getCStr(), str6.getLength());
	md5_6.final(output_buf);
	CPPUNIT_ASSERT (md5_6.toString(output_buf) == STR_6_FOR_MD5);
	
	//字符里面含空格
	String str7 = "a b c d";
	MD5Hash md5_7;
	md5_7.update((const unsigned char*)str7.getCStr(), str7.getLength());
	md5_7.final(output_buf);
	CPPUNIT_ASSERT (md5_7.toString(output_buf) == STR_7_FOR_MD5);
	
	//中文含空格
	String str8 = "今 天 是 九 一 八";
	MD5Hash md5_8;
	md5_8.update((const unsigned char*)str8.getCStr(), str8.getLength());
	md5_8.final(output_buf);
	CPPUNIT_ASSERT (md5_8.toString(output_buf) == STR_8_FOR_MD5);
	
	//混合 大小写字符,中文，空格,特殊字符
	String str9 = "今 天 是 九 一 八ab cdE FG% ^&";
	MD5Hash md5_9;
	md5_9.update((const unsigned char*)str9.getCStr(), str9.getLength());
	md5_9.final(output_buf);
	CPPUNIT_ASSERT (md5_9.toString(output_buf) == STR_9_FOR_MD5);	
}





