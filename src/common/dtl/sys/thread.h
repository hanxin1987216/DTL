/***************************************************************************************************
thread.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Co., Ltd.(2011 - 2012), All rights reserved.

Purpose:
	线程库
	
Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2012-3-28
***************************************************************************************************/

#ifndef __DTL_SYS_THREAD_H__
#define __DTL_SYS_THREAD_H__

#if PRAGMA_ONCE
#	pragma once
#endif


#ifdef __WINDOWS__
typedef void* ThreadPointer;
#else
typedef gpointer ThreadPointer;
#endif
/**
 * The priority to schedule of a thread.
 */
enum ThreadPriority
{
	/**
	 * The minimum priority that a thread can have. 
	 */
	LOW_PRIORITY = 1,

   /**
	* The default priority that is assigned to a thread. 
	*/
	NORMAL_PRIORITY,

	/**
	 * The maximum priority that a thread can have. 
	 */
	HIGH_PRIORITY,
	
}; // End enum ThreadPriority

/**
 * Represents the execution state of a thread.
 */
enum ThreadState
{
	/**
	 * The method Thread.start() has not been called on the thread.
	 */
	NOT_STARTED_STATE = 1,
	
	/**
	 * The thread has been started and it is running without blocking.
	 */
	RUNNING_STATE,
	
	/**
	 * The thread is on when the method Thread.pause() be called on success.
	 */
	PAUSED_STATE,
	
	/**
	 * The thread is on when the method Thread.run() has returned, 
	 *	or the method Thread.stop() be called on succcess, 
	 *	or the thread object has been destroyed.
	 */
	STOPPED_STATE,
	
}; // End enum ThreadState

/*
 * #Thread defined to represents a thread. This class provide routines to
 * control execution, adjust priority and get the state of the thread.
 */
 
class DTL_DLLEXPORT Thread
{
	DTL_DECLARE_NO_COPY_CLASS (Thread)

// Contructor and Destructor
public:
	/**
	 * Constructs a new thread instance with default setting.
	 *
	 * @throw Exception If cannot create the thread.
	 */
	Thread (void);

	/**
	 * Constructs a new thread instance with thread name specified.
	 *
	 * @param name	The thread name.
	 * @throw Exception If the name is empty.
	 * @throw Exception If cannot create the thread.
	 */
	explicit Thread (const String& name);
	
	/**
	 * Stops the thread if it is running, destruct the thread instance.
	 */
	virtual ~Thread (void);

	/**
	 * Subclass override this method to execute thread code.
	 */
	virtual void run (void) = 0;

// Static members
public:
	/**
	 * Blocks the current thread for the specified number of milliseconds. 
	 * 
	 * @param millisec 	The number to block, in millisecond. Specify 
	 *					cpp::lang::Int::INFINITE_VALUE to block the thread indefinitely. 
	 */
	static void sleep (int millisec);
	
	/**
	 * Causes the current thread of execution to temporarily pause 
	 * and allow other threads to execute. 
	 */
	static void yield (void);

	/**
	 * Returns the current thread identifier.		 
	 */
	static int getCurThreadId (void);
	
// public methods
public:
	/**
	 * Starts a thread, this method call run() method to execute code of
	 *	this thread.
	 *
	 * @throw Exception If the thread has been started.
	 * @throw Exception If cannot start the thread.
	 */
	void start (void);

	/**
	 * Gets the thread's name, which is the identifier of the thread.
	 * @return the thread's name.
	 */
	String getName (void) const
	{
		return _name;
	}
	
	/**
	 * Sets the thread's name.
	 * @param name 	The name for the thread.
	 */
	void setName (const String& name)
	{
		_name = name;
	}

	/**
	 * Gets the thread's priority.
	 * @return The thread's priority.
	 */
	ThreadPriority getPriority (void) const
	{
		return _priority;
	}
	
	/**
	 * Sets new priority for this thread.
	 * 
	 * @param priority 	The new priority to set.
	 * @throw Exception If the thread has been stopped.
	 * @throw Exception If cannot to set new priority for this thread.
	 */
	void setPriority (ThreadPriority priority);

	/** 
	 * Get the thread's execution state.
	 * @return The execution state of this thread.
	 */
	ThreadState getThreadState (void) const;
	
	/**
	 * Tests if this thread is alive. A thread is alive if it has 
	 * been started and has not yet died. 
	 *
	 * @return  true if this thread is alive, otherwise false.
	 */
	bool isAlive (void) const;
	
	/**
	 * Forces the thread ends if the thread is running.
	 *
	 * @throw Exception If the thread state is not running.
	 * @throw Exception If cannot stop the thread.
	 */
	void stop (void);	
	
	/**
	 * Suspends this thread. 
	 * If the thread is alive, it is suspended and makes no further progress unless 
	 *	and until it is resumed. 
	 *
	 * @throw Exception If the thread state is not running.
	 * @throw Exception If cannot pause the thread.
	 */
	void pause (void); 

	/**
	 * Resumes a suspended thread. 
	 * If the thread is alive but suspended, it is resumed and is permitted to 
	 *	make progress in its execution.  
	 *
	 * @throw Exception If the thread state is not paused.
	 * @throw Exception If cannot resume the thread.
	 */
	void resume (void);

	/**
	 * Blocks the calling thread until this thread terminates.
	 * If the thread has been stopped, this method return immediately.
	 *
	 * @throw Exception If the thread state is not running.
	 * @throw Exception If cannot wait this thread.
	 */
	void join (void)
	{
		join (Int::INFINITE_VALUE);
	}
	
	/**
	 * Blocks the calling thread util the time out or theis thread terminates.
	 * If the thread has been stopped, this method return immediately.
	 *
	 * @param millisecTimeout	The timeout to wait, in milliseconds.
	 *
	 * @throw Exception If the timeout is less than zero and not be Int::INFINITE_VALUE.
	 * @throw Exception If the thread state is not running.
	 * @throw Exception If cannot wait this thread.
	 */
	void join (int millisecTimeout);
	
	ThreadPointer getHandle (void) const
	{
		return _handle;
	}

protected:
	friend unsigned DTL_STDCALL threadBeginEntry (void* param);
	
	String _name;
	ThreadPriority _priority;
	ThreadState	_state;		
			
	ThreadPointer _handle;

	static int _threadTotalCount;
}; // End class Thread
#endif // __DTL_SYS_THREAD_H__
