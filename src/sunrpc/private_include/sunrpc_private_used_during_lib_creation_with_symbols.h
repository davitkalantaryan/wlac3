// 
// file:			sunrpc_private_used_during_lib_creation_with_symbols.h
// created on:		2019 Aug 18 
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// 
#ifndef WLAC2_sunrpc_private_used_during_lib_creation_with_symbols_h
#define WLAC2_sunrpc_private_used_during_lib_creation_with_symbols_h

#include <rpc/wlac2_sunrpc_internal.h>

#ifdef _WIN32

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#define WSAerrno (WSAGetLastError())
#define gettimeofday(tv,tz) ((tv)->tv_sec = (long)time(0), (tv)->tv_usec = 0)

#endif  // #ifdef _WIN32

#include "sunrpc_private_used_during_lib_creation.h"
#include <time.h>


#endif   // #ifndef WLAC2_sunrpc_private_used_during_lib_creation_with_symbols_h
