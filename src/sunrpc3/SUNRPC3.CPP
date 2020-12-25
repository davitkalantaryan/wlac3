// sunrpc.cpp : Defines the entry point for the DLL application.
//

#include "sunrpc_private_used_during_lib_creation_with_symbols.h"
#include "sunrpc.h"


EXTERN_C_EXP2 void sun_rpc_report(const char* lpszMsg);
EXTERN_C_EXP2 int sun_rpc_init(void);
EXTERN_C_EXP2 int sun_rpc_exit(void);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			 sun_rpc_init();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
				sun_rpc_exit();
			break;
    }
    return TRUE;
}


/*
// This is an example of an exported variable
SUNRPC_API int nSunrpc=0;

// This is an example of an exported function.
SUNRPC_API int fnSunrpc(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see sunrpc.h for the class definition
CSunrpc::CSunrpc()
{ 
	return; 
}

*/