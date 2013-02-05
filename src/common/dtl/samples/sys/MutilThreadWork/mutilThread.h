/***************************************************************************************************
MutilThread.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Test case for Thread class  测试线程类，派生自Thread类

Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/


#ifndef __MUTILTHREAD_H__
#define __MUTILTHREAD_H__


class MutilThread : public Thread
{
public:
	MutilThread(String threadName);
	~MutilThread(void);
	
	
public:
	virtual void run() = 0;
	virtual void threadWork() = 0;
	
};


#endif //End __MUTILTHREAD_H__
