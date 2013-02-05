/***************************************************************************************************
rc4tc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Rc4 测试

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-20
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "rc4tc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( Rc4TestCase );

void
Rc4TestCase::encode (void)
{
	char *str = "hanxindljfadjfajklkajjdjj";
	char *pwd = "23";
	int len = strlen (str);
	char *pEncrypted = (char *)malloc(len + 1);
	
	RC4::encode (str, pwd, strlen (str) +1, pEncrypted);	
	pEncrypted[len + 1] = '\0';
	
	//cout << "---------encode out:" << "len=" << strlen (pEncrypted) << "str=" << pEncrypted << endl;
	
	
	char *out_t = (char *)malloc (strlen (pEncrypted) + 1);
	RC4::decode(pEncrypted, pwd, strlen (pEncrypted) + 1, out_t);
	//cout << "-----------decode:" << out_t << endl;

	CPPUNIT_ASSERT (String(str) == String (out_t));
	
	free (pEncrypted);
	pEncrypted = 0;

	free (out_t);
	out_t = 0;
}


void 
Rc4TestCase::decode (void)
{
	char *str = "hanxindljfadjfajklkajjdjj";
	char *pwd = "23";
	int len = strlen (str);
	char *pEncrypted = (char *)malloc(len + 1);
	
	RC4::encode (str, pwd, strlen (str) +1, pEncrypted);	
	pEncrypted[len + 1] = '\0';
	
	//cout << "---------encode out:" << "len=" << strlen (pEncrypted) << "str=" << pEncrypted << endl;
	
	
	char *out_t = (char *)malloc (strlen (pEncrypted) + 1);
	RC4::decode(pEncrypted, pwd, strlen (pEncrypted) + 1, out_t);
	//cout << "-----------decode:" << out_t << endl;

	CPPUNIT_ASSERT (String(str) == String (out_t));
	
	free (pEncrypted);
	pEncrypted = 0;

	free (out_t);
	out_t = 0;
}

