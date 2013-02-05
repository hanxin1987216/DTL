/***************************************************************************************************
gzcompress.h
 	Copyright (c) Datatom Co., Ltd.(2012 - 2015), All rights reserved.

Purpose:
	this is a class of Data compression  
	
Auther:
	zhang.wencong@datatom.com

Created Time:
	2012-07-31
***************************************************************************************************/
#ifndef __DTL_GZCOMPRESS_HEAD_H__
#define __DTL_GZCOMPRESS_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#include <zconf.h>
#include <zlib.h>

//数据长度
#define COMPRESS_BUFF_SIZE (1024*1024*1)

class DTL_DLLEXPORT Compress
{

public:

	/**
	 * 对指定的文件sourcePathName进行压缩,输出压缩文件destPathName
	 *
	 * @param	sourcePathName 压缩的文件名.
	 * @param	destPathName 压缩后的文件名.
	 *
	 * @throw 	压缩异常，抛出压缩失败提示
	**/
	void CompressFile(const String& sourcePathName, const String& destPathName);
	
	/**
	 * 对传入的数据unComprBuffer, 长度为uncomprLen进行压缩后,
	 *输出的压缩数据ComprBuffer和压缩的数据的长度comprLen
	 *特别注意：comprLen的长度要比uncomprLen大0.1%加上12个字节, 否则可能会出现异常
	 *抛出异常Z_BUF_ERROR -5就是空间不足
	 *
	 * @param	unComprBuffer 传入参数, 压缩前的数据.
	 * @param	uncomprLen 传入参数, 压缩前的数据长度.
	 * @param	ComprBuffer 传出参数, unComprBuffer数据被压缩后的数据.
	 * @param	comprLen    传入和传出参数, 压缩前的数据长度，注意传入的数值应为(comprLen=(1+0.1%)*uncomprLen+12).
	 * comprLen最好比uncomprLen大0.2%.
	 *
	 * @throw 	压缩异常，抛出压缩失败提示(Z_DATA_ERROR(-3) 数据错误
		Z_MEM_ERROR (-4) 内存错误 Z_BUF_ERROR (-5) 空间不足)
	**/
	void CompressBuffer(Byte *ComprBuffer, uLong& comprLen, 
								const Byte *unComprBuffer,uLong& uncomprLen);
	
	/**自定义压缩等级:
	 * 对传入的数据unComprBuffer, 长度为uncomprLen进行压缩后,
	 *输出的压缩数据ComprBuffer和压缩的数据的长度comprLen, level为压缩的等级, 可以自定压缩级别
	 *特别注意：comprLen的长度要比uncomprLen大0.1%加上12个字节, 
	 *抛出异常Z_BUF_ERROR-5 就是空间不足
	 *
	 * @param	unComprBuffer 传入参数, 压缩前的数据.
	 * @param	uncomprLen 传入参数, 压缩前的数据长度.
	 * @param	ComprBuffer 传出参数, unComprBuffer数据被压缩后的数据
	 * @param	comprLen    传入和传出参数, 压缩前的数据长度，注意传入的数值应为(comprLen=(1+0.1%)*uncomprLen+12).
	 * comprLen最好比uncomprLen大0.2%
	 *
	 * @param	level    压缩的级别
	 *					 0 Z_NO_COMPRESSION, 
	 *					 1 Z_BEST_SPEED, 
	 *                   9 Z_BEST_COMPRESSION, 
	 *					-1 Z_DEFAULT_COMPRESSION).
	 *
	 * @throw 	压缩异常，抛出压缩失败提示(Z_DATA_ERROR(-3) 数据错误
	 * Z_MEM_ERROR (-4) 内存错误 Z_BUF_ERROR (-5) 空间不足)
	**/
	void CompressBuffer2( Byte *ComprBuffer,uLong& comprLen,
						const Byte *unComprBuffer, uLong& uncomprLen, int level=Z_DEFAULT_COMPRESSION);	
						
	/**
	* 对文件进行解压, 输出解压后的文件
	*
	* @param	sourecePathName 压缩文件的文件名.
	* @param	destPathName    解压后的文件名
	*
	* @throw 	压缩异常，压缩异常，抛出压缩失败提示(Z_DATA_ERROR(-3) 数据错误
	* Z_MEM_ERROR (-4) 内存错误 Z_BUF_ERROR (-5) 空间不足)
	**/					
	void DeCompressFile(const String& sourcePathName, const String& destPathName);
	
	/**
	 * 对传入的压缩数据compr长度为comprLen进行解压,输出解压后的数据unComprBuffer和长度uncomprLen,
	 *注意:解压后的数据unComprBuffer要够大, 能够容纳compr解压后的数据大小。抛出异常Z_DATA_ERROR
	 *-3 表示数据读取错误, Z_BUF_ERROR为空间不足
	 *
	 * @param	unComprBuffer 传出参数, 解压后的数据.
	 * @param	uncomprLen 传出参数, 解压后的数据长度.
	 * @param	ComprBuffer 传入参数, 压缩数据.
	 * @param	comprLen    传入参数, 压缩数据长度.
	 *
	 * @throw 	解压异常，抛出压缩失败提示(Z_DATA_ERROR(-3) 数据错误
	 * Z_MEM_ERROR (-4) 内存错误 Z_BUF_ERROR (-5) 空间不足)
	**/	
	void DeCompressBuffer(Byte *unComprBuffer,uLong& uncomprLen, Byte *compr, uLong& comprLen);
	
};
	
#endif //__DTL_GZCOMPRESS_HEAD_H__









