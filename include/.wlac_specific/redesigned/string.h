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

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_strerror_needed)
WLAC_EXPORT char* wlac_strerror(int errnum);
#endif

END_C_DECL2

#define strerror wlac_strerror

#endif  // #ifndef __wlac_redesigned_string_h__
