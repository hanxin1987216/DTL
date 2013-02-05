/***************************************************************************************************
base64.h
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	Base64 ±à¡¢½âÂëµÄ²âÊÔ
	
Auther:
	zheng.tingsong   £¨zheng.tingsong@datatom.com£©

Created Time:
	2012-2-9
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>

unsigned char source[10] = "ABCDEFGHI";
unsigned char dest[20];

void
test_encode( void )
{
	int count = 9;
	int j;
	cout << "begin encode" << endl;
	Base64 test;
	int i = test.encode (source, 9, dest, true);
	if (i == 1)
	cout << "success!" << endl;
	else
	cout << "failure!" << endl;
	for (j = 0; j < count; j++)
	{
		cout << (unsigned char) dest[j] << endl;
	}
}

int
main (int argc, char* argv [ ])
{
	memset (dest, 0, 20);
	test_encode ();
	return 0;
}