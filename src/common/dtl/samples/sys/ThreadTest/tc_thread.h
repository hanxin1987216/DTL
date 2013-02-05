/***************************************************************************************************
tc_thread.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Test case for Thread class

Author:
	Huang.Xianming

Creating Time:
	2012-04-25
***************************************************************************************************/


#ifndef __THREAD_TEST_CASE_HEADER__
#define __THREAD_TEST_CASE_HEADER__	0xafefd002

#if PRAGMA_ONCE
	#pragma once
#endif


#include <dtl/dtl.h>
#include "dtl/sys/thread.h"

/**
*	测试线程类，派生自Thread类
*/
class TestThread : public Thread
{
public:
	TestThread(void);
	TestThread(const String &name);
	
	virtual ~TestThread(void);

protected:
	virtual void run(void);
	
};


/**
*	线程测试类
*/
class ThreadTestCase
{
public:
	ThreadTestCase(void);
	~ThreadTestCase(void);
public:
	void testStart(void);
	void testStop(void);
	void testPause(void);
	void testJoin(void);
	void testResume(void);

public:
	void testGetName(void);
	void testSetName(void);
	void testGetPriority(void);
	void testSetPriority(void);
	void testGetState(void);

public:
	void testIsAlive(void);

public:
	void testSleep(void);
	void testYield(void);
	void testGetCurThreadId(void);
protected:
	TestThread _thread;
};

#endif
