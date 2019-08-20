// 
// (c) 2015-2018 WLAC. For details refers to LICENSE.md
//

// common_include_for_headers.h
// 2017 Dec 06
// created by D. Kalantaryan
// 
// This header does not introduces any symbol.
// Header includes other header "first_includes/common_definations_wul.h",
// that in turn again does not introduce any symbol
//

#ifndef WLAC2_first_includes__common_include_for_headers_h
#define WLAC2_first_includes__common_include_for_headers_h
#ifndef WLAC2_first_includes__common_definations_wul_h

#define WLAC2_INTERNAL_HEADER_INCLUDED

#ifdef _MSC_VER
//#define INCLUDE_NEXT	#include
#endif

#ifndef _WIN64
// In the UNIX like systems sizeof(time_t)==sizeof(void*)==sizeof(long)
#if !defined(_USE_32BIT_TIME_T)
#define _USE_32BIT_TIME_T
#endif  // #if !defined(_USE_32BIT_TIME_T)
#endif


#if defined(_MSC_VER)& (_MSC_VER >= 1900) & defined(WARNINGS_DISABLE)
#pragma warning(disable : 4312)
#pragma warning(disable : 4311)
#pragma warning(disable : 4302)
#pragma warning(disable : 4477)
#pragma warning(disable : 4018)		//'<' : signed/unsigned mismatch
#pragma warning(disable : 4244)		// Possible loss of data
#pragma warning(disable : 4267)		// Warning for integer type mismatch. In gcc ...
#pragma warning(disable : 4800)		// forcing value to bool ...
#pragma warning(disable : 4305)		//  truncation from 'double' to 'float'
#pragma warning(disable : 4805)		//  '==' : unsafe mix of type 'int' and type 'bool' in operation
#endif  // #if defined(_MSC_VER)& (_MSC_VER >= 1900) & defined(WARNINGS_DISABLE)

#include <.wlac_specific/first_includes/common_definations_wul.h>

#ifndef WLAC_INCLUDE_REDIRECTIONS_DONE
#define WLAC_INCLUDE_REDIRECTIONS_DONE

#pragma include_alias( <sys/stat.h>, <.wlac_specific/redesigned/sys/stat.h> )
#pragma include_alias( "sys/stat.h", ".wlac_specific/redesigned/sys/stat.h" )

#pragma include_alias( <sys/types.h>, <.wlac_specific/redesigned/sys/types.h> )
#pragma include_alias( "sys/types.h", ".wlac_specific/redesigned/sys/types.h" )

#pragma include_alias( <errno.h>, <.wlac_specific/redesigned/errno.h> )
#pragma include_alias( "errno.h", ".wlac_specific/redesigned/errno.h" )

#pragma include_alias( <fcntl.h>, <.wlac_specific/redesigned/fcntl.h> )
#pragma include_alias( "fcntl.h", ".wlac_specific/redesigned/fcntl.h" )

#pragma include_alias( <io.h>, <.wlac_specific/redesigned/io.h> )
#pragma include_alias( "io.h", ".wlac_specific/redesigned/io.h" )

#pragma include_alias( <process.h>, <.wlac_specific/redesigned/process.h> )
#pragma include_alias( "process.h", ".wlac_specific/redesigned/process.h" )

#pragma include_alias( <signal.h>, <.wlac_specific/redesigned/signal.h> )
#pragma include_alias( "signal.h", ".wlac_specific/redesigned/signal.h" )

#pragma include_alias( <stdio.h>, <.wlac_specific/redesigned/stdio.h> )
#pragma include_alias( "stdio.h", ".wlac_specific/redesigned/stdio.h" )

#pragma include_alias( <stdlib.h>, <.wlac_specific/redesigned/stdlib.h> )
#pragma include_alias( "stdlib.h", ".wlac_specific/redesigned/stdlib.h" )

#pragma include_alias( <time.h>, <.wlac_specific/redesigned/time.h> )
#pragma include_alias( "time.h", ".wlac_specific/redesigned/time.h" )

#pragma include_alias( <wchar.h>, <.wlac_specific/redesigned/wchar.h> )
#pragma include_alias( "wchar.h", ".wlac_specific/redesigned/wchar.h" )

#pragma include_alias( <direct.h>, <.wlac_specific/redesigned/direct.h> )
#pragma include_alias( "direct.h", ".wlac_specific/redesigned/direct.h" )

#pragma include_alias( <rpc.h>, <.wlac_specific/redesigned/rpc.h> )
#pragma include_alias( "rpc.h", ".wlac_specific/redesigned/rpc.h" )

#pragma include_alias( <fstream>, <.wlac_specific/redesigned/fstream> )
#pragma include_alias( "fstream", ".wlac_specific/redesigned/fstream" )

#pragma include_alias( <windows.h>, <.wlac_specific/redesigned/windows.h> )
#pragma include_alias( "windows.h", ".wlac_specific/redesigned/windows.h" )

#pragma include_alias( <WinSock2.h>, <.wlac_specific/redesigned/WinSock2.h> )
#pragma include_alias( "WinSock2.h", ".wlac_specific/redesigned/WinSock2.h" )


#pragma include_alias( <WS2tcpip.h>, <.wlac_specific/redesigned/WS2tcpip.h> )
#pragma include_alias( "WS2tcpip.h", ".wlac_specific/redesigned/WS2tcpip.h" )

#pragma include_alias( <stddef.h>, <.wlac_specific/redesigned/stddef.h> )
#pragma include_alias( "stddef.h", ".wlac_specific/redesigned/stddef.h" )

#pragma include_alias( <string.h>, <.wlac_specific/redesigned/string.h> )
#pragma include_alias( "string.h", ".wlac_specific/redesigned/string.h" )

#endif  // #ifndefWLAC_INCLUDE_REDIRECTIONS_DONE

#endif  // #ifndef WLAC2_first_includes__common_definations_wul_h
#endif  // #ifndef WLAC2_first_includes__common_include_for_headers_h
