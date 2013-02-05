/***************************************************************************************************
tc_thread.cpp:	
	C++ Foundation Library TestCase source files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Test case for Thread class

Author:
	Huang.Xianming

Creating Time:
	2012-04-20
***************************************************************************************************/


#include "tc_thread.h"
#include "dtl/dtl.h"


//TestThread
TestThread::TestThread()
	: Thread()
{
	
}

TestThread::TestThread(const String &name)
	: Thread(name)
{
}

void TestThread::run()
{
	while(true)
	{
//		printf("\n\tRunning!\n");
	}
}

TestThread::~TestThread()
{
}



//ThreadTestCase
ThreadTestCase::ThreadTestCase()
{
}

ThreadTestCase::~ThreadTestCase()
{
	if (_thread.isAlive())
	{
		_thread.stop();
	}
}

void ThreadTestCase::testStart()
{
	printf("testStart().\n");
	try
	{
		_thread.start();
		printf("\tOK!\n");
	}
	catch (Exception &e)
	{
		printf("\tFailed:\t%s\n", e.getMessage().getCStr());
	}
	catch (...)
	{
		printf("\tFailed:\tUnknown exception!\n");
	}
}

void ThreadTestCase::testStop()
{
	printf("testStop().\n");
	try
	{
		_thread.stop();
		printf("\tOK!\n");
	}
	catch (Exception &e)
	{
		printf("\tFailed:\t%s\n", e.getMessage().getCStr());
	}
}

void ThreadTestCase::testPause()
{
	printf("testPause().\n");
	try
	{
		_thread.pause();
		printf("\tOK!\n");
	}
	catch (Exception &e)
	{
		printf("\tFailed:\t%s\n", e.getMessage().getCStr());
	}
}

void ThreadTestCase::testJoin()
{
	printf("testJoin().\n");
	try
	{
		_thread.join(500);
		printf("\tOK!\n");
	}
	catch(Exception &e)
	{
		printf("\tFailed:\t%s\n", e.getMessage().getCStr());
	}
	
}

void ThreadTestCase::testResume()
{
	printf("testResume().\n");
	try
	{
		_thread.resume();
		printf("\tOK!\n");
	}
	catch (Exception &e)
	{
		printf("\tFailed:\t%s\n", e.getMessage().getCStr());
	}
}

void ThreadTestCase::testGetName()
{
	printf("testGetName().\n");
	String strName;
	strName = _thread.getName();
	printf("\tThread name:\t%s\n", strName.getCStr());
	printf("\tOK!\n");
}

void ThreadTestCase::testSetName()
{
	char strNewName[MAX_PATH];
	printf("tesetSetName().\n");
	printf("\tPlease enter new thread name.\n");
	gets(strNewName);
	_thread.setName(strNewName);
	printf("\tOK!\n");
}

void ThreadTestCase::testGetPriority()
{
	printf("testGetPriority().\n");
	ThreadPriority priority = _thread.getPriority();
	switch (priority)
	{
	case LOW_PRIORITY:
		printf("\tThread priority:\tlow.\n");
		break;
	case NORMAL_PRIORITY:
		printf("\tThread priority:\tnormal.\n");
		break;
	case HIGH_PRIORITY:
		printf("\tThread priority:\thigh.\n");
		break;
	default:
		printf("\tThread priority:\tunknown.\n");
		break;
	}
	printf("\tOK!\n");
}

void ThreadTestCase::testSetPriority()
{
	printf("testSetPriority().\n");
	printf("\tPlease enter the priority:\n");
	printf("\t1----low\n");
	printf("\t2----normal\n");
	printf("\t3----high\n");

	char t[2] = "\0";
	memset(t, '\0', 2);
	gets(t);
	if ((t[0] != '1') && (t[0] != '2') && (t[0] != '3'))
	{
		printf ("\tFailed:\tunexpected priority\n");
		return;
	}
	ThreadPriority priority = (ThreadPriority)(atoi(t));
	_thread.setPriority(priority);
	printf("\tOK!\n");
}

void ThreadTestCase::testGetState()
{
	printf("testGetState().\n");
	ThreadState state = _thread.getThreadState();
	switch (state)
	{
	case NOT_STARTED_STATE:
		printf("\tThread state:\tnot started.\n");
		break;
	case RUNNING_STATE:
		printf("\tThread state:\trunning.\n");
		break;
	case PAUSED_STATE:
		printf("\tThread state:\tpaused.\n");
		break;
	case STOPPED_STATE:
		printf("\tThread state:\tstopped.\n");
		break;
	default:
		printf("\tThread state:\tunknown.\n");
		break;
	}
	printf("\tOK!\n");
}

void ThreadTestCase::testIsAlive()
{
	printf("testIsAlive().\n");
	if (_thread.isAlive())
	{
		printf("\tThread is alive.\n");
	}
	else
	{	
		printf("\tThread is not alive.\n");
	}
	printf("\tOK!\n");
}

void ThreadTestCase::testSleep()
{
	printf("testSleep().\n");
	_thread.sleep(5000);
	printf("\tOK!\n");
}


void ThreadTestCase::testYield()
{
	printf("testYield().\n");
	Thread::yield();
	printf("\tOK!\n");
}

void ThreadTestCase::testGetCurThreadId()
{
	printf("testGetCurThreadId().\n");
	int threadId = Thread::getCurThreadId();
	printf("\tCurrent thread ID:\t%d\n", threadId);
	printf("\tOK!\n");
}
