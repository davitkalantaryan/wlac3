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

#define HIDDEN_SYMBOL2 static

BEGIN_C_DECL2

HIDDEN_SYMBOL2 struct WlacListItem*			gh_allThreads = NEWNULLPTR2;


HIDDEN_SYMBOL2 void FreeThreadData(struct PthreadPrivate* a_threadData)
{
	free(a_threadData);
}


HIDDEN_SYMBOL2 struct PthreadPrivate* CreateThreadData(struct PthreadPrivate* a_pParent, pthread_t a_threadHandle)
{
	struct sigaction* pParentAction;
	struct PthreadPrivate* pThreadData = STATIC_CAST2(struct PthreadPrivate*, calloc(1,sizeof(struct PthreadPrivate)));

	if(!pThreadData){return pThreadData;}

	pThreadData->parentThreadPtr = a_pParent;
	pThreadData->threadHandle = a_threadHandle;
	memset(pThreadData->signalData.isSigactionCalled2,0,sizeof(pThreadData->signalData.isSigactionCalled2));

	if(a_pParent){
		pParentAction = a_pParent->signalData.sigActions;
	}
	else {
		pParentAction = gh_globalSignalData.sigActions;
	}

	memcpy(pThreadData->signalData.sigActions,pParentAction,sizeof(pThreadData->signalData.sigActions));
	return pThreadData;
}


HIDDEN_SYMBOL2 struct PthreadPrivate*  GetOrCreateDataForThread(pthread_t a_thread)
{
	struct PthreadPrivate* pThrData = STATIC_CAST2(pthread_t, HashByPointer_GetValueByKey_GlobalHash(a_thread));
	if (!pThrData) {
		void* pOldData;
		pThrData = CreateThreadData(NEWNULLPTR2, a_thread);
		if (!pThrData) { return pThrData; }
		if(LIST_ADD_ALREADY_EXIST==HashByPointer_AddNew_GlobalHash(a_thread, pThrData,&pOldData)){
			FreeThreadData(pThrData);
			pThrData = STATIC_CAST2(pthread_t,pOldData);
		}
	}  // if(!pThrData){

	return pThrData;
}

HIDDEN_SYMBOL3 struct PthreadPrivate* GetOrCreateCurrentThreadData(void)
{
	struct PthreadPrivate* pThrData = STATIC_CAST2(struct PthreadPrivate*,TlsGetValue(gh_tlsPthreadDataKey));

	if(!pThrData){
		pthread_t currentThread = GetCurrentThread();
		pThrData = GetOrCreateDataForThread(currentThread);
		if(!pThrData){return pThrData;}
		TlsSetValue(gh_tlsPthreadDataKey, pThrData);
	}

	return pThrData;
}


HIDDEN_SYMBOL2 void SetParentThreadPointer(struct PthreadPrivate* a_pParent, struct PthreadPrivate* a_childThreadData)
{
	a_childThreadData->parentThreadPtr = a_pParent;
	if(a_pParent){
		for(uint64_t i=0;i<_NSIG;++i){
			if (!GET_SIGACTION_BIT(a_childThreadData->signalData.isSigactionCalled2,i) && 
				GET_SIGACTION_BIT(a_pParent->signalData.isSigactionCalled2,i)) {
				a_childThreadData->signalData.sigActions[i]= a_pParent->signalData.sigActions[i];
				SET_SIGACTION_BIT(a_childThreadData->signalData.isSigactionCalled2,i);
			}
		}
	}

}


END_C_DECL2
