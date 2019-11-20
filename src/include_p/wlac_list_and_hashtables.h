//  
// file:			src/include_p/wlac_list_and_hashtables.h  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  

#ifndef WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H
#define WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <stddef.h>
#include <.wlac_specific/redesigned/windows.h>

BEGIN_C_DECL2

enum LIST_ADD_RET {LIST_ADD_ADDED,LIST_ADD_ALREADY_EXIST,LIST_ADD_ERROR};

//#define ITERATE_OVER_LIST(_firstListItem, _iterateListItem)	\
//	for( int _iter=1, (_iterateListItem)=(_firstListItem); _iter||((_iterateListItem)!=(_firstListItem));_iter=0,(_iterateListItem) = (_iterateListItem)->next )

#define ITERATE_OVER_LIST(_firstListItem, _iterateListItem)	\
	for( (_iterateListItem)=(_firstListItem),(_firstListItem)=NEWNULLPTR2; ((_iterateListItem)!=(_firstListItem)); (_firstListItem)=(_firstListItem)?(_firstListItem):(_iterateListItem),(_iterateListItem)=(_iterateListItem)->next)

#define WLAC_GLOBAL_HASH_SIZE		4096

struct WlacListItem {
	struct WlacListItem *prev, *next;
};

struct HashByPointerItem {
	struct WlacListItem listItem;
	void* data;
	void* key;
};

struct HashByPointer {
	size_t						tableSize; // later on this will be power of 2
	struct WlacListItem**		table;
};

//extern HIDDEN_SYMBOL2 struct HashByPointer*				gh_pWlacGlobalHash;
//extern HIDDEN_SYMBOL2 HANDLE							gh_mutexForGlobalHash;

HIDDEN_SYMBOL3 void*				HashByPointer_GetValueByKey_GlobalHash(void* key);
HIDDEN_SYMBOL3 enum LIST_ADD_RET	HashByPointer_AddNew_GlobalHash(void* key, void* data, void** a_ppOldData);

#ifdef INTERNAL_SYMBOL_VISIBILITY
// list API
INTERNAL_SYMBOL_VISIBILITY void							WlacListItem_Construct(struct WlacListItem* ARGNONULL2 item);
INTERNAL_SYMBOL_VISIBILITY void							WlacListItem_AddAfter(struct WlacListItem* ARGNONULL2 oldItem, struct WlacListItem* ARGNONULL2 newItem);
INTERNAL_SYMBOL_VISIBILITY void							WlacListItem_AddBefore(struct WlacListItem* ARGNONULL2 oldItem, struct WlacListItem* ARGNONULL2 newItem);
INTERNAL_SYMBOL_VISIBILITY void							WlacListItem_RemoveEntry(struct WlacListItem* ARGNONULL2 item);

// hashtable API
INTERNAL_SYMBOL_VISIBILITY struct HashByPointer*		HashByPointer_CreateAndConstruct(size_t size);
INTERNAL_SYMBOL_VISIBILITY void							HashByPointer_DestructAndFree(struct HashByPointer* hash);
#ifdef _DEBUG
INTERNAL_SYMBOL_VISIBILITY size_t						HashByPointer_GetIndexByKey(struct HashByPointer* hash, void* key);
#endif
INTERNAL_SYMBOL_VISIBILITY enum LIST_ADD_RET			HashByPointer_AddNew2(struct HashByPointer* a_hash, void* a_key, void* a_data, void** a_ppOldData);
INTERNAL_SYMBOL_VISIBILITY int							HashByPointer_AddNew(struct HashByPointer* hash, void* key, void* data);
INTERNAL_SYMBOL_VISIBILITY struct HashByPointerItem*	HashByPointer_GetItemByKey(struct HashByPointer* hash, void* key, size_t* ARGNONULL2 a_pIntex);
INTERNAL_SYMBOL_VISIBILITY void*						HashByPointer_GetValueByKey(struct HashByPointer* hash, void* key);
INTERNAL_SYMBOL_VISIBILITY void							HashByPointer_RemoveEntry(struct HashByPointer* hash, void* key);

INTERNAL_SYMBOL_VISIBILITY struct HashByPointerItem*	HashByPointer_GetItemByKey_GlobalHash(void* key, size_t* ARGNONULL2 a_pIntex);
INTERNAL_SYMBOL_VISIBILITY void							HashByPointer_RemoveEntry_GlobalHash(void* key);

#endif  // #ifdef INTERNAL_SYMBOL_VISIBILITY


END_C_DECL2


#endif  // #ifndef WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H
