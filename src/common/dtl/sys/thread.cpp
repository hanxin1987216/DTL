/***************************************************************************************************
thread.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	线程库
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2012-3-28
***************************************************************************************************/

#include <dtprec.h>

#include "../prec.h"
#include "../lang/string.h"
#include "../lang/int.h"
#include "../mono_base/uglify.h"
#include "exception.h"

#ifdef __WINDOWS__
#include <process.h>
#endif


#include "thread.h"


#ifdef __WINDOWS__
#define TO_ATOMIC(value) reinterpret_cast<LONG volatile*>(value)
#else
#define TO_ATOMIC(value) reinterpret_cast<gint32 volatile*>(value)
#endif

unsigned DTL_STDCALL
threadBeginEntry (void* param)
{
	Thread* thr = reinterpret_cast<Thread*>(param);
	
	if (thr != 0) {
		try {
			thr->run ();
		}
		catch (Exception& e) {
			// Mark the thread state as stopped.
			::InterlockedExchange (TO_ATOMIC(&(thr->_state)), 
								   STOPPED_STATE);		

			if (e.getErrorId () != Exception::NO_MAPPED_ERROR_ID)
				return e.getErrorId ();
		}
		catch (...) {
			// Mark the thread state as stopped.
			::InterlockedExchange (TO_ATOMIC(&(thr->_state)), 
								   STOPPED_STATE);		

			return 1;
		}
		
		// Mark the thread state as stopped.
		::InterlockedExchange (TO_ATOMIC(&(thr->_state)), 
							   STOPPED_STATE);		
		
		return 0; // Ok
	} 

	return 1; // Failure
}

