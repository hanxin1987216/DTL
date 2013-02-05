#include <dtprec.h>
#include <dtl.h>

unsigned char source[17] = "1A2B3C4D5E6F7G8H";
unsigned char key[33]="abcdefghijklmnopqrst";

unsigned char decode_buf[17];

unsigned char encode_buf[17+16];

void encode ()
{
	int count = 0;
	int i =0;
	RijndaelEncryption encrypt_1 (key, OD_ENCRYPT);
	count = encrypt_1.encode (source, 16, encode_buf);
	
	
	cout << "开始编码:" << endl;
	for (i=0; i<count; i++)
	{
		printf("%02x", encode_buf[i]);
		//cout << (unsigned char) encode_buf[i];
		//cout << encode_buf[i];
	}
	
	cout << endl;
}


void decode ()
{
	int count = 0;
	int i =0;
	cout << "开始解码：" << endl;
	
	RijndaelEncryption encrypt_2 (key, OD_DECRYPT);
	count = encrypt_2.decode (encode_buf, 32, decode_buf);
	
	for (i=0; i<16; i++)
	{
		//printf("%02x",decode_buf[i]);
		cout <<  (unsigned char) decode_buf[i];
	}
	
	cout << endl;
}

int main ()
{
	cout << "原始字符串为:" << endl << source << endl;
	memset (encode_buf, 0, 17 + 16);
	memset (decode_buf, 0, 17);
	encode ();
	decode ();	
}
