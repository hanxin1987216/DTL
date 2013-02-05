/****************************************************************************************************
md5.h
 	Copyright (c) Datatom, Inc.(2011), All rights reserved.

Purpose:
	define md5
	
Auther:
	zhangfei (zhang.fei@datatom.com)

Created Time:
	2011-10-8
****************************************************************************************************/

#ifndef __CPP_SECURITY_BMD5_H__
#define __CPP_SECURITY_BMD5_H__


struct MD5Context 
{
   unsigned int buf[4];
   unsigned int bits[2];
   unsigned char in[64];
};

class DTL_DLLEXPORT MD5Hash 
{
// Ctors and dtor
public:
	MD5Hash (void);
	~MD5Hash (void);

// Public methods
public:
	/*
	* Update context to reflect the concatenation of another buffer full
	* of bytes.
	*/
	void update (const unsigned char* input, size_t length);

	/*
	* Final wrapup - pad to 64-byte boundary with the bit pattern 
	* 1 0* (64-bit count of bits processed, MSB-first)
	*/
	void final (unsigned char* output);

	/**
	 * 转换成可读的字符串
	 */
	String toString (unsigned char digest[16], bool uppercase = true);
	
	/**
	 * 计算md5值
	 */
	static String md5(const char* buffer, int len);
	static String md5(const String& str);

protected:
	MD5Context	_md5;
	
}; // End MD5Hash

#endif // __CPP_SECURITY_BMD5_H__
