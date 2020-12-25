/*
 *	File: gem_timing_functions.cpp
 *
 *	Created on: Dec 23, 2015
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements all functions connected to posix threading
 *		1) gettimeofday
 *		2) usleep
 *		3) nanosleep
 *
 *
 */

#include <sys/time.h>
#include <.wlac_specific/redesigned/windows.h>
#include <time.h>

BEGIN_C_DECL2


WLAC_EXPORT int gettimeofday(struct timeval *a_tv, struct timezone *a_tz)
{
	static void* spPointer = NEWNULLPTR2;
	FILETIME ft;
	unsigned __int64 tmpres = 0;
#if(_MSC_VER >= 1400)
	long lnTzTemp;
	int nldTemp;
#endif

	if (a_tv){
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		tmpres /= 10;  /*convert into microseconds*/
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		a_tv->tv_sec = (long)(tmpres / 1000000UL);
		a_tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (a_tz){
		// (setting timezone environmental variable) once
		if (InterlockedCompareExchangePointerNew(&spPointer, (void*)1, NULL) == NULL)
		{
			_tzset();
		}
#if(_MSC_VER >= 1400)
		_get_timezone(&lnTzTemp);
		a_tz->tz_minuteswest = lnTzTemp / 60;
		_get_daylight(&nldTemp);
		a_tz->tz_dsttime = nldTemp;
#else
		a_tz->tz_minuteswest = _timezone / 60;
		a_tz->tz_dsttime = _daylight;
#endif
	}

	return 0;
}


/// Should be cheched
#if 1
#define usleep(_x)		SleepEx(STATIC_CAST2(DWORD,(_x))/1000,TRUE)
#else
WLAC_EXPORT int usleep(int64_t a_usec)
{
#if 0
	struct timeval tv;
	struct timeval* pTv = NULL;
	int maxsd, fh1;
	fd_set rfds;

	fh1 = (int)socket(AF_INET, SOCK_STREAM, 0);

	//fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET((unsigned int)fh1, &rfds);
	maxsd = fh1 + 1;

	if (a_usec > 0)
	{
		tv.tv_sec = a_usec / 1000000L;
		tv.tv_usec = a_usec % 1000000L;
		pTv = &tv;
	}

	return (long)select(maxsd, &rfds, 0, 0, pTv);
#else

	DWORD msSleep = (DWORD)(a_usec / (int64_t)1000);
	Sleep(msSleep);
	return 0;

#endif
}
#endif


WLAC_EXPORT int nanosleep(const struct timespec *a_req, struct timespec *a_rem)
{
	int64_t timeToWait = a_req ? (a_req->tv_sec * 1000000 + a_req->tv_nsec / 1000) : 0;
	return usleep(timeToWait);
}


#if defined(_MSC_VER) & (_MSC_VER >= 1400)
#else  // #if defined(_MSC_VER) & (_MSC_VER >= 1400)
GEM_API struct tm *gmtime_r(const time_t *a_timep, struct tm *a_result)
{
	struct tm * result = gmtime(a_timep);

	if (!result) return NULL;
	memcpy(a_result, result, sizeof(struct tm));
	return a_result;
}
#endif // #if defined(_MSC_VER) & (_MSC_VER >= 1400)


END_C_DECL2



