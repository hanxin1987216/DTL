/***************************************************************************************************
base16.cpp
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	base16 编、解码
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/
#include <dtprec.h>
#include "base16.h"



#include <cassert>

const char Base16::sm_capital[17] = "0123456789ABCDEF";
const char Base16::sm_lowercase[17] = "0123456789abcdef";
const char Base16::sm_base16val[128] = {
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
      0,  1,  2,  3,   4,  5,  6,  7,   8,  9,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD, 10, 11, 12,  13, 14, 15,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD, 10, 11, 12,  13, 14, 15,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
    BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
};

/**
* 对数据进行编码
* @param in: 要编码的数据
* @param inLen: 要编码的数据长度（字节数）
* @param out: [out]缓冲区，存放编码后的数据（至少是2倍inLen大）
* @param capital: 编码中的字母是否大小；取值true表示大写（默认），false表示小写
* @return: 如果@in或者@out为空指针，则编码失败并返回false；否则成功，返回true。
*/
bool Base16::encode(const void *in, size_t inLen, char *out, bool capital)
{
    assert(in && out);
    if (in == 0 || out == 0)
        return false;

    const unsigned char *src = reinterpret_cast<const unsigned char *>(in);
    const char *digits = capital ? sm_capital : sm_lowercase;

    for (size_t i = 0; i < inLen; ++i) {
        // 高四位
        int index = src[i] >> 4;
        out[ 2 * i] = digits[index];
        // 低四位
        index = src[i] & 0x0F;
        out[2 * i + 1] = digits[index];
    }

    return true;
}

/**
* 对数据进行编码
* @param in: 要编码的数据
* @param inLen: 要编码的数据长度（字节数）
* @param capital: 编码中的字母是否大小；取值true表示大写（默认），false表示小写
* @return: 如果in为空指针，则编码失败并返回空串；否则成功，返回编码后的字符串数据。
*/
String Base16::encode(const void *in, size_t inLen, bool capital)
{
    assert(in);
    if (in == 0)
        return "";

    char *buf = new char[inLen * 2];

    encode(in, inLen, buf, capital);

	String res(buf, inLen * 2);
    delete [] buf;
    return res;
}

/**
* 对数据进行解码
* @param in: 要解码的数据
* @param inLen: 要解码的数据的长度（必须为偶数）
* @param out: [out]缓冲区，存放解码后的数据（至少是@inLen的一半大小）
* @return: 如果@inLen不为偶数或者输入数据中非法字符，则解码失败，返回false；
*          否则解码成功，返回true
*/
bool Base16::decode(const char *in, size_t inLen, void *out)
{
    assert(inLen % 2 == 0);
    if (inLen % 2 != 0)
        return false;

    unsigned char *dest = reinterpret_cast<unsigned char *>(out);

    for (size_t i = 0; i < inLen; i += 2) {
        // 高四位
        char ch = decode16(in[i]);
        if (ch == BAD)
            return false;  // 非法字符
        dest[i / 2] = ch << 4;

        // 低四位
        ch = decode16(in[i + 1]);
        if (ch == BAD)
            return false;  // 非法字符
        dest[i / 2] |= ch;
    }

    return true;
}

