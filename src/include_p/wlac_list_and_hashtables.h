//  
// file:			src/include_p/wlac_list_and_hashtables.h  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  

#ifndef WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H
#define WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <stddef.h>

BEGIN_C_DECL2

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

// list API
HIDDEN_SYMBOL2 void							WlacListItem_Construct(struct WlacListItem* ARGNONULL2 item);
HIDDEN_SYMBOL2 void							WlacListItem_AddAfter(struct WlacListItem* ARGNONULL2 oldItem, struct WlacListItem* ARGNONULL2 newItem);
HIDDEN_SYMBOL2 void							WlacListItem_AddBefore(struct WlacListItem* ARGNONULL2 oldItem, struct WlacListItem* ARGNONULL2 newItem);
HIDDEN_SYMBOL2 void							WlacListItem_RemoveEntry(struct WlacListItem* ARGNONULL2 item);

// hashtable API
HIDDEN_SYMBOL2 struct HashByPointer*		HashByPointer_CreateAndConstruct(size_t size);
HIDDEN_SYMBOL2 void							HashByPointer_DestructAndFree(struct HashByPointer* hash);
#ifdef _DEBUG
HIDDEN_SYMBOL2 size_t						HashByPointer_GetIndexByKey(struct HashByPointer* hash, void* key);
#endif	
HIDDEN_SYMBOL2 int							HashByPointer_AddNew(struct HashByPointer* hash, void* key, void* data);
HIDDEN_SYMBOL2 struct HashByPointerItem*	HashByPointer_GetItemByKey(struct HashByPointer* hash, void* key, size_t* ARGNONULL2 a_pIntex);
HIDDEN_SYMBOL2 void*						HashByPointer_GetValueByKey(struct HashByPointer* hash, void* key);
HIDDEN_SYMBOL2 void							HashByPointer_RemoveEntry(struct HashByPointer* hash, void* key);


END_C_DECL2


#endif  // #ifndef WLAC_SRC_INCLUDE_P_LIST_AND_HASHTABLES_H
