/***************************************************************************************************
gzcompress.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
	This file contain the declaration of classes Compression

Author:
	zhang.wencong@datatom.com

Creating Time:
	2012-7-31
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
#include <zconf.h>
#include <zlib.h>

#include "gzcompress.h"
using namespace std;

/**
 *对文件进行压缩,输出压缩后的文件
**/
void 
Compress::CompressFile(const String& sourcePathName, const String& destPathName)
{
	Bytef *uncompr;	             //未压缩数据
	
	Bytef buncompres[COMPRESS_BUFF_SIZE + 1];
	uncompr = buncompres;
	
	if (!Path::isValidPath(sourcePathName))
	{
		THROW("sourcePathName is null");
	}
	
	int len = 0; //读取数据的长度
	gzFile w_gzfile;
	String error;
	
	//以压缩方式打开文件
	if (NULL == (w_gzfile= gzopen(destPathName.getCStr(), "wb")))
	{
		error.format("Error gzopening file %s:%s", destPathName.getCStr(), strerror(errno));
		THROW(error);
	}
	
	FileInputStream fileinput(sourcePathName);
	
	//从文件中读取长度为GZ_BUFF_SIZE的数据
	len = fileinput.read(uncompr, COMPRESS_BUFF_SIZE);
	try
	{
		while(len > 0)
		{
			//写入压缩文件
			if( gzwrite(w_gzfile, uncompr, len) < 0)
			{
				error.format("%s:gzwrite error", destPathName.getCStr());
				THROW(error);
			}			
			
			memset (uncompr, 0, COMPRESS_BUFF_SIZE);
			//读取数据
			len = fileinput.read(uncompr, COMPRESS_BUFF_SIZE);
		}
	}
	catch(Exception e)
	{
		//关闭读写文件
		fileinput.close();
		gzclose(w_gzfile); 
		THROW(e.getMessage().getCStr());
	}
	
	fileinput.close();	
	gzclose(w_gzfile);
}
	
/**
 *对传入数据进行压缩,输出压缩后的数据和数据的长度
**/
void Compress::CompressBuffer( Byte *ComprBuffer,uLong& comprLen,
						const Byte *unComprBuffer, uLong& uncomprLen)
{
	int ret = -1;
	if (NULL == unComprBuffer)
	{
		THROW("unComprBuffer is null");
	}
	if (NULL == ComprBuffer)
	{
		THROW("ComprBuffer is null");
	}
	//开始压缩数据
	ret = compress(ComprBuffer, &comprLen, unComprBuffer, uncomprLen);
	//异常信息提示
	if (ret != Z_OK)
	{
		String err;
		err.format("CompressBuffer err:%d", ret);
		THROW(err);
	}
}


/**
 *自定义压缩等级:对传入数据进行压缩,输出压缩后的数据和数据长度, level为压缩级别
**/
void Compress::CompressBuffer2( Byte *ComprBuffer,uLong& comprLen,
						const Byte *unComprBuffer, uLong& uncomprLen, int level)
{
	int ret = -1;
	if (NULL == unComprBuffer)
	{
		THROW("unComprBuffer is null");
	}
	if (NULL == ComprBuffer)
	{
		THROW("ComprBuffer is null");
	}
	
	ret = compress2(ComprBuffer, &comprLen, unComprBuffer, uncomprLen, level);
	if (ret != Z_OK)
	{
		String err;
		err.format("CompressBuffer err:%d", ret);
		THROW(err);
	}
}


/**
 * 对传入的文件的进行解压, 输出解压后的文件(对单个文件进行解压)
**/
void Compress::DeCompressFile(const String& sourcePathName, const String& destPathName)
{  
	Byte *compr;                //压缩数据
	
	uLong comprLen   = COMPRESS_BUFF_SIZE; 		//压缩数据长度
	
	Bytef bcompres[COMPRESS_BUFF_SIZE+1];
	compr = bcompres;
	
	if (0 == sourcePathName.getLength())
	{
		THROW("sourcePathName is null");
	}
	if (0 == destPathName.getLength())
	{
		THROW("destPathName is null");
	}
	
	gzFile r_file;    
	int len = 0;
	String error;
	
	if ((r_file=gzopen(sourcePathName.getCStr(), "rb")) == NULL) 
	{
		error.format("Error gzopening file %s:%s", sourcePathName.getCStr(), strerror(errno));
		THROW(error);
	}
	
	FileOutputStream fileout(destPathName.getCStr(), OPEN_OR_CREATE_MODE);
	
	if ((len = gzread(r_file, compr, comprLen)) < 0)
	{
        error.format("gzread err: %s\n", strerror(errno));
        THROW(error.getCStr());
    }
	
	try
	{
		while (len > 0)
		{
			fileout.write(compr, len); //写入文件
			
			memset(compr, 0, COMPRESS_BUFF_SIZE);
			//读取压缩文件
			len = gzread(r_file, compr, comprLen);
		}	
	}
	catch(Exception e)
	{
		gzclose(r_file);  //close  read
		fileout.close();  //close write
		THROW(e.getMessage().getCStr());
	}
	
	gzclose(r_file);  //close  read
	fileout.close();  //close write
}

/**
 * 对传入的数据的进行解压, 输出压缩数据和长度
**/
void Compress::DeCompressBuffer(Byte *unComprBuffer,uLong& uncomprLen, Byte *compr, uLong& comprLen)
{

	int ret = -1 ; //err msg
	if (NULL == compr)
	{
		THROW("compr is null");
	}
	if (NULL == unComprBuffer)
	{
		THROW("unComprBuffer is null");
	}
	
	ret = uncompress(unComprBuffer, &uncomprLen, compr, comprLen);    //compress the stream
	if (Z_OK != ret)
	{
		String err;
		err.format("uncompress err:%d", ret);
		THROW(err);
	}
}
	

	