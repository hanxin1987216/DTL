/***************************************************************************************************
encrypt.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	encrypt head file
	
Author:
	 º«ÐÀ(han.xin@datatom.com)
	
Creating Time:
	2011-11-28
  	
***************************************************************************************************/

#ifndef _SECURITY_ENCRYPT_H__
#define _SECURITY_ENCRYPT_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include "rijndael.h"


/**
 * direction of encryption or decryption.
 */
enum DTL_DLLEXPORT OpDirection
{
	// encryption
	OD_ENCRYPT,

	// decryption
	OD_DECRYPT
};


class DTL_DLLEXPORT RijndaelEncryption
{
// Ctors and Dtor
public:
	/**
	 * Constrct AES encryption or decryption object with specified key.
	 *
	 * @param key		key to encrypt or decrypt, the length must be 32 bytes.
	 * @throw ArgumentException if key is null.
	 */	
	
	RijndaelEncryption (const unsigned char* key, 
						OpDirection direction, 
						const unsigned char* iv = 0);

	~RijndaelEncryption (void);

// Public methods
public:
	size_t encode (const unsigned char* input, size_t length, unsigned char* output);

	// @output must be at least (@length + 16) bytes long
	size_t decode (const unsigned char* input, size_t length, unsigned char* output);

	void encode (const unsigned char* input, size_t length, vector<unsigned char>& out);

	void decode (const unsigned char* input, size_t length, vector<unsigned char>& out);

	// Not be padding
	void blockEncode (const unsigned char* input, size_t length, unsigned char* output);
	void blockDecode (const unsigned char* input, size_t length, unsigned char* output);

protected:
	Rijndael _aes;
};// END RijndaelEncryption
	

#endif // _SECURITY_ENCRYPT_H__