inline ThreadPointer 
createThread (Thread* thread)
{
#ifdef __WINDOWS__
	unsigned int threadId = 0; // For Win98/ME
	void* handle = (void*)::_beginthreadex (NULL, 
							   		       	  0, 
							   		  		  threadBeginEntry, 
							   		  		  reinterpret_cast<LPVOID> (thread), 
							   		  		  CREATE_SUSPENDED, 
							   		  		  &threadId);
#else
	gsize threadId = 0;
	
	gpointer handle = CreateThread (0, 
										   0, 
										   threadBeginEntry,			     
										   reinterpret_cast<gpointer> (thread), 
										   CREATE_SUSPENDED, 
										    &threadId); 
#endif
	String errMsg;
	errMsg.format (_T("create Thread failed, %s."), SystemErrorHandler::getInstance ()->toString (errno).getCStr ());
				   	
	if (handle == 0) {		
		THROW_ID (errMsg,errno);	
	}
		
	return handle;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// class #Thread - base class for multithread

// protected static 
int Thread::_threadTotalCount = 0;
	
// public ctor
Thread::Thread (void)
	: _name ()
	, _priority (NORMAL_PRIORITY)
	, _state (NOT_STARTED_STATE)
	, _handle (0)
{
	_name.format (_T("Thread %d"), ++Thread::_threadTotalCount);
	
	// create a thread with SUSPENDED state, util user call start() to resume it.
	_handle = createThread (this);
}

// public ctor
Thread::Thread (const String& name)
	: _name (name)
	, _priority (NORMAL_PRIORITY)
	, _state (NOT_STARTED_STATE)
	, _handle (0)
{
	if (name.isEmpty ())
		THROW ("thread name is empty");
								 
	// create a thread with SUSPENDED state, util user call start() to resume it.
	_handle = createThread (this);							 
}

// public virtual dtor
Thread::~Thread (void) 
{
	if (_handle != 0) {		
		unsigned int exitCode;
		
		if (::GetExitCodeThread (_handle, TO_DWORD_PTR(&exitCode))) {
			if (exitCode == STILL_ACTIVE)
				::TerminateThread (_handle, 1); // exit thread abnormally
		}
		
		::CloseHandle (_handle);
	}
}

// public static
void
Thread::sleep (int millisec)
{	
	::SleepEx (millisec, TRUE);
}

// public static
void 
Thread::yield (void)
{
	
#ifdef __WINDOWS__
	// SwitchToThread is not supported on Win9x.     
    if (Environment::getCurrentOSVersion () >= cpp::system::OS_WINNT) {
        ::SwitchToThread ();
    }
    else 
    	::SleepEx (0, TRUE);
#elif defined(__LINUX__)
	pthread_yield ();
#else
	Thread::sleep (0);
#endif
}

// public static 
int 
Thread::getCurThreadId (void)
{
	return ::GetCurrentThreadId ();
}

// public
void
Thread::start (void) 
{
	ThreadState state = getThreadState ();
	if (state != NOT_STARTED_STATE)
		THROW (_T("IDS_THREAD_HAS_STARTED"));
	
	// Mark the thread state as running.
	::InterlockedExchange (TO_ATOMIC(&_state), 
						   RUNNING_STATE);
			
	// The thread was created with SUSPENDING state, just resume it to start.	
	if (::ResumeThread (_handle) < 0) {
		_state = NOT_STARTED_STATE; // OK?
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
	}
}

// public
void
Thread::setPriority (ThreadPriority priority)
{	
	ThreadState state = getThreadState ();		
	if (state == STOPPED_STATE)
		THROW(_T("IDS_THREAD_HAS_STOPPED"));
	
#ifdef __WINDOWS__
	int p = THREAD_PRIORITY_NORMAL;	
	switch (priority)
	{
	case LOW_PRIORITY:
		p = THREAD_PRIORITY_LOWEST;
		break;
		
	case NORMAL_PRIORITY:
		p = THREAD_PRIORITY_NORMAL;
		break;
		
	case HIGH_PRIORITY:
		p = THREAD_PRIORITY_HIGHEST;
		break;
	}
	
	if (::SetThreadPriority (_handle, p) == FALSE)
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
#endif

	_priority = priority;
}

// public
void
Thread::stop (void)
{	
	ThreadState state = getThreadState ();
	if (state == NOT_STARTED_STATE) {
		THROW (_T("IDS_THREAD_NOT_STARTED"));
	}
	else if (state == STOPPED_STATE) {
		THROW(_T("IDS_THREAD_HAS_STOPPED"));
	}

	unsigned int exitCode;
	if (::GetExitCodeThread (_handle, TO_DWORD_PTR(&exitCode)) == FALSE)
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
		
	if (exitCode == STILL_ACTIVE) {
		if (::TerminateThread (_handle, 1) == FALSE) // exit thread abnormally
			THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
	}
	
	// Mark state as stopped
	::InterlockedExchange (TO_ATOMIC(&_state), 
						   STOPPED_STATE);
				
	::CloseHandle (_handle);
	_handle = 0; // Avoid to stop again.	
}

// public
void 
Thread::pause (void)
{	
	ThreadState state = getThreadState ();
	if (state != RUNNING_STATE)
		THROW (_T("IDS_THREAD_PAUSE_ERR"));	
		
	if (::SuspendThread (_handle) < 0)
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
	
	// Mark the thread state as paused
	::InterlockedExchange (TO_ATOMIC(&_state), 
						   PAUSED_STATE);	
}

// public
void 
Thread::resume (void)
{	
	ThreadState state = getThreadState ();
	if (state != PAUSED_STATE)
		THROW (_T("IDS_THREAD_RESUME_ERR"));
		
	if (::ResumeThread (_handle) < 0)
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
		
	// Mark the thread state as running
	::InterlockedExchange (TO_ATOMIC(&_state), 
						   RUNNING_STATE);	
}

// public
void 
Thread::join (int millisecTimeout)
{
	ThreadState state = getThreadState ();
	if (state == STOPPED_STATE)
		return; // Has stopped, so return directly.
	
	if (state != RUNNING_STATE)
		THROW (_T("IDS_THREAD_JOIN_ERR"));
	
	unsigned ret = ::WaitForSingleObject (this->_handle, millisecTimeout);
	if (ret == WAIT_FAILED)
		THROW_ID (strerror (::GetLastError ()), ::GetLastError ());
}

// public
bool 
Thread::isAlive (void) const
{
   	ThreadState curState = getThreadState ();
				
	if ((curState != NOT_STARTED_STATE) && (curState != STOPPED_STATE)) 
		return true;
	else
		return false;		
}

// public 
ThreadState 
Thread::getThreadState (void) const
{
	ThreadState state = NOT_STARTED_STATE;
	::InterlockedExchange (TO_ATOMIC(&state), 
						   _state);	
						   
	return state;
}

