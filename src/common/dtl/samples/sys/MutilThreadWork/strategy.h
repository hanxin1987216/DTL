
/***************************************************************************************************
stategy.h:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
     	具体线程策略

Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/

#include "mutilThread.h"

#ifndef _STARTEGY_H___
#define _STARTEGY_H__


class TreadStartegy
{
public:

	TreadStartegy(MutilThread *mutilThread);
	~TreadStartegy();

public:
	void threadRun();

private:
	MutilThread* ptrMutilThread;
};// end startegy

#endif //End _STARTEGY_H__

