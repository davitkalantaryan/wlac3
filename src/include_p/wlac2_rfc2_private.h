//
// file:		wlac_rfc_private.h
// created on:	2018 Dec 17
//

#ifndef __wlac_wlac_rfc_private_h__
#define __wlac_wlac_rfc_private_h__

#ifndef IGNORE_ALL_WLAC_SYMBOLS
#define IGNORE_ALL_WLAC_SYMBOLS
#endif

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include ".wlac_specific/rfc2/wlac2_rfc2.h"
#include <stddef.h>
#include <stdint.h>

#ifndef RFC_API
#ifdef ___RFC_LIB_CREATION___
#define RFC2_API			EXPORT_SYM_FROM_LIB2
#define RFC2_VAR			extern EXPORT_SYM_FROM_LIB2
#elif defined(__USING_GEM_SOURCES__)  // #ifdef ___GEM_LIB_CREATION___
#define RFC2_API
#define RFC2_VAR			extern
#else   // #ifdef ___GEM_LIB_CREATION___
#define RFC2_API			IMPORT_FROM_LIB_API
#define RFC2_VAR			IMPORT_FROM_LIB_VAR
#endif  // #ifdef ___GEM_LIB_CREATION___
#endif  // #ifndef GEM_API

#ifndef AllocMemOnRemoteProcess
#define		AllocMemOnRemoteProcess(__hProcess, __size) \
					VirtualAllocEx((__hProcess),0,(__size),MEM_COMMIT,PAGE_READWRITE)
#endif // #ifndef AllocMemOnRemoteProcess
#ifndef DeleteMemOnRemoteProcess
#define		DeleteMemOnRemoteProcess(__hProcess,__mem) \
					VirtualFreeEx((__hProcess),(LPVOID)((size_t)(__mem)), 0, MEM_RELEASE)
#endif  // #ifndef DeleteMemOnRemoteProcess

BEGIN_C_DECL2

struct SInjectedType {
	uint64_t	dllNameLen;		// rounded to 8
	//uint16_t	funcionNameLen;	// rounded to 8
	//uint64_t	dllName;		// should be casted to char*
	//uint64_t	functionName;	// should be casted to char*
	uint64_t	memorySize;		// is a same as provided by user, but allocation done more
	//uint64_t	memoryAddress;
};

#define ROUND_FOR_PADDING(_value)							(   (  ((_value)>>3)+1  )<<3   )
#define DLL_NAME_FROM_INJECT(_injectData)					(  ( (char*)(_injectData) ) + sizeof(struct SInjectedType)   )
#define MEMORY_FROM_INJECT(_injectData, _injectLocal)		(  DLL_NAME_FROM_INJECT(_injectData) + \
																((size_t)(_injectLocal).dllNameLen)  )
#define FUNCTION_NAME_FROM_INJECT(_injectData,_injectLocal)	(  MEMORY_FROM_INJECT(_injectData,_injectLocal) + \
																( (size_t)ROUND_FOR_PADDING( (_injectLocal).memorySize ) )  )


END_C_DECL2


#endif  // #ifndef __wlac_wlac_rfc_private_h__
