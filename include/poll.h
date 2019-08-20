//
// file:			poll.h
// created on:		2019 Aug 19
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_poll_h
#define WLAC2_poll_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_cmmon_internal.h>

BEGIN_C_DECL2

/* Type used for the number of file descriptors.  */
typedef unsigned long int nfds_t;

#if !defined(IFNORE_ALL_WLAC_SYMBOLS) || defined(poll_sockets_needed) || defined(poll_needed)
WLAC_EXPORT int poll_sockets(struct pollfd *fds, nfds_t nfds, int timeout);
#endif

#if !defined(IFNORE_ALL_WLAC_SYMBOLS) || defined(wlac_poll_needed) || defined(poll_needed)
WLAC_EXPORT int wlac_poll(struct pollfd *fds, nfds_t nfds, int timeout);
#endif


END_C_DECL2


#if !defined(IGNORE_WLAC_POLL) && !defined(poll)
#define  poll wlac_poll
#endif  // #if !defined(_IGNORE_WLAC_POLL) && !defined(poll)


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_poll_h
