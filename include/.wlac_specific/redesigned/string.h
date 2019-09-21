// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

// wlac/redesigned/stdlib.h
// 2017 Dec 07

#ifndef __wlac_redesigned_string_h__
#define __wlac_redesigned_string_h__

// if we are here then include below is included
//#include <first_includes/common_include_for_headers.h>

#pragma include_alias( <string.h>, <string.h> )
#include <string.h>

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_strerror_needed) || defined(strerror_needed)
WLAC_EXPORT char* wlac_strerror(int errnum);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strcasecmp_needed)
WLAC_EXPORT int strcasecmp(const char *s1, const char *s2);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strncasecmp_needed)
WLAC_EXPORT int strncasecmp(const char *s1, const char *s2, size_t n);
#endif

END_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strerror_needed)
#define strerror wlac_strerror
#endif

#endif  // #ifndef __wlac_redesigned_string_h__
