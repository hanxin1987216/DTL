/*
 * timefuncs.c:  performance timer and other time functions
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#include <config.h>
#include <glib.h>
#include <sys/time.h>
#include <stdlib.h>

#include "./wapi.h"
#include "./timefuncs-private.h"

#undef DEBUG

void _wapi_time_t_to_filetime (time_t timeval, WapiFileTime *filetime)
{
	guint64 ticks;
	
	ticks = ((guint64)timeval * 10000000) + 116444736000000000ULL;
	filetime->dwLowDateTime = ticks & 0xFFFFFFFF;
	filetime->dwHighDateTime = ticks >> 32;
}

void _wapi_timeval_to_filetime (struct timeval *tv, WapiFileTime *filetime)
{
	guint64 ticks;
	
	ticks = ((guint64)tv->tv_sec * 10000000) +
		((guint64)tv->tv_usec * 10) + 116444736000000000ULL;
	filetime->dwLowDateTime = ticks & 0xFFFFFFFF;
	filetime->dwHighDateTime = ticks >> 32;
}

gboolean QueryPerformanceCounter(WapiLargeInteger *count G_GNUC_UNUSED)
{
	return(FALSE);
}

gboolean QueryPerformanceFrequency(WapiLargeInteger *freq G_GNUC_UNUSED)
{
	return(FALSE);
}

guint32 GetTickCount (void)
{
	struct timeval tv;
	guint32 ret;
	
	ret=gettimeofday (&tv, NULL);
	if(ret==-1) {
		return(0);
	}
	
	/* This is supposed to return milliseconds since reboot but I
	 * really can't be bothered to work out the uptime, especially
	 * as the 32bit value wraps around every 47 days
	 */
	ret=(guint32)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

#ifdef DEBUG
	g_message ("%s: returning %d", __func__, ret);
#endif

	return(ret);
}
