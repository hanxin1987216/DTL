/***************************************************************************************************
sha1.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	sha1 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-18
 ****************************************************************/

#include "sha1tc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Sha1TestCase);

#define STR_1_FOR_SHA1 "01B307ACBA4F54F55AAFC33BB06BBBF6CA803E9A"
#define STR_2_FOR_SHA1 "5DFAC39F71AD4D35A153BA4FC12D943A0E178E6A"
#define STR_3_FOR_SHA1 "4E174BBC3E0A536AA8899D1F459318F797DC325A"
#define STR_4_FOR_SHA1 "198F529E8A949723231E2A27FA0FAD30486734C2"
#define STR_5_FOR_SHA1 "FCDD5C859549BA4CB355192A5C8EA249CFA72D95"
#define STR_6_FOR_SHA1 "088FB1A4AB057F4FCF7D487006499060C7FE5773"
#define STR_7_FOR_SHA1 "30A47D966E96EF820533B160CD25BC61CE71EC7C"
#define STR_8_FOR_SHA1 "6DF68AECF315BFA0A5B6C5F373AB03B4EBCA018E"
#define STR_9_FOR_SHA1 "5CAD520EB5060F1264EE6F2758A9DC5B4003B5C9"

#define	LEN 6
#define BUF_SIZE 20

void
Sha1TestCase::setUp(void) {}

void
Sha1TestCase::tearDown(void) {}

void 
Sha1TestCase::testSHA1(void)
{
	unsigned char output_buf[BUF_SIZE];
	
	//数字
	String str1 = "1234567890";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str1.getCStr(), str1.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_1_FOR_SHA1);
	
	//小写字母
	String str2 = "abcdefghijk";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str2.getCStr(), str2.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_2_FOR_SHA1);
	
	//大写字母
	String str3 = "ABCDEFGHIJK";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str3.getCStr(), str3.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_3_FOR_SHA1);

 	//特殊符号
	String str4 = "!@#$%^&*)(";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str4.getCStr(), str4.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_4_FOR_SHA1);
	 
 	//中文
	String str5 = "今天是九一八";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str5.getCStr(), str5.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_5_FOR_SHA1); 
	 
	//空格---3个空格
	String str6 = "   ";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str6.getCStr(), str6.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_6_FOR_SHA1);
	
	//字符里面含空格
	String str7 = "a b c d";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str7.getCStr(), str7.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_7_FOR_SHA1);
	 
	//中文含空格
	String str8 = "今 天 是 九 一 八";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str8.getCStr(), str8.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_8_FOR_SHA1);
	 
	//混合 大小写字符,中文，空格,特殊字符
	String str9 = "今 天 是 九 一 八ab cdE FG% ^&";
	memset(output_buf, 0, BUF_SIZE);
	SHA1Hash::encode((unsigned char *)str9.getCStr(), str9.getLength(), output_buf);
	CPPUNIT_ASSERT (SHA1Hash::toString(output_buf) == STR_9_FOR_SHA1); 	 
} 