//
// file:			wlac2_unix_like_signaling.c  
// created on:		2019 Aug 27
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/signal.h>
#include <memory.h>

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigemptyset_needed)
WLAC_EXPORT int sigemptyset(sigset_t *a_set)
{
	memset(a_set->__val, 0, sizeof(a_set->__val));
	return 0;
}
#endif


#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaddset_needed)
WLAC_EXPORT int sigaddset(sigset_t *a_set, int a_signo)
{
	if (a_set && (a_signo < _SIGSET_NWORDS)) {
		a_set->__val[a_signo] = 1;
	}
	return 0;
}
#endif
