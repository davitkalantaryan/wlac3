//  
// file:			src/wlac2/wlac_threading.c  
// created on:		2019 Sep 23  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  


#include <wlac_list_and_hashtables.h>
#include <.wlac_specific/redesigned/windows.h>
#include <wlac_internal_private.h>
#include <wlac_threading_private.h>
#include <unistd.h>
#include <malloc.h>

BEGIN_C_DECL2

HIDDEN_SYMBOL2 struct PthreadPrivate* GetOrCreateCurrentThreadData(void)
{
	struct PthreadPrivate* pThrData = STATIC_CAST2(struct PthreadPrivate*,TlsGetValue(gh_tlsPthreadDataKey));

	if(!pThrData){
		pthread_t currentThread = GetCurrentThread();
		pThrData = GetorCreateDataForThread(currentThread);
		if(!pThrData){return pThrData;}
		TlsSetValue(gh_tlsPthreadDataKey, pThrData);
	}

	return pThrData;
}


HIDDEN_SYMBOL2 struct PthreadPrivate*  GetorCreateDataForThread(pthread_t a_thread)
{
	struct PthreadPrivate* pThrData = STATIC_CAST2(pthread_t, HashByPointer_GetValueByKey_GlobalHash(a_thread));
	if (!pThrData) {
		pThrData = CreateThreadData(NEWNULLPTR2, a_thread);
		if (!pThrData) { return pThrData; }
		HashByPointer_AddNew_GlobalHash(a_thread, pThrData);
	}  // if(!pThrData){

	return pThrData;
}


HIDDEN_SYMBOL2 struct PthreadPrivate* CreateThreadData(struct PthreadPrivate* a_pParent, pthread_t a_threadHandle)
{
	struct sigaction* pParentAction;
	struct PthreadPrivate* pThreadData = STATIC_CAST2(struct PthreadPrivate*, calloc(1,sizeof(struct PthreadPrivate)));

	if(!pThreadData){return pThreadData;}

	pThreadData->parentThreadPtr = a_pParent;
	pThreadData->threadHandle = a_threadHandle;
	pThreadData->signalData.isSigactionCalled = 0;

	if(a_pParent){
		pParentAction = a_pParent->signalData.sigActions;
	}
	else {
		pParentAction = gh_globalSignalData.sigActions;
	}

	memcpy(pThreadData->signalData.sigActions,pParentAction,sizeof(pThreadData->signalData.sigActions));
	return pThreadData;
}


HIDDEN_SYMBOL2 void SetParentThreadPointer(struct PthreadPrivate* a_pParent, struct PthreadPrivate* a_childThreadData)
{
	if(!a_childThreadData->signalData.isSigactionCalled){
		if(a_pParent && a_pParent->signalData.isSigactionCalled){
			memcpy(a_childThreadData->signalData.sigActions, a_pParent->signalData.sigActions, sizeof(a_childThreadData->signalData.sigActions));
			a_childThreadData->signalData.isSigactionCalled = 1;
		}
	}
}


END_C_DECL2
