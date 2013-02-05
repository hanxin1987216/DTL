/*
 * shared.h:  Shared memory handle, and daemon launching
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	han.xin (han.xin@Datatom.com)
 *
 * (C) 2002 Ximian, Inc.
 */

#ifndef _WAPI_SHARED_H_
#define _WAPI_SHARED_H_

#include <mono_base/wapi-private.h>

typedef enum {
	WAPI_SHM_DATA,
	WAPI_SHM_FILESHARE
} _wapi_shm_t;

extern gpointer _wapi_shm_attach (_wapi_shm_t type);
extern void _wapi_shm_semaphores_init (void);
extern int _wapi_shm_sem_lock (int sem);
extern int _wapi_shm_sem_trylock (int sem);
extern int _wapi_shm_sem_unlock (int sem);

#endif /* _WAPI_SHARED_H_ */
