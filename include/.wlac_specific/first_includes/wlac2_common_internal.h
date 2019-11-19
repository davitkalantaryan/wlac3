// 
// file:			wlac2_common_internal.h
// created on:		2019 Aug 18 
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// 
#ifndef WLAC2_first_includes__wlac2_common_internal_h
#define WLAC2_first_includes__wlac2_common_internal_h
//#ifndef WLAC2_first_includes__common_definations_wul_h

#ifdef __INTELLISENSE__
typedef unsigned long       DWORD;
#endif

#ifndef DEFINE_WLAC_INTERNALS
#define DEFINE_WLAC_INTERNALS

#ifdef _WIN64
#ifdef __WORDSIZE
#undef __WORDSIZE
#endif
#define __WORDSIZE 64
#else
#ifndef _USE_32BIT_TIME_T
#define _USE_32BIT_TIME_T
#endif
#endif  // #ifdef _WIN64

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

#if		defined(_MSC_VER)
#define EXPORT_SYM_FROM_LIB2		_declspec(dllexport)
#define IMPORT_SYM_FROM_LIB2		_declspec(dllimport)
#define HIDDEN_SYMBOL3	
#if defined(__cplusplus) // check also version
#define CPP11_OR_HIGHER2
#endif
#elif	defined(__GNUC__)
#define EXPORT_SYM_FROM_LIB2		
#define IMPORT_SYM_FROM_LIB2	
#define HIDDEN_SYMBOL3				__attribute__((visibility(hidden)))	
#if defined(__cplusplus) // check also version
#define CPP11_OR_HIGHER2
#endif
#endif

#ifdef __cplusplus
#define STATIC_CAST2(_type,_value)		static_cast<_type>(_value)
#define REINTERPRET_CAST2(_type,_value)	reinterpret_cast<_type>(_value)
#define CONST_CAST2(_type,_value)		const_cast<_type>(_value)
#define DYNAMIC_CAST2(_type,_value)		dynamic_cast<_type>(_value)
#else
#define STATIC_CAST2(_type,_value)		((_type)(_value))
#define REINTERPRET_CAST2(_type,_value)	((_type)(_value))
#define CONST_CAST2(_type,_value)		((_type)(_value))
#define DYNAMIC_CAST2(_type,_value)		((_type)(_value))
#endif

// this should force to make compile time check when possible
#define ARGNONULL2

#ifdef WLAC_DLL_CRAETION
#define WLAC_EXPORT		EXPORT_SYM_FROM_LIB2
#elif defined(USING_WLAC_SOURCES_OR_STATIC_LIB)
#define WLAC_EXPORT
#else
#define WLAC_EXPORT		IMPORT_SYM_FROM_LIB2
#endif

#ifdef CPP11_OR_HIGHER2
#define NEWNULLPTR2	nullptr
#else
#define NEWNULLPTR2 NULL
#endif

#ifndef __THROW
#define __THROW
#endif

#ifndef RESTRICT
#if(_MSC_VER >= 1400)
#define RESTRICT	__restrict
#else
#define RESTRICT
#endif
#endif  // #ifndef RESTRICT

#define	USERGROUPID_EXPORT2

#endif  // #ifndef DEFINE_WLAC_INTERNALS


#ifndef HANDLE_MEM_DEF
#define HANDLE_MEM_DEF(_memory,...)	do{if(!(_memory)){exit(1);}}while(0)
#endif

#define LIKELY2(_cond)		(_cond) 
#define UNLIKELY2(_cond)	(_cond) 


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


#ifdef __cplusplus
#define INITIALIZER(f) \
        static void f(void); \
        struct f##_t_ { f##_t_(void) { f(); } }; static f##_t_ f##_; \
        static void f(void)
#elif defined(_MSC_VER)
#pragma section(".CRT$XCU",read)
#define INITIALIZER2_(f,p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_")) \
        static void f(void)
#if defined(_WIN64) || defined(_M_ARM)
#define INITIALIZER(f) INITIALIZER2_(f,"")
#else
#define INITIALIZER(f) INITIALIZER2_(f,"_")
#endif
#else
#define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif

//#endif  // #ifndef WLAC2_first_includes__common_definations_wul_h
#endif  // #ifndef WLAC2_first_includes__wlac2_common_internal_h
