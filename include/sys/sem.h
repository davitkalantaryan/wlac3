//
// file:			sys/sem.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__sem_h
#define WLAC2_sys__sem_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

/* Commands for `semctl'.  */
#ifndef GETPID
#define GETPID		11		/* get sempid */
#define GETVAL		12		/* get semval */
#define GETALL		13		/* get all semval's */
#define GETNCNT		14		/* get semncnt */
#define GETZCNT		15		/* get semzcnt */
#define SETVAL		16		/* set semval */
#define SETALL		17		/* set all semval's */
#endif  // #ifndef GETPID

/* Flags for `semop'.  */
#ifndef SEM_UNDO
#define SEM_UNDO	0x1000		/* undo the operation on exit */
#endif

BEGIN_C_DECL2

#if !defined(key_t_defined) && !defined(key_t)
#define key_t_defined
typedef int ket_t;
#endif  // #if !defined(____key_t_defined) && !defined(__key_t_defined)

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(semget_needed)
WLAC_EXPORT int semget(key_t key, int nsems, int semflg);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(semctl_needed)
WLAC_EXPORT int semctl(int semid, int semnum, int cmd, ...);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(semop_needed)
WLAC_EXPORT int semop(int semid, struct sembuf *sops, size_t nsops);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__sem_h
