//
// file:			sys/shm.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__shm_h
#define WLAC2_sys__shm_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

#ifndef PATH_MAX
#define PATH_MAX	1024
#endif

BEGIN_C_DECL2

#if !defined(key_t_defined) && !defined(key_t)
#define key_t_defined
typedef int ket_t;
#endif  // #if !defined(____key_t_defined) && !defined(__key_t_defined)

struct sembuf
{
	unsigned short int sem_num;	/* semaphore number */
	short int sem_op;		/* semaphore operation */
	short int sem_flg;		/* operation flag */
};

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmctl_needed)
WLAC_EXPORT int shmctl(int shmid, int cmd, struct shmid_ds *buf);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmget_needed)
int shmget(key_t key, size_t size, int shmflg);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__shm_h
