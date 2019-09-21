// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

/*
 *	File: <time_new.h> For WINDOWS MFC
 *
 *	Created on: Dec 23, 2015
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *
 */
#ifndef __win_time_new_h__
#define __win_time_new_h__

// if we are here then include below is included
//#include <first_includes/common_include_for_headers.h>

#pragma include_alias( <time.h>, <time.h> )
#pragma include_alias( "time.h", "time.h" )
#include <time.h>

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strerror_needed)
#ifdef strftime
#undef strftime
#endif
#define strftime wlac_strftime
#endif


#if defined(_MSC_VER) && (_MSC_VER>=1900) && defined(_INC_TIME)
#define TIMESPEC_NOT_NEEDED
#endif

#if !defined(__timespec_defined) && !defined(timespec_defined) && !defined(TIMESPEC_NOT_NEEDED)
struct timespec {
	time_t   tv_sec;        /* seconds */
	long     tv_nsec;       /* nanoseconds */
};
#ifndef _CRT_NO_TIME_T
#define _CRT_NO_TIME_T
#endif
#define __timespec_defined
#define timespec_defined
#endif  // #if !defined(__timespec_defined) && !defined(timespec_defined)

//char *ctime_r(const time_t *timep, char *buf);
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(ctime_r_needed)
#if !defined(ctime_r) & !defined(ctime_r_defined)
#define ctime_r(_a_timep, _a_buf)	(ctime((_a_timep)) ? strcpy((_a_buf),ctime((_a_timep))) : NULL)
#endif  // #if !defined(ctime_r) & !defined(ctime_r_defined)
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(localtime_r_needed)
#ifdef localtime_r
#undef localtime_r
#endif
#define	localtime_r(_timep_,_result_)	(localtime(_timep_) ? ((struct tm*)memcpy((_result_),localtime(_timep_),sizeof(struct tm))) : NEWNULLPTR2)
#endif

BEGIN_C_DECL2

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(nanosleep_needed)
WLAC_EXPORT int nanosleep(const struct timespec *a_req, struct timespec *a_rem);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strptime_needed)
WLAC_EXPORT char *strptime(const char *s, const char *format, struct tm *tm);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_strftime_needed) || defined(strftime_needed)
WLAC_EXPORT size_t wlac_strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(gettimeofday_needed)
WLAC_EXPORT int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif

#if (!defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(strftime_needed)) && !defined(strftime_not_needed)
#define strftime	wlac_strftime
#endif

END_C_DECL2


#endif  /* #ifndef __win_time_new_h__ */
