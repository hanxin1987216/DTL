/*
 * thread-private.h:  Private definitions for thread handles
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_THREAD_PRIVATE_H_
#define _WAPI_THREAD_PRIVATE_H_

#include <config.h>
#include <glib.h>
#include <pthread.h>
#ifdef HAVE_SEMAPHORE_H
#include <semaphore.h>
#endif
#ifdef USE_MACH_SEMA
#include <mach/mach_init.h>
#include <mach/task.h>
#include <mach/semaphore.h>
typedef semaphore_t MonoSemType;
#define MONO_SEM_INIT(addr,value) semaphore_create (current_task (), (addr), SYNC_POLICY_FIFO, (value))
#define MONO_SEM_WAIT(sem) semaphore_wait (*(sem))
#define MONO_SEM_POST(sem) semaphore_signal (*(sem))
#define MONO_SEM_DESTROY(sem) semaphore_destroy (current_task (), *(sem))
#elif defined(__AIX__)
// AIX4.3 doesn't implement sem functions.
/*#include "events.h"
#include "wait.h"
typedef gpointer MonoSemType;
#define MONO_SEM_INIT(addr,value) do { *addr = CreateEvent (NULL, TRUE, FALSE, NULL); } while(FALSE)
#define MONO_SEM_WAIT(sem) WaitForSingleObject ((sem), INFINITE)
#define MONO_SEM_POST(sem) SetEvent ((sem))
#define MONO_SEM_DESTROY(sem) CloseHandle ((sem))*/

typedef int	mono_sem_t;

extern int mono_sem_destroy(mono_sem_t *);
extern int mono_sem_init(mono_sem_t *, int, unsigned int);
extern int mono_sem_post(mono_sem_t *);
extern int mono_sem_wait(mono_sem_t *);

typedef mono_sem_t MonoSemType;
#define MONO_SEM_INIT(addr,value) mono_sem_init ((addr), 0, (value))
#define MONO_SEM_WAIT(sem) mono_sem_wait ((sem))
#define MONO_SEM_POST(sem) mono_sem_post ((sem))
#define MONO_SEM_DESTROY(sem) mono_sem_destroy ((sem))
#else
typedef sem_t MonoSemType;
#define MONO_SEM_INIT(addr,value) sem_init ((addr), 0, (value))
#define MONO_SEM_WAIT(sem) sem_wait ((sem))
#define MONO_SEM_POST(sem) sem_post ((sem))
#define MONO_SEM_DESTROY(sem) sem_destroy ((sem))
#endif

extern struct _WapiHandleOps _wapi_thread_ops;

typedef enum {
	THREAD_STATE_START,
	THREAD_STATE_EXITED
} WapiThreadState;

struct _WapiHandle_thread
{
	WapiThreadState state;
	guint32 exitstatus;
	pid_t owner_pid;
	gboolean joined;
	guint32 create_flags;
	/* Fields below this point are only valid for the owning process */
	pthread_t id;
	GPtrArray *owned_mutexes;
	gpointer handle;
	MonoSemType suspend_sem;
	guint32 (*start_routine)(gpointer arg);
	gpointer start_arg;
	GSList *apc_queue;
};

typedef struct
{
	guint32 (*callback)(gpointer arg);
	gpointer param;
} ApcInfo;

extern gboolean _wapi_thread_apc_pending (gpointer handle);
extern gboolean _wapi_thread_cur_apc_pending (void);
extern gboolean _wapi_thread_dispatch_apc_queue (gpointer handle);
extern void _wapi_thread_own_mutex (gpointer mutex);
extern void _wapi_thread_disown_mutex (gpointer mutex);

#endif /* _WAPI_THREAD_PRIVATE_H_ */
