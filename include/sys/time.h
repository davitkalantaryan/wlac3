//
// file:			sys/time.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2_sys__time_h
#define WLAC2_sys__time_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/sys/types.h>

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(gettimeofday_needed)
WLAC_EXPORT int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2_sys__time_h
