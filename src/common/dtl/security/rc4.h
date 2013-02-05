/***************************************************************************************************
rc4.h
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	rc4 编、解码
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/

#ifndef __ENCODE_RC4__H__
#define __ENCODE_RC4__H__

#include "../prec.h"

void swapints(int *array, int ndx1, int ndx2);


/**
* Base64编码/解码的工具类。
* 所有成员均为静态成员。
*/

class DTL_DLLEXPORT RC4
{
public:
	   /**
    * 对数据进行编码
    * @param in: 要编码的数据
    * @param inLen: 要编码的数据长度（字节数）
    * @param out: [out]缓冲区，存放编码后的数据（长度和要编码的数据长度相当），用完注意释放。
    * @return: 编码失败返回false；成功 返回true。
    */
    static bool encode(const char *in, const char* key, size_t inLen, char *out);

    /**
    * 对数据进行解码
    * @param in: 要解码的数据
    * @param inLen: 要解码的数据的长度（必须为偶数）
    * @param out: [out]缓冲区，存放解码后的数据（长度和要解码的数据长度相当）,用完注意释放。
    * @return: 解码失败，返回false；
    *          解码成功，返回true
    */
    static bool decode(const char *in, const char* key, size_t inLen, char *out);

};

#endif // __ENCODE_RC4__H__
