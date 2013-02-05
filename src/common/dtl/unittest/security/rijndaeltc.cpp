/***************************************************************************************************
rijndaeltc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Rijndael 测试

Author:
	yan.zhineng@datatom.com

Creating Time:
	2012-3-20
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "rijndaeltc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( RijndaelTestCase );

void
RijndaelTestCase::init (void)
{
/*	RD_UINT8 inputBuf[256], passwd[16], Encrypted[512], Decrypted[256], *pch;   
	int ix, iLen; 
	
	while(1)   
	{   
		printf("Please enter your plain code and press the Enter: \n");   
		fgets((char*)inputBuf, sizeof(inputBuf), stdin);   
		for (ix = strlen((char*)inputBuf) - 1; (ix >= 0) && (inputBuf[ix] == 10); ix--)   
		inputBuf[ix] = 0;   
		if (!inputBuf[0])   
		break;   
		printf("\nPlease enter the key: ");   
		fgets((char*)passwd, sizeof(passwd), stdin);   
		for (ix = strlen((char*)passwd) - 1; (ix >= 0) && (passwd[ix] == 10); ix--)   
		passwd[ix] = 0;   
		if (!passwd[0])   
		break;   
		iLen = strlen((char*)inputBuf); 
		//int init (Mode mode,Direction dir,const RD_UINT8 *key,KeyLength keyLen,RD_UINT8 * initVector = 0);
		Rijndael zts;
		//zts.init (Rijndael::ECB, Rijndael::Encrypt, passwd, Rijndael::Key16Bytes);
		//zts.init (Rijndael::ECB, (Rijndael::Direction)0, passwd, (Rijndael::KeyLength)0, (RD_UINT8*)0);
		//int blockEncrypt(const RD_UINT8 *input, int inputLen, RD_UINT8 *outBuffer);
		
		zts.blockEncrypt (inputBuf, iLen, Encrypted);
		printf("\n加密后:\n");   
		for (pch = Encrypted, ix=0; ix < (iLen*2); pch++, ix++)   
        {   
            if (!(ix % 20))   
                printf("\n");   
            printf("%X ", (unsigned char)*pch);   
        }   
		//int blockDecrypt(const RD_UINT8 *input, int inputLen, RD_UINT8 *outBuffer);
		//zts.init (Rijndael::ECB, Rijndael::Decrypt, passwd, Rijndael::Key16Bytes);
		//zts.init ((Rijndael::Mode)0, (Rijndael::Direction)1, passwd, (Rijndael::KeyLength)0, (RD_UINT8*)0);
		zts.blockDecrypt (Encrypted, iLen*2, Decrypted); 
     //   Decrypted[iLen] = 0;     
        printf("\n解密后： %s\n", Decrypted);   
        
	}*/
	
		//	int init(Mode mode,Direction dir,const RD_UINT8 *key,KeyLength keyLen,RD_UINT8 * initVector = 0);
		
		
	// Input data

	RD_UINT8 key[] = "dfa";                       // The key
//	initializeYour256BitKey();                   // Obviously initialized with sth
	RD_UINT8 * plainText = (RD_UINT8 *)"fdsasdf2345tregu"; // Your plain text
	int plainTextLen = 16;      // Plain text length
	
	// Encrypting
	Rijndael rin;
	RD_UINT8 output[32];
	
	rin.init(Rijndael::CBC,Rijndael::Encrypt,key,Rijndael::Key32Bytes);
	// It is a good idea to check the error code
	int len = rin.padEncrypt(plainText,plainTextLen,output);
	cout << len << endl;
//	if(len >= 0)
//	cout << (char*)output << endl;
//	useYourEncryptedText();
//	else encryptError(len);
	
	// Decrypting: we can reuse the same object
	unsigned char output2[16];
	rin.init(Rijndael::CBC,Rijndael::Decrypt,key,Rijndael::Key32Bytes);
	int len1 = rin.padDecrypt(output,32,output2);
	cout << len1;
	if(len1 >= 0)
	cout << output2 << endl;
}
