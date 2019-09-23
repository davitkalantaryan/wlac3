// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

// 2017 Dec 07

#ifndef __wlac_stdio_h__
#define __wlac_stdio_h__

#include <.wlac_specific/first_includes/common_include_for_headers.h>

#pragma include_alias( <stdio.h>, <stdio.h> )
#pragma include_alias( "stdio.h", "stdio.h" )
#include <stdio.h>
#include <share.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#include <corecrt_io.h>
#endif

__BEGIN_C_DECLS

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_fopen_needed) || defined(fopen_needed)
GEM_API_FAR FILE* wlac_fopen(const char* fileName, const char* mode);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_rename_needed) || defined(rename_needed)
GEM_API_FAR int wlac_rename(const char *oldname, const char *newname);
#endif

#ifdef _WIN64
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_snprintf_needed) || defined(snprintf_needed)
GEM_API_FAR int wlac_snprintf(char* buffer, size_t count, const char* format, ...);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_sprintf_needed) || defined(sprintf_needed)
GEM_API_FAR int wlac_sprintf(char* buffer, const char* format, ...);
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_sscanf_needed) || defined(sscanf_needed)
GEM_API_FAR int wlac_sscanf(const char* buffer, const char* format,...);
#endif
#endif   // #ifdef _WIN64

__END_C_DECLS

#ifndef NOT_USE_WLAC_REDESIGNED
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(fopen_needed)
#ifdef fopen
#undef fopen
#endif
#define fopen wlac_fopen
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(rename_needed)
#ifdef rename
#undef rename
#endif
#define rename wlac_rename
#endif

#ifdef _WIN64

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(snprintf_needed)
#ifdef snprintf
#undef snprintf
#endif
#define snprintf wlac_snprintf
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sprintf_needed)
#ifdef sprintf
#undef sprintf
#endif
#define sprintf wlac_sprintf
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sscanf_needed)
#ifdef sscanf
#undef sscanf
#endif
#define sscanf wlac_sscanf
#endif

#else  // #ifdef _WIN64

#endif   //#ifndef NOT_USE_WLAC_REDESIGNED

#if defined(_MSC_VER) & (_MSC_VER>1400)
#pragma warning (disable:4996)
#endif

#endif  // #ifdef _WIN64


#endif  // #ifndef __wlac_stdio_h__
