/***************************************************************************************************
lock.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: lock

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2011-10-10
***************************************************************************************************/

#include <defs.h>
#include "../prec.h"

#include "../mono_base/critical-sections.h"
#include <assert.h>


#ifndef __WINDOWS__
	#include   <unistd.h>
	#include   <sys/stat.h>
	#include   <fcntl.h>
#endif


static pthread_mutexattr_t attr;


#include "lock.h"



// public virtual
BaseLock::~BaseLock (void)
{
	// Do nothing
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// ThreadMutexLock
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef __WINDOWS__
static void
initCriticalSection (CRITICAL_SECTION* cs)
{
	__try{
		::InitializeCriticalSection (cs);
	}
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		//DTLASSERT (false);
		// FIXME: How should we do?
	}
}
#endif



// public ctor
ThreadMutexLock::ThreadMutexLock (void)
{
#ifdef __WINDOWS__
	initCriticalSection (&_cs);
#else
	::InitializeCriticalSection (&_cs);
#endif
}

// public dtor
ThreadMutexLock::~ThreadMutexLock (void)
{
	::DeleteCriticalSection (&_cs);
}
	
// public virtual
void
ThreadMutexLock::lock (void)
{
#ifdef __WINDOWS__
	__try {
#endif
		::EnterCriticalSection (&_cs); 
#ifdef __WINDOWS__
	}
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		//DTLASSERT (false);
		// FIXME: How should we do?
	}
#endif
}

// public virtual
void
ThreadMutexLock::unlock (void) 
{	
	::LeaveCriticalSection (&_cs);
}

// public virtual
bool
ThreadMutexLock::tryLock (void) 
{
#ifdef __WINDOWS__
	__try {
#endif
		return (::TryEnterCriticalSection (&_cs) == TRUE); 

#ifdef __WINDOWS__
	}
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		//DTLASSERT (false);
		// FIXME: How should we do?
	}
	
	return false;
#endif
}