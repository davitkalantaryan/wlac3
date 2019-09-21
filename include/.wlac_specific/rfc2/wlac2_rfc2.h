//
// file:		rfc/wlac_rfc.h
// created on:	2018 Dec 17
//

#ifndef __wlac_rfc_wlac_rfc_h__
#define __wlac_rfc_wlac_rfc_h__

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#ifndef CINTERFACE
#define CINTERFACE
#define CINTERFACE_here_defined
#endif
#ifndef NOMINMAX
#define NOMINMAX
#define NOMINMAX_here_defined
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stddef.h>
//SET_WLAC_ALIAS(stdio.h)

#define RFC2_NO_ERROR				0
#define RFC2_UNKNOWN_ERROR			-1
#define RFC2_LIBRARY_NOT_FOUND		-2
#define RFC2_FUNCTION_NOT_FOUND		-3

#ifndef RFC_API_FAR
#ifdef ___RFC_LIB_CREATION___
#define RFC2_API_FAR		EXPORT_SYM_FROM_LIB2
#define RFC2_VAR_FAR		extern EXPORT_SYM_FROM_LIB2
#elif defined(__USING_RFC_SOURCES__)  // #ifdef ___GEM_LIB_CREATION___
#define RFC2_API_FAR
#define RFC2_VAR_FAR		extern
#else   // #ifdef ___GEM_LIB_CREATION___
#define RFC2_API_FAR		IMPORT_SYM_FROM_LIB2
#define RFC2_VAR_FAR		IMPORT_SYM_FROM_LIB2
#endif  // #ifdef ___GEM_LIB_CREATION___
#endif  // #ifndef GEM_API_FAR


BEGIN_C_DECL2

typedef void* (*TypeFunctionIsCalledOnRemote)(void*,int);

RFC2_API_FAR int CallFunctionOnRemoteProcess(
	HANDLE hProcess, const char* libName,const char* fncName,void* data, size_t memorySize,void** pReturn);
RFC2_API_FAR int CallFunctionOnRemoteProcessByPid(
	int pid, const char* libName,const char* fncName,void* data, size_t memorySize,void** pReturn);

RFC2_VAR_FAR	int	g_nRfcLibraryLoggingLevel;

END_C_DECL2

#ifdef CINTERFACE_here_defined
#undef CINTERFACE_here_defined
#undef CINTERFACE
#endif
#ifdef NOMINMAX_here_defined
#undef NOMINMAX_here_defined
#undef NOMINMAX
#endif


#endif  // #ifndef __wlac_rfc_wlac_rfc_h__
