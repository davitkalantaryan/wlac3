//  
// file:			src/include_p/wlac_threading_private.h  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  

#ifndef WLAC_SRC_INCLUDE_P_WLAC_THREADING_PRIVATE_H
#define WLAC_SRC_INCLUDE_P_WLAC_THREADING_PRIVATE_H

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include "wlac_list_and_hashtables.h"
#include <stddef.h>
#include <.wlac_specific/redesigned/signal.h>
#include <pthread.h>
#include <stdint.h>

#define GET_SIGACTION_BIT(_isSigactionCalled2,_bitNum)	\
	(  (_isSigactionCalled2)[(_bitNum)/8] & (1i64<<((_bitNum)%8)) )

#define SET_SIGACTION_BIT(_isSigactionCalled2,_bitNum)	\
	do{ (_isSigactionCalled2)[(_bitNum)/8] |= (1i64<<((_bitNum)%8)); }while(0)

#define CLEAR_SIGACTION_BIT(_isSigactionCalled2,_bitNum)	\
	do{ (_isSigactionCalled2)[(_bitNum)/8] &= (~(1i64<<((_bitNum)%8))); }while(0)

BEGIN_C_DECL2

struct PSignalData {
	struct sigaction			sigActions[_NSIG];
	uint64_t					isSigactionCalled2[1 + _NSIG/sizeof(uint64_t)/8];
};

struct PthreadPrivate {
	pthread_t					threadHandle;
	struct WlacListItem*		listItem;
	struct PthreadPrivate*		parentThreadPtr;
	char*						threadName;
	struct PSignalData			signalData;
};

extern HIDDEN_SYMBOL3 struct PSignalData			gh_globalSignalData;
//extern HIDDEN_SYMBOL2 struct WlacListItem*			gh_allThreads;


// list API
//HIDDEN_SYMBOL2 void							WlacListItem_Construct(struct WlacListItem* ARGNONULL2 item);
//HIDDEN_SYMBOL2 struct PthreadPrivate*	CreateThreadData(struct PthreadPrivate* pParent, pthread_t threadHandle);
HIDDEN_SYMBOL3 struct PthreadPrivate*	GetOrCreateCurrentThreadData(void);
//HIDDEN_SYMBOL2 struct PthreadPrivate*	GetorCreateDataForThread(pthread_t thread);
//HIDDEN_SYMBOL2 void						SetParentThreadPointer(struct PthreadPrivate* pParent, struct PthreadPrivate* childThreadData);


END_C_DECL2


#endif  // #ifndef WLAC_SRC_INCLUDE_P_WLAC_THREADING_PRIVATE_H
