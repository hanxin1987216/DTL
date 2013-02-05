/***************************************************************************************************
rc4.cpp
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	rc4 编、解码
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/
#include <dtprec.h>
#include "rc4.h"
#include <cassert>


void swapints(int *array, int ndx1, int ndx2)
{
    int temp = array[ndx1];
    array[ndx1] = array[ndx2];
    array[ndx2] = temp;
}

//char *
void
EnDeCrypt(const char *pszText, int iTextLen, const char *pszKey,char *cipher)
/* ;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   ;:::  This routine does all the work. Call it both to ENcrypt    :::
   ;:::  and to DEcrypt your data.                                  :::
   ;:::  You MUST free the returned pointer when no longer needed   :::
   ;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
{
//    char *cipher = NULL;                /* Output buffer                */
    int a, b, i=0, j=0, k;              /* Ambiguously named counters   */
    int ilen;                           /* Length of a string           */
    int sbox[256];                      /* Encryption array             */
    int key[256];                       /* Numeric key values           */

    ilen = strlen(pszKey);

    for (a=0; a < 256; a++)
    {
        key[a] = pszKey[a % ilen];
        sbox[a] = a;
    }

    for (a=0, b=0; a < 256; a++)
    {
        b = (b + sbox[a] + key[a]) % 256;
        swapints(sbox, a, b);
    }

//    cipher = (char *)malloc(iTextLen * sizeof (char));

    for (a=0; a < iTextLen; a++)
    {
        i = (i + 1) % 256;
        j = (j + sbox[i]) % 256;
        swapints(sbox, i, j);
        k = sbox[(sbox[i] + sbox[j]) % 256];
        cipher[a] = (char)(pszText[a] ^ k);
    }
 //   return cipher;
}

bool
RC4::encode(const char *src, const char* key, size_t srclen, char *dest)
{
	assert(src);
    if (src == 0)
        return false;
	
	//if (dest != NULL)
	//{
		//free (dest);
		//dest = NULL;
	//}
		
	EnDeCrypt (src, srclen, key, dest);
	return true;
}


bool
RC4::decode(const char *src, const char* key, size_t srclen, char *dest)
{
	assert(src);
    if (src == 0)
        return false;

	//if (dest != NULL)
	//{
	//	free (dest);
		//dest = NULL;
	//}
	
	EnDeCrypt (src, srclen, key, dest);

	return true;
}
