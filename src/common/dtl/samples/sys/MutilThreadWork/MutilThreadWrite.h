/***************************************************************************************************
MutilThreadWrite.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	写文件线程方法
Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/

#ifndef _MutilThreadWrite_H__
#define _MutilThreadWrite_H__

#include "mutilThread.h"

/**
*     写文件线程方法
*/

class MutilThreadWrite : public MutilThread
{
public:
	MutilThreadWrite(String threadName, const String &pathName, String Content);
	~MutilThreadWrite(void);
	
	//MutilThreadWrite(int threadNum, int count);
public:
	void run();
	void threadWork();

protected:
	void writeFile();

private:
	String _pathname;                     	
	String _content;
	
};// MutilThreadWrite


#endif //End _MutilThreadWrite_H___     