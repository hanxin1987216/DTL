/*
 * critical-sections.h:  Critical sections
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_CRITICAL_SECTIONS_H_
#define _WAPI_CRITICAL_SECTIONS_H_

#include <glib.h>
#include <pthread.h>

#include "mono-mutex.h"

G_BEGIN_DECLS

typedef struct _WapiCriticalSection WapiCriticalSection;

struct _WapiCriticalSection
{
	guint32 depth;
	mono_mutex_t mutex;
};

//typedef struct _WapiCriticalSection CRITICAL_SECTION;

extern void InitializeCriticalSection(WapiCriticalSection *section);
extern gboolean InitializeCriticalSectionAndSpinCount(WapiCriticalSection *section, guint32 spincount);
extern void DeleteCriticalSection(WapiCriticalSection *section);
extern guint32 SetCriticalSectionSpinCount(WapiCriticalSection *section, guint32 spincount);
extern gboolean TryEnterCriticalSection(WapiCriticalSection *section);
extern void EnterCriticalSection(WapiCriticalSection *section);
extern void LeaveCriticalSection(WapiCriticalSection *section);

G_END_DECLS

#endif /* _WAPI_CRITICAL_SECTIONS_H_ */
