//
// file:			netinet/in.h
// created on:		2019 Aug 19
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_netinet__in_h
#define WLAC2_netinet__in_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

BEGIN_C_DECL2

#ifndef CINTERFACE
#define CINTERFACE
#define CINTERFACE_here_defined
#endif

#ifndef NOMINMAX
#define NOMINMAX
#define NOMINMAX_here_defined
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <Winldap.h>

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(bindresvport_needed)
WLAC_EXPORT int bindresvport(int sockfd, struct sockaddr_in *sin);
#endif


#ifdef CINTERFACE_here_defined
#undef CINTERFACE_here_defined
#undef CINTERFACE
#endif

#ifdef NOMINMAX_here_defined
#undef NOMINMAX_here_defined
#undef NOMINMAX
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_netinet__in_h
