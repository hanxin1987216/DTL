/***************************************************************************************************
timediff.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	时间转化

Author:
	韩欣

Creating Time:
	2011-10-10
***************************************************************************************************/

#ifndef __DTL_SYS_TIMEDIFF_H__
#define __DTL_SYS_TIMEDIFF_H__

#if PRAGMA_ONCE
#pragma once
#endif

	
class DTL_DLLEXPORT TimeDiff
{
public:
	explicit TimeDiff (const int64& epoch)
		: _epoch (epoch)
	{
	}

	/**
	 * Get the days of the time span.
	 */
	int getDays (void) const;

protected:
	int64 _epoch; 
};


#endif // __DTL_SYS_TIMEDIFF_H__

