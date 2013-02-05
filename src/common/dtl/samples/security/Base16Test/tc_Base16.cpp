#include <dtprec.h>
#include <dtl.h>

int main()   
{   
	char buf[256], base16_encode[512], base16_decode[256], *pch, *pch1;   
	int ix, iLen;   
	
	while(1)   
	{   
		printf("输入要加密的字符串，输入回车退出: \n");   
		fgets(buf, sizeof(buf), stdin);   
		for (ix = strlen(buf) - 1; (ix >= 0) && (buf[ix] == 10); ix--)   
		buf[ix] = 0;   
		if (!buf[0])   
		break;     
		iLen = strlen(buf); 
		Base16::encode (buf, iLen, base16_encode, true);
		printf("\n加密后:\n");   
		for (pch = base16_encode, ix = 0; ix < iLen*2; pch++, ix++)   
        {   
            if (!(ix % 20))   
                printf("\n");   
            printf("%X ", (unsigned char)*pch);   
        } 		
		Base16::decode (base16_encode, iLen*2, base16_decode);    
        base16_decode[iLen] = 0;     
        printf("\n解密后：%s\n", base16_decode);    
	
		//free(base16_encode);   
		//free(base16_decode);   
    }   
    return 0;   
}   
   

