/***************************************************************************************************
gzcompresstc.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Compress 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-17
 ****************************************************************/

#include "gzcompresstc.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CompressTestCase);

#define TEST_FILE_SRC 				"/etc/profile"
#define TEST_FILE_COMPRESS			"/root/Desktop/profile_bak"
#define TEST_FILE_UNCOMPRESS 		"/root/Desktop/profile_bak_uncompress"
#define INPUT_BUF_MAX 				512
#define FILE_PATH					"/tmp/toolstcTestFile"

void
CompressTestCase::setUp(void) 
{
	InitDTLibrary ();
}

void
CompressTestCase::tearDown(void) 
{
	File file1(TEST_FILE_COMPRESS);
	File file2(TEST_FILE_UNCOMPRESS);
	File file(TEST_FILE_UNCOMPRESS);
	file1.remove();
	file2.remove();
}

void
CompressTestCase::testCompressFile(void)
{
	//测试压缩和解压后文件长度是否一致
 	Compress compre;
 	compre.CompressFile(TEST_FILE_SRC, TEST_FILE_COMPRESS);
	compre.DeCompressFile(TEST_FILE_COMPRESS, TEST_FILE_UNCOMPRESS);
 	File file_src(TEST_FILE_SRC);
	File file_uncompress(TEST_FILE_UNCOMPRESS);

	CPPUNIT_ASSERT (file_src.getLength() == file_uncompress.getLength()); 
}

void 
CompressTestCase::testCompressBuffer(void)
{
	//通过读取文件TEST_FILE_SRC，进行压缩后在进行解压来验证其函数的正确性。
 	Compress compre;
	FileInputStream in(TEST_FILE_SRC);
	
	Byte buf_uncompress[INPUT_BUF_MAX];
	Byte buf_compress[INPUT_BUF_MAX];
	Byte buf_decompress[INPUT_BUF_MAX];
	
	memset(buf_uncompress, 0, INPUT_BUF_MAX);
	memset(buf_compress, 0, INPUT_BUF_MAX);
	memset(buf_decompress, 0, INPUT_BUF_MAX);
	
	ulong comprLen = sizeof(buf_compress)/sizeof(buf_compress[0]);
	ulong decompreLen = sizeof(buf_decompress)/sizeof(buf_decompress[0]);	
	
	ulong uncomprLen = in.read(buf_uncompress, INPUT_BUF_MAX);
	compre.CompressBuffer(buf_compress, comprLen, buf_uncompress, uncomprLen);
	compre.DeCompressBuffer(buf_decompress, decompreLen, buf_compress, comprLen);
	
	CPPUNIT_ASSERT (comprLen == decompreLen); 
}	

void
CompressTestCase::testCompressBuffer2(void)
{
 	Compress compre;
	FileInputStream in(TEST_FILE_SRC);
	
	Byte buf_uncompress[INPUT_BUF_MAX];
	Byte buf_compress[INPUT_BUF_MAX];
	Byte buf_decompress[INPUT_BUF_MAX];

	memset(buf_uncompress, 0, INPUT_BUF_MAX);
	memset(buf_compress, 0, INPUT_BUF_MAX);
	memset(buf_decompress, 0, INPUT_BUF_MAX);
	
	ulong comprLen = sizeof(buf_compress)/sizeof(buf_compress[0]);
	ulong decompreLen = sizeof(buf_decompress)/sizeof(buf_decompress[0]);	
	ulong uncomprLen = in.read(buf_uncompress, INPUT_BUF_MAX);
	
	//压缩级别Z_NO_COMPRESSION
	compre.CompressBuffer2(buf_compress, comprLen, buf_uncompress, uncomprLen, 0);	
	compre.DeCompressBuffer(buf_decompress, decompreLen, buf_compress, comprLen);
	CPPUNIT_ASSERT (comprLen == decompreLen);
	
	//压缩级别Z_BEST_SPEED
	compre.CompressBuffer2(buf_compress, comprLen, buf_uncompress, uncomprLen, 1);	
	compre.DeCompressBuffer(buf_decompress, decompreLen, buf_compress, comprLen);
	CPPUNIT_ASSERT (comprLen == decompreLen);
	
	//压缩级别Z_DEFAULT_COMPRESSION
	compre.CompressBuffer2(buf_compress, comprLen, buf_uncompress, uncomprLen, -1);	
	compre.DeCompressBuffer(buf_decompress, decompreLen, buf_compress, comprLen);
	CPPUNIT_ASSERT (comprLen == decompreLen);
	
	//压缩级别Z_BEST_COMPRESSION	
	compre.CompressBuffer2(buf_compress, comprLen, buf_uncompress, uncomprLen, 9);	
	compre.DeCompressBuffer(buf_decompress, decompreLen, buf_compress, comprLen);
	CPPUNIT_ASSERT (comprLen == decompreLen);	
}










