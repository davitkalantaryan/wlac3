//
// file:			sys/ipc.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__ipc_h
#define WLAC2_sys__ipc_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>


/* Mode bits for `msgget', `semget', and `shmget'.  */
#ifndef IPC_CREAT
#define IPC_CREAT	01000		/* Create key if key does not exist. */
#define IPC_EXCL	02000		/* Fail if key exists.  */
#define IPC_NOWAIT	04000		/* Return error on wait.  */
#endif  // #ifndef IPC_CREAT

BEGIN_C_DECL2

#if !defined(key_t_defined) && !defined(key_t)
#define key_t_defined
typedef int ket_t;
#endif  // #if !defined(____key_t_defined) && !defined(__key_t_defined)


END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__ipc_h
