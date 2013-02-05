/***************************************************************************************************
lock.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	This file contain the declaration of classes: lock

Author:
	韩欣 （han.xin@datatom.com）

Creating Time:
	2012-2-10
***************************************************************************************************/

#ifndef __DTL_LOCK_HEAD_H__
#define __DTL_LOCK_HEAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif

#ifndef __WINDOWS__
	#include <glib.h>
	#include <pthread.h>
#endif


/**
 * Base class to provide synchronized mechanism for sharing resource.
 */
class DTL_DLLEXPORT BaseLock 
{
public:
	virtual ~BaseLock (void);		
	
	/**
	 * Lock the sharing resource for current thread. If the sharing resource 
	 * has been locked, the method blocks the calling thread util the sharing
	 * resource be unlocked.
	 *
	 * @throw LockException if error occurred when to lock.		 
	 */
	virtual void lock (void) = 0;
	
	
	/**
	 * Release the lock of the sharing resource for current thread.
	 * After this method calling, other thread that has locked to wait can get
	 *	a change to enter the sharing resource.
	 *
	 * @throw LockException if error occurred when to unlock.
	 */
	virtual void unlock (void) = 0;
	
	/**
	 * Attempt to lock the sharing resource for current thread. If the sharing
	 * resource has be locked, the method returns false immediately. 
	 * 
	 * @throw LockException if error occurred when try to lock.
	 * @return true if lock on successs, false if the sharing resource has been
	 *	locked by another thread.
	 */
	virtual bool tryLock (void) = 0;
}; // End class BaseLock



/**
 * class #AutoLock lock the sharing resource on construction, unlock until the object is
 * desctroyed.
 */
template<typename lock_t>
struct AutoLock
{
	AutoLock (lock_t* lock) 
		: _lock(lock)
	{
		_lock->lock();
	}

	~AutoLock (void)
	{
		_lock->unlock();
	}

	lock_t* _lock;
};



/**
 * Synchronization class that use thread mutex to lock and unlock, this lock is 
 * only for thread mutex, and it has better performance than MutexLock.
 */
class DTL_DLLEXPORT ThreadMutexLock : public BaseLock
{
	DTL_DECLARE_NO_COPY_CLASS (ThreadMutexLock)
	
public:
	/**
	 * Initializes the mutex that uses to synchronize thread for accessing 
	 *	shared resources. 
	 *
	 * @throw LockException if error occurred when create or initialize the object.
	 */
	ThreadMutexLock (void);
	
	/**
	 * Destroys the mutex and release the system resource.
	 */
	~ThreadMutexLock (void);
		
public:
	/**
	 * Lock the sharing resource for current thread. If the sharing resource 
	 * has been locked, the method blocks the calling thread util the sharing
	 * resource be unlocked. 
	 * NOTE: If the object has name, the lock can be used to synchronize different
	 * processes.
	 *
	 * @throw LockException if error occurred when to lock.
	 */
	virtual void lock (void);
	
	/**
	 * Release the lock of the sharing resource for current thread.
	 * After this method calling, other thread that has locked to wait can get
	 *	a change to enter the sharing resource.
	 * NOTE: If the object has name, the lock can be used to synchronize different
	 * processes.
	 *
	 * @throw LockException if error occurred when to unlock.
	 */
	virtual void unlock (void);
	
	/**
	 * Attempt to lock the sharing resource for current thread. If the sharing
	 * resource has be locked, the method returns false immediately. 
	 * NOTE: If the object has name, the lock can be used to synchronize different
	 * processes.
	 * 
	 * @throw LockException if error occurred when try to lock.
	 * @return true if lock on successs, false if the sharing resource has been
	 *	locked by another thread.
	 */
	virtual bool tryLock (void);
	
private:
#ifdef __WINDOWS__
	CRITICAL_SECTION _cs;
#else
	_WapiCriticalSection _cs;
#endif
}; // End class ThreadMutexLock	


#endif // __DTL_LOCK_HEAD_H__
