/***************************************************************************************************
Test_base16
 	Copyright (c) Datatom Co., Ltd.(2012 - 2013), All rights reserved.

Purpose:
	��base16 �ࡢ����Ĳ���
	
Auther:
	֣ͦ�� zheng.tingsong@datatom.com              

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
    * �����ݽ��б���
    * @param in: Ҫ���������
    * @param inLen: Ҫ��������ݳ��ȣ��ֽ�����
    * @param out: [out]����������ű��������ݣ�������2��inLen��
    * @param capital: �����е���ĸ�Ƿ��С��ȡֵtrue��ʾ��д��Ĭ�ϣ���false��ʾСд
    * @return: ���@in����@outΪ��ָ�룬�����ʧ�ܲ�����false������ɹ�������true��
    */
     i = zts_1.encode(source, 10, encode_buf, true);
	 if (i == 0)
	 printf("����ʧ��!\n");
	 else
	 printf("����ɹ�!\n");
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

