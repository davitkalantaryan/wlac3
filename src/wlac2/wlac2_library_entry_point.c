//  
// file:			src/wlac2/wlac2_library_entry_point.c  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  


#include <wlac_list_and_hashtables.h>
#include <wlac_threading_private.h>
#include <.wlac_specific/redesigned/windows.h>
#include <wlac_internal_private.h>
#include <unistd.h>

#define UNUSED2(x) (void)(x)

BEGIN_C_DECL2

HIDDEN_SYMBOL2 DWORD	gh_tlsPthreadDataKey	= TLS_OUT_OF_INDEXES;
HIDDEN_SYMBOL2 int		gh_nLibraryExitStarted	= 0;
HIDDEN_SYMBOL2 int		gh_nFreeLibraryCalled	= 0;
HIDDEN_SYMBOL2 char		gh_path[MAX_PATH];

static int				s_nSocketLibraryInited = 0;

static int  WlacInitializeStatic(void* pReservedArg,HINSTANCE a_hinstDLL);
static void WlacCleanStatic(void* pReservedArg);

static void DefaultSignalFunction(int a_sigNum) { UNUSED2(a_sigNum); }
static void Default_sa_restorer(void) {}

BOOL WINAPI DllMain(
	_In_ HINSTANCE a_hinstDLL,
	_In_ DWORD     a_fdwReason,
	_In_ LPVOID    a_lpvReserved)
{
	switch(a_fdwReason){
	case DLL_PROCESS_ATTACH:
		if(WlacInitializeStatic(a_lpvReserved,a_hinstDLL)){
			return FALSE;
		}
		break;
	case DLL_PROCESS_DETACH:
		WlacCleanStatic(a_lpvReserved);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}


WLAC_EXPORT void WLAC2_DllMain_For_Clean_Called(void* a_pReservedArg)
{
	if(!gh_nLibraryExitStarted){
		gh_nLibraryExitStarted = 1;
		gh_nFreeLibraryCalled = !a_pReservedArg ? 1 : 0;
	}
}


static int WlacInitializeStatic(void* a_pReservedArg,HINSTANCE a_hinstDLL)
{
	WORD wVersionRequested;
	WSADATA wsaData;

	gh_nLibraryExitStarted = 0;
	gh_nFreeLibraryCalled = 0;

	GetModuleFileNameA(a_hinstDLL,gh_path,MAX_PATH);

	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		WlacCleanStatic(a_pReservedArg);
		return -1;
	}
	s_nSocketLibraryInited = 1;
	/* Confirm that the WinSock DLL supports 2.2.		*/
	/* Note that if the DLL supports versions greater	*/
	/* than 2.2 in addition to 2.2, it will still return*/
	/* 2.2 in wVersion since that is the version we		*/
	/* requested.										*/
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WlacCleanStatic(a_pReservedArg);
		return -2;
	}

	gh_mutexForGlobalHash = CreateMutex(NEWNULLPTR2, FALSE, NEWNULLPTR2);
	if(!gh_mutexForGlobalHash){
		WlacCleanStatic(a_pReservedArg);
		return -1;
	}

	//gh_mutexForGlobalSigactions= CreateMutex(NEWNULLPTR2, FALSE, NEWNULLPTR2);
	//if (!gh_mutexForGlobalSigactions) {
	//	WlacCleanStatic(a_pReservedArg);
	//	return -2;
	//}

	gh_pWlacGlobalHash = HashByPointer_CreateAndConstruct(WLAC_GLOBAL_HASH_SIZE);
	if(!gh_pWlacGlobalHash){
		WlacCleanStatic(a_pReservedArg);
		return -3;
	}

	if( TLS_OUT_OF_INDEXES == (gh_tlsPthreadDataKey = TlsAlloc() )  ){
		WlacCleanStatic(a_pReservedArg);
		return -4;
	}

	return 0;
}


static void WlacCleanStatic(void* a_pReservedArg)
{
	int i;

	WLAC2_DllMain_For_Clean_Called(a_pReservedArg);
	gh_path[0] = 0;
	if(gh_pWlacGlobalHash){
		HashByPointer_DestructAndFree(gh_pWlacGlobalHash);
		gh_pWlacGlobalHash = NEWNULLPTR2;
	}

	if (gh_mutexForGlobalHash) {
		CloseHandle(gh_mutexForGlobalHash);
		gh_mutexForGlobalHash = NEWNULLPTR2;
	}

	//if (gh_mutexForGlobalSigactions) {
	//	CloseHandle(gh_mutexForGlobalSigactions);
	//	gh_mutexForGlobalSigactions = NEWNULLPTR2;
	//}

	if(gh_tlsPthreadDataKey!=TLS_OUT_OF_INDEXES){
		TlsFree(gh_tlsPthreadDataKey);
		gh_tlsPthreadDataKey = TLS_OUT_OF_INDEXES;
	}

	for(i=0;i< _NSIG;++i){
		gh_globalSignalData.sigActions[i].sa_flags = 0; // if SA_SIGINFO then more verbose function is used
		sigemptyset(&(gh_globalSignalData.sigActions[i].sa_mask));
		gh_globalSignalData.sigActions[i].sa_handler = &DefaultSignalFunction;
		gh_globalSignalData.sigActions[i].sa_restorer = &Default_sa_restorer;
	}

	if (s_nSocketLibraryInited) {
		WSACleanup();
		s_nSocketLibraryInited = 0;
	}
}


END_C_DECL2
