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

#include "../prec.h"
#include "../lang/string.h"

#include "timediff.h"
#include "date.h"

// public 
int 
TimeDiff::getDays (void) const
{
	return (int) (_epoch / Date::ticksPerDay);
}
