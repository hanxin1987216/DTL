/***************************************************************************************************
int.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	文件锁

Author:
	韩欣 （han.xin@datatom.com）

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_LOCKFILE_H__
#define __DTL_LOCKFILE_H__

#if PRAGMA_ONCE
#	pragma once
#endif

/**
 * 文件锁
 */
class DTL_DLLEXPORT Lockfile
{
public:

	/**
	 * Create a new lock object that can be used to make locks.
	 */
	Lockfile (void);
	Lockfile (const char *name);


	/**
	 * Destroy the current lock and release it.
	 */
	~Lockfile (void)
	{
		unlock();
	}

public:

	/**
	 * Lock a system-wide name for this process.  If the lock
	 * is successful, return true.  If an existing lock was
	 * already acquired, release it first.
	 *
	 * @return true if lock successful.
	 * @param name system-wide lock to use.
	 */
	bool lock (const char *name);
	void unlock (void);


	/**
	 * Flag if the current process has aqcuired a lock.
	 *
	 * @return true if we have the lock.
	 */
	bool isLocked (void);

private:

#ifdef __WINDOWS__

	HANDLE		_mutex;
	bool		_flagged;
#else	
	char		*_path;	 // 锁文件路径

#endif


	
}; // End class Int


#endif // __DTL_LOCKFILE_H__
