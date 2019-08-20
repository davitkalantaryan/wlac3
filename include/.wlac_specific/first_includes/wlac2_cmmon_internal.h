// 
// file:			windows_sunrpc_internal.h
// created on:		2019 Aug 18 
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// 
#ifndef WLAC2_first_includes__wlac2_common_internal_h
#define WLAC2_first_includes__wlac2_common_internal_h
//#ifndef WLAC2_first_includes__common_definations_wul_h

#ifndef DEFINE_WLAC_INTERNALS
#define DEFINE_WLAC_INTERNALS

#ifdef __cplusplus
#define BEGIN_C_DECL2		extern "C"{
#define END_C_DECL2			}
#define EXTERN_C_EXP2		extern "C"
#else
#define BEGIN_C_DECL2		
#define END_C_DECL2			
#define EXTERN_C_EXP2		extern 
#endif

#define REGISTER2			register

#ifdef WLAC_DLL_CRAETION

#define WLAC_EXPORT

#elsif defined(USING_WLAC_SOURCES_OR_STATIC_LIB)

#define WLAC_EXPORT

#else

#define WLAC_EXPORT

#endif


#endif  // #ifndef DEFINE_WLAC_INTERNALS

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

#endif  // #ifndef WLAC_INCLUDE_REDIRECTIONS_DONE

//#endif  // #ifndef WLAC2_first_includes__common_definations_wul_h
#endif  // #ifndef WLAC2_first_includes__wlac2_common_internal_h
