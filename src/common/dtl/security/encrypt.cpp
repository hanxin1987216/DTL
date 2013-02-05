/***************************************************************************************************
encrypt.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	encrypt impl file
	
Author:
	º«ÐÀ (han.xin@datatom.com)
	
Creating Time:
	2011-11-28
***************************************************************************************************/

#include "../prec.h"

#include "../sys/exception.h"
#include "encrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////////////////
// class #RijndaelEncryption

// public ctor
RijndaelEncryption::RijndaelEncryption (const unsigned char* key, 
										OpDirection direction, 
										const unsigned char* iv /* = 0 */)
	: _aes ()
{
	if (key == 0)
		THROW ("key is null");
		
	Rijndael::Direction d = direction == OD_ENCRYPT ? Rijndael::Encrypt : Rijndael::Decrypt;
	int ret = _aes.init (Rijndael::CBC, 
						 d, key, 
						 Rijndael::Key32Bytes, 
						 const_cast<unsigned char*> (iv));
						 
	if (ret != RIJNDAEL_SUCCESS)
		THROW ("aes init failed");
}

// public dtor
RijndaelEncryption::~RijndaelEncryption (void)
{
}

// public virtual
void
RijndaelEncryption::decode (const unsigned char* input, size_t length, vector<unsigned char>& out)
{
	//AESCheckBufferLen (length);

	unsigned char* buf;// = new unsigned char[length];
	//ANY_NEW_ARRAY_THROW (buf, unsigned char, length);

	int ret = _aes.padDecrypt (input, (int) length, buf);

	if (ret < 0) {
		delete [] buf;
		THROW ("ret smaller than 0 ,");
	}
	else {
		out.assign (buf, buf + ret);
		delete [] buf;
	}
}

// public 
void
RijndaelEncryption::encode (const unsigned char* input, size_t length, vector<unsigned char>& out)
{
	//AESCheckBufferLen (length);

	unsigned char* buf;// = new unsigned char[length + 16];
	//ANY_NEW_ARRAY_THROW (buf, unsigned char, (length + 16));

	int ret = _aes.padEncrypt (input, (int) length, buf);

	if (ret < 0) {
		delete [] buf;
		THROW ("padEncrypt failed");
	}
	else {
		out.assign (buf, buf + ret);
		delete [] buf;
	}
}

// public virtual
size_t 
RijndaelEncryption::encode (const unsigned char* input, size_t length, unsigned char* output)
{
	//AESCheckBufferLen (length);

	int ret = _aes.padEncrypt (input, (int) length, output);

	if (ret < 0) {
		THROW ("encode error");
	}
	
	return ret;
}

// public virtual
size_t 
RijndaelEncryption::decode (const unsigned char* input, size_t length, unsigned char* output)
{
	//AESCheckBufferLen (length);

	int ret = _aes.padDecrypt (input, (int) length, output);

	if (ret < 0) {
		THROW ("decode failed");
	}

	return ret;
}

// public
void 
RijndaelEncryption::blockEncode (const unsigned char* input, size_t length, unsigned char* output)
{
	//AESCheckBufferLen (length);

	int ret = _aes.blockEncrypt (input, (int) length * 8/* bits */, output);

	if (ret < 0) {
		THROW ("blockEncode failed");
	}
}

// public
void 
RijndaelEncryption::blockDecode (const unsigned char* input, size_t length, unsigned char* output)
{
	//AESCheckBufferLen (length);

	int ret = _aes.blockDecrypt (input, (int) length * 8/* bits */, output);

	if (ret < 0) {
		THROW ("blockDecrypt faield");
	}
}
