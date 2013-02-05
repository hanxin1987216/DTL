/***************************************************************************************************
base16.h
 	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	base16 编、解码
	
Auther:
	韩欣 (han.xin@datatom.com)

Created Time:
	2011-11-4
***************************************************************************************************/

#ifndef __BASE16__H__
#define __BASE16__H__

#include "../prec.h"
#include "../lang/string.h"

/**
* 类Base16是一个用于Base16（十六进制）编码/解码的工具类。
* 所有成员均为静态成员。
*/

class DTL_DLLEXPORT Base16
{
public:
    /**
    * 对数据进行编码
    * @param in: 要编码的数据
    * @param inLen: 要编码的数据长度（字节数）
    * @param out: [out]缓冲区，存放编码后的数据（至少是2倍inLen大）
    * @param capital: 编码中的字母是否大小；取值true表示大写（默认），false表示小写
    * @return: 如果in或者out为空指针，则编码失败并返回false；否则成功，返回true。
    */
    static bool encode(const void *in, size_t inLen, char *out, bool capital = true);

    /**
    * 对数据进行编码
    * @param in: 要编码的数据
    * @param inLen: 要编码的数据长度（字节数）
    * @param capital: 编码中的字母是否大小；取值true表示大写（默认），false表示小写
    * @return: 如果in为空指针，则编码失败并返回空串；否则成功，返回编码后的字符串数据。
    */
    static String encode(const void *in, size_t inLen, bool capital = true);

    /**
    * 对数据进行解码
    * @param in: 要解码的数据
    * @param inLen: 要解码的数据的长度（必须为偶数）
    * @param out: [out]缓冲区，存放解码后的数据（至少是@inLen的一半大小）
    * @return: 如果inLen不为偶数或者输入数据中非法字符，则解码失败，返回false；
    *          否则解码成功，返回true
    */
    static bool decode(const char *in, size_t inLen, void *out);

private:
    enum {BAD = -1};
    static const char sm_lowercase[17];
    static const char sm_capital[17];
    static const char sm_base16val[128];

    static char decode16(unsigned char ch) {
        return ch < 128 ? sm_base16val[ch] : BAD;
    }
};


#endif // __BASE64__H__
