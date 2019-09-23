//
// file:			sys/ioctl.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__ioctl_h
#define WLAC2_sys__ioctl_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>

#define		SIOCGIFCONF		0x8912		/* get iface list		*/
#define		SIOCGIFFLAGS	0x8913		/* get flags			*/

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(ioctl_needed)
WLAC_EXPORT int ioctl(int d, int request, ...);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__ioctl_h
