/***************************************************************************************************
stategy.cpp:	
	C++ Foundation Library TestCase header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
     	具体线程策略

Author:
        liu.wenxue@datatom.com	

Creating Time:
	2013-01-30
***************************************************************************************************/

#include <dtl/dtl.h>
#include <dtprec.h>

#include "strategy.h"


TreadStartegy::TreadStartegy(MutilThread *mutilThread):ptrMutilThread(mutilThread)
{ 

}

TreadStartegy::~TreadStartegy()
{ 
	delete ptrMutilThread;
}


void 
TreadStartegy::threadRun()
{
		ptrMutilThread->threadWork();
}

    

