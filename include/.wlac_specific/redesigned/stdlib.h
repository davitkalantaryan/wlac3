// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

// wlac/redesigned/stdlib.h
// 2017 Dec 07

#ifndef __wlac_redesigned_stdlib_h__
#define __wlac_redesigned_stdlib_h__

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/.privatei/header_for_resolving_errno.h>


BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_getenv_needed) || defined(getenv_needed)
WLAC_EXPORT char* wlac_getenv(const char* a_name);
#endif

END_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(getenv_needed)
#define getenv wlac_getenv
#endif

#endif  // #ifndef __wlac_redesigned_stdlib_h__
