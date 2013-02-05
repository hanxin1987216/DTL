/***************************************************************************************************
MutilThreadRead.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	读文件线程方法

Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/

#ifndef _MutilThreadRead_H__
#define _MutilThreadRead_H__

#include "mutilThread.h"

/**
*     读文件线程方法
*/

class MutilThreadRead : public MutilThread
{
public:
	MutilThreadRead(String threadName, const String &pathName, String &Content);
	~MutilThreadRead(void);
	
	//MutilThreadRead(int threadNum, int count);
public:
                  
	void run();
	void threadWork();
	
protected:
    void readFile();	
	
private:
	String _pathname;
	String &_content;
	
}; // end MutilThreadRead


#endif 

    