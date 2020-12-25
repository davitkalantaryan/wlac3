//
// file:			wlac2_unix_like_signaling.c  
// created on:		2019 Aug 27
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <.wlac_specific/redesigned/signal.h>
#include <memory.h>
#include <wlac_threading_private.h>
#include <wlac_internal_private.h>
#include <.wlac_specific/rfc2/wlac2_rfc2.h>

#define HIDDEN_SYMBOL2 static

BEGIN_C_DECL2

HIDDEN_SYMBOL3 struct PSignalData			gh_globalSignalData;

static _inline BOOL CheckSignalValidity(int a_sig)
{
	if ((a_sig >= 0) && (a_sig < _NSIG)) {
		return TRUE;
	}
	return FALSE;
}

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigemptyset_needed)
WLAC_EXPORT int sigemptyset(sigset_t *a_set)
{
	memset(a_set->__val, 0, sizeof(a_set->__val));
	return 0;
}
#endif


#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaddset_needed)
WLAC_EXPORT int sigaddset(sigset_t *a_set, int a_signo)
{
	if (a_set && (a_signo < _SIGSET_NWORDS)) {
		a_set->__val[a_signo] = 1;
	}
	return 0;
}
#endif

// todo: Empty
#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(sigaction_needed)
WLAC_EXPORT int sigaction(int a_sig, const struct sigaction * a_action, struct sigaction * a_oldAction)
{
	struct PthreadPrivate* pThisThreadData ;

	if(!CheckSignalValidity(a_sig)){
		return ERANGE;
	}

	pThisThreadData = GetOrCreateCurrentThreadData();
	if(!pThisThreadData){
		return ENOMEM;
	}

	if(a_oldAction){
		*a_oldAction = pThisThreadData->signalData.sigActions[a_sig];
	}

	if(a_action){
		pThisThreadData->signalData.sigActions[a_sig] = *a_action;
		SET_SIGACTION_BIT(pThisThreadData->signalData.isSigactionCalled2,a_sig);
		gh_globalSignalData.sigActions[a_sig] = *a_action;
		SET_SIGACTION_BIT(gh_globalSignalData.isSigactionCalled2,a_sig);
	}

	return 0;
}
#endif


#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(kill_needed)

WLAC_EXPORT void* FunctionCalledOnRemoteProcess(void* a_pData, size_t a_nMemoryLength)
{
	struct siginfo* pSigData = STATIC_CAST2(struct siginfo*, a_pData);

	if((a_nMemoryLength!=sizeof(struct siginfo))||(!pSigData)){
		return STATIC_CAST2(void*,ENODATA);
	}

	if(!CheckSignalValidity(pSigData->si_signo)){
		return STATIC_CAST2(void*, ERANGE);
	}

	if(pSigData->si_signo==SIGKILL){
		_Exit(3);
	}

	// 1. check whether signal is ignored
	//		// 1.a if yes, then check whether sigwait is there

	return NEWNULLPTR2;
}

WLAC_EXPORT int kill(pid_t a_pid, int a_sig)
{
	struct siginfo	sigData;
	void* pReturn;

	if(!CheckSignalValidity(a_sig)){
		return ERANGE;
	}

	sigData.si_signo = a_sig;

	CallFunctionOnRemoteProcessByPid(a_pid,gh_path,"FunctionCalledOnRemoteProcess",&sigData,sizeof(struct siginfo),&pReturn);

	return STATIC_CAST2(int, REINTERPRET_CAST2(size_t,pReturn));
}
#endif

END_C_DECL2
