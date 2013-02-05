/***************************************************************************************************
base64.h
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	base64 加密算法
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/

#ifndef __BASE64__H__
#define __BASE64__H__

/**
* Base64编码/解码的工具类。
* 所有成员均为静态成员。
*/

class DTL_DLLEXPORT Base64
{
public:
    /**
    * 对数据进行编码
    * @param in: 要编码的数据
    * @param inLen: 要编码的数据长度（字节数）
    * @return:  返回加密后的字符串
    */
    static String encode(const unsigned char *in, size_t inLen);

    /**
    * 对数据进行解码
    * @param in: 要解码的数据
    * @param inLen: 要解码的数据的长度
    * @param outLen: 解码字符串的内容长度
    * @return: 解码结果字符串
    */
    static String decode(const unsigned char *in, size_t inLen, int& outLen);
};


#endif // __BASE64__H__
