//
// file:			strings.h
// created on:		2019 Aug 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef WLAC2__strings_h
#define WLAC2__strings_h
#ifndef WLAC_IGNORE_ALL_IN_HEADERS

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/sys/types.h>

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strcasecmp_needed)
WLAC_EXPORT int strcasecmp(const char *s1, const char *s2);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strncasecmp_needed)
WLAC_EXPORT int strncasecmp(const char *s1, const char *s2, size_t n);
#endif

END_C_DECL2


#endif  // #ifndef WLAC_IGNORE_ALL_IN_HEADERS
#endif  // #ifndef WLAC2__strings_h
