/***************************************************************************************************
sha1.h
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	sha1 编、解码
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/

#ifndef __ENCODE_SHA1__H__
#define __ENCODE_SHA1__H__

#include "../prec.h"
#include "../lang/string.h"
/**
 * \brief          SHA-1 context structure
 */
typedef struct
{
    unsigned long total[2];     /*!< number of bytes processed  */
    unsigned long state[5];     /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */

    unsigned char ipad[64];     /*!< HMAC: inner padding        */
    unsigned char opad[64];     /*!< HMAC: outer padding        */
}sha1_context;


class DTL_DLLEXPORT SHA1Hash
{
public:

	/**
	 * brief          Output = SHA-1( input buffer )
	 *
	 * @param input    buffer holding the  data
	 * @param ilen     length of the input data
	 * @param output   SHA-1 checksum result
	 */
	static void encode (unsigned char *input, int ilen, unsigned char output[20] );
	
	/**
	 * 转换为16进制可读字符串
	 * @return  返回一个可读的40个字节的字符串
	 * @param   digest 传入的不可读20个字节的编码		
	 * @param   uppercase 大小写设定，默认是大写
	 */
	static String toString(unsigned char digest[20], bool uppercase = true);
};


class DTL_DLLEXPORT SHA1HMACHash
{
public:

	/**
	 * brief          Output = SHA-1 HMAC( input buffer )
	 *
	 * @param input    buffer holding the  data
	 * @param ilen     length of the input data
	 * @param output   SHA-1 HMAC checksum result
	 */
	static void encode ( unsigned char *key, int keylen, unsigned char *input, int ilen, unsigned char output[20] );
	
	/**
	 * 转换为16进制可读字符串
	 * @return  返回一个可读的40个字节的字符串
	 * @param   digest 传入的不可读20个字节的编码		
	 * @param   uppercase 大小写设定，默认是大写
	 */
	static String toString(unsigned char digest[20], bool uppercase = true);
};


#endif // __ENCODE_SHA1__H__
