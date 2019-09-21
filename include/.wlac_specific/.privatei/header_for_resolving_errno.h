// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

// header_for_resolving_errno.h
// 2017 Dec 29

#ifndef WLAC2_dot_privatei__header_for_resolving_errno_h
#define WLAC2_dot_privatei__header_for_resolving_errno_h

//#include <first_includes/common_include_for_headers.h>
#include <.wlac_specific/first_includes/wlac2_common_internal.h>

#pragma include_alias( <errno.h>, <errno.h> )
#pragma include_alias( <stddef.h>, <stddef.h> )
#pragma include_alias( <stdlib.h>, <stdlib.h> )

#pragma include_alias( "errno.h", "errno.h" )
#pragma include_alias( "stddef.h", "stddef.h" )
#pragma include_alias( "stdlib.h", "stdlib.h" )

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
//#pragma include_alias( <stdlib.h>, <redesigned/stdlib.h> )
//#pragma include_alias( <stddef.h>, <redesigned/stddef.h> )
//#pragma include_alias( <errno.h>, <redesigned/errno.h> )

__BEGIN_C_DECLS

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_errno_needed) || defined(errno_needed)
GEM_API_FAR int* wlac_errno(void);
#endif
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(wlac_exit_needed) || defined(exit_needed)
GEM_API_FAR void wlac_exit(int status, int signal);
#endif

__END_C_DECLS

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(errno_needed)
#ifdef errno
#undef errno
#endif
#define errno (*wlac_errno())
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(exit_needed)
#if ( !defined(__cplusplus)||defined(exit_redefination_needed) ) && !defined(exit_redefination_not_needed)

#ifdef SIGNAL_FOR_EXIT
#define exit(_status_) \
	do{ \
		printf("Fl:%s,ln:%d: ExitCall(%d)\n",__FILE_FROM_PATH__(__FILE__),__LINE__,(_status_)); \
		wlac_exit((_status_),SIGNAL_FOR_EXIT);\
	}while(0)
#else
#define exit _exit
#endif

#endif   // #if ( !defined(__cplusplus)||defined(exit_redefination_needed) ) && !defined(exit_redefination_not_needed)
#endif  // #if !defined(IGNORE_ALL_WLAC_SYMBOLS) ||defined(exit_needed)


#endif  // #ifndef WLAC2_dot_privatei__header_for_resolving_errno_h
