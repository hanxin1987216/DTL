/***************************************************************************************************
compress.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
	This file contain the declaration of classes Compression

Author:
	hanxin (han.xin@datatom.com)
	
Creating Time:
	2013-2-2
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "../mono_base/uglify.h"
#include "../io/comdef.h"
#include "../io/file.h"
#include "../io/path.h"
#include "../io/fileinputstream.h"
#include "../io/fileoutputstream.h"

#include "compress.h"
using namespace std;

size_t 
SnappyCompress::Compress(const char* input, size_t len, string *output)
{
	return snappy::Compress(input, len , output);
}

bool
SnappyCompress:: UnCompress(const char* compressed, size_t compressed_length,string* uncompressed)
{
	if (snappy::IsValidCompressedBuffer(compressed, compressed_length) == false)
		THROW ("illegal compressed buffer, cannot uncompress");
	
	return snappy::Uncompress(compressed, compressed_length, uncompressed);
}

void 
SnappyCompress::RawCompress(const char* input,
					   size_t input_length,
					   char* compressed,
					   size_t* compressed_length)
{
	snappy::RawCompress(input, input_length, compressed, compressed_length);
}


bool 
SnappyCompress::RawUnCompress(const char* compressed, size_t compressed_length,
							char* uncompressed)
{
	if (snappy::IsValidCompressedBuffer(compressed, compressed_length) == false)
		THROW ("illegal compressed buffer, cannot uncompress");

	return snappy::RawUncompress(compressed, compressed_length, uncompressed);
}

/**
* 返回最大的压缩大小
* @param  压缩源数据块的大小
*/
size_t 
SnappyCompress::MaxCompressedLength(size_t source_bytes)
{
	return snappy::MaxCompressedLength(source_bytes);
}

/**
* @param compressed  		 compressed buffer produced by RawCompress() or Compress()
* @param compressed_length   compressed buffer length
* @return  Returns true and stores the length of the uncompressed data 
			inresult normally.  Returns false on parsing error.
*/
size_t 
SnappyCompress::GetUnCompressedLength(const char* compressed, size_t compressed_length)
{
	size_t result = 0;
	if (snappy::GetUncompressedLength(compressed, compressed_length, &result) == false)
		result = 0;
	
	return result;
}

							
