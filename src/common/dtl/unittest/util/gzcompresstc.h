/***************************************************************************************************
gzcompresstc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Compress 测试

Author: 
	Yang.bing

Creating Time:
	2012-9-17
 ****************************************************************/
#ifndef __GZCOMPRESS_TC_H__
#define __GZCOMPRESS_TC_H__

#include <cppunit/tester.h>

class CompressTestCase : public  CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE (CompressTestCase);

		CPPUNIT_TEST_DESCRIPTION(testCompressFile,	 _T("测试CompressFile, 压缩文件是否正确"));
		CPPUNIT_TEST_DESCRIPTION(testCompressBuffer, _T("测试CompressBuffer, 压缩数据是否正确"));
		CPPUNIT_TEST_DESCRIPTION(testCompressBuffer2, _T("测试CompressBuffer2, 压缩数据是否正确"));

	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testCompressFile(void);
	void testCompressBuffer(void);
	void testCompressBuffer2(void);
	
private:

};

#endif //end  __GZCOMPRESS_TC_H__
