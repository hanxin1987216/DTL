#include <dtprec.h>
#include <dtl.h>

int main()   
{   
	RD_UINT8 inputBuf[256], passwd[16], Encrypted[512], Decrypted[256], *pch;   
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
        Decrypted[iLen] = 0;     
        printf("\n解密后： %s\n", Decrypted);   
        

    }   
    return 0;   
}   
   

