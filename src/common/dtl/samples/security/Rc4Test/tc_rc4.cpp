#include <dtprec.h>
#include <dtl.h>

char *EnDeCrypt(const char *pszText, int iTextLen, const char *pszKey);    

int main()   
{   
	char buf[256], passwd[16], *pEncrypted, *pDecrypted, *pch;   
	int ix, iLen;   
	
	pEncrypted = NULL;
	pDecrypted = NULL;
	
	while(1)   
	{   
		printf("输入要加密的字符串，输入回车退出: \n");   
		fgets(buf, sizeof(buf), stdin);   
		for (ix = strlen(buf) - 1; (ix >= 0) && (buf[ix] == 10); ix--)   
		buf[ix] = 0;   
		if (!buf[0])   
		break;   
		printf("\n输入密钥: ");   
		fgets(passwd, sizeof(passwd), stdin);   
		for (ix = strlen(passwd) - 1; (ix >= 0) && (passwd[ix] == 10); ix--)   
		passwd[ix] = 0;   
		if (!passwd[0])   
		break;   
		iLen = strlen(buf); 
		RC4::encode (buf, passwd, iLen, &pEncrypted);
		//pEncrypted = EnDeCrypt(buf, iLen, passwd);
		printf("\n加密后:\n");   
		for (pch = pEncrypted, ix=0; ix < iLen; pch++, ix++)   
        {   
            if (!(ix % 20))   
                printf("\n");   
            printf("%X ", (unsigned char)*pch);   
        }   
		RC4::decode (pEncrypted, passwd, iLen, &pDecrypted); 
		//pDecrypted = EnDeCrypt(pEncrypted, iLen, passwd);   
        pDecrypted[iLen - 1] = 0;     
        printf("\n解密后： %s\n", pDecrypted);   
        
		if (pEncrypted == NULL)
			free(pEncrypted);   
        if (pDecrypted == NULL)
			free(pDecrypted);   
    }   
    return 0;   
}   
   
