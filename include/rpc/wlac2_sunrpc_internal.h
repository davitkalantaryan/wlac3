// 
// file:			windows_sunrpc_internal.h
// created on:		2019 Aug 18 
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// 
#ifndef WLAC2_rpc__wlac2_sunrpc_internal_h
#define WLAC2_rpc__wlac2_sunrpc_internal_h

#ifdef SUNRPC_LIB_CREATION
#define SUNRPC_LIB_EXPORT	_declspec(dllexport)
#elif defined(SUNRPC_SOURCES_USED)
#define SUNRPC_LIB_EXPORT
#else
#define SUNRPC_LIB_EXPORT	_declspec(dllimport)
#endif

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

#endif  // #ifndef DEFINE_WLAC_INTERNALS
#endif  // #ifndef WLAC2_rpc__wlac2_sunrpc_internal_h
