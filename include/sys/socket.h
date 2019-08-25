//
// file:			sys/socket.h
// created on:		2019 Aug 19
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__socket_h
#define WLAC2_sys__socket_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

#include <netinet/in.h>
#include <sys/ioctl.h>

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(gethostbyname_r_needed)
int gethostbyname_r(const char *name,
	struct hostent *ret, char *buf, size_t buflen,
	struct hostent **result, int *h_errnop);
#endif


END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__socket_h
