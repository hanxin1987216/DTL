/***************************************************************************************************
Test_base16
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	对base16 编、解码的测试
	
Auther:
	郑挺松 zheng.tingsong@datatom.com              

Created Time:
	2012-2-3
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>


//unsigned char source[17] = "0123456789aBcdEf";
//unsigned char decode_buf[17] = {0};
//unsigned char encode_buf[17*2];

char source[10] = "012345678";
char decode_buf[10] = {0}; 
char encode_buf[10*2];

void encode()
{   
	int count = 9;
	int i = 0;
	cout << "begin encode" << endl;
	Base64 zts_1;
	/**
    * 对数据进行编码
    * @param in: 要编码的数据
    * @param inLen: 要编码的数据长度（字节数）
    * @param out: [out]缓冲区，存放编码后的数据（至少是2倍inLen大）
    * @param capital: 编码中的字母是否大小；取值true表示大写（默认），false表示小写
    * @return: 如果@in或者@out为空指针，则编码失败并返回false；否则成功，返回true。
    */
     i = zts_1.encode(source, 10, encode_buf, true);
	 if (i == 0)
	 printf("编码失败!\n");
	 else
	 printf("编码成功!\n");
	 for (int j=0; j<count; j++)
	{
		//cout << (unsigned char) encode_buf[i];
		printf("%02x",encode_buf[j]);
	}
	cout << endl;
}


int main()
{
    memset( encode_buf, 0, 10*2 );
	encode();
}

