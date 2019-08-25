//  
// file:			src/include_p/wlac_hashtables.c  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  

#include <wlac_list_and_hashtables.h>
#include <stdlib.h>
#include <malloc.h> // for clang this is not necessary

//#ifdef _WIN64
//#define BITS_TO_SHIFT	3
//#define REMN_MASK		0x7
//#else
//#define BITS_TO_SHIFT	3
//#define REMN_MASK		0x7
//#endif

// this is gold combination with minimum colission
#define BITS_TO_SHIFT	2
#define REMN_MASK		0x3

#define container_of_wlac(_ptr,_type,_member)	(_type*)(((char*)(_ptr))-offsetof(_type,_member))


HIDDEN_SYMBOL2 void WlacListItem_Construct(struct WlacListItem* ARGNONULL2 a_item)
{
	a_item->next = a_item->prev = a_item;
}


HIDDEN_SYMBOL2 void WlacListItem_AddAfter(struct WlacListItem* ARGNONULL2 a_oldItem, struct WlacListItem* ARGNONULL2 a_newItem)
{
	a_newItem->next = a_oldItem->next;
	a_oldItem->next->prev = a_newItem;

	a_oldItem->next = a_newItem;
	a_newItem->prev = a_oldItem;
}


HIDDEN_SYMBOL2 void WlacListItem_AddBefore(struct WlacListItem* ARGNONULL2 a_oldItem, struct WlacListItem* ARGNONULL2 a_newItem)
{
	a_newItem->prev = a_oldItem->prev;
	a_oldItem->prev->next = a_newItem;

	a_oldItem->prev = a_newItem;
	a_newItem->next = a_oldItem;
}


HIDDEN_SYMBOL2 void WlacListItem_RemoveEntry(struct WlacListItem* ARGNONULL2 a_item)
{
	a_item->next->prev = a_item->prev;
	a_item->prev->next = a_item->next;
}


//////////////////////////////////////////////////
#ifdef _DEBUG
HIDDEN_SYMBOL2 size_t HashByPointer_GetIndexByKey(struct HashByPointer* a_hash, void* a_key)
#else
static _inline size_t HashByPointer_GetIndexByKey(struct HashByPointer* a_hash, void* a_key)
#endif
{
	size_t	unKey = REINTERPRET_CAST2(size_t, a_key);
	size_t	unIndexCore = unKey >> BITS_TO_SHIFT;
	size_t	unIndexMasked = unKey & REMN_MASK;

	return (unIndexCore + unIndexMasked)% a_hash->tableSize;
}


HIDDEN_SYMBOL2 struct HashByPointer* HashByPointer_CreateAndConstruct(size_t a_size)
{
	struct HashByPointer* pReturn = STATIC_CAST2(struct HashByPointer*,malloc(sizeof(struct HashByPointer)));
	HANDLE_MEM_DEF(pReturn,"Unable to get memory for pointerHash");

	pReturn->table = STATIC_CAST2(struct WlacListItem**, calloc(a_size,sizeof(struct WlacListItem*)));
	HANDLE_MEM_DEF(pReturn->table, "Unable to get memory for pointerHash");

	pReturn->tableSize = a_size;

	return pReturn;
}


HIDDEN_SYMBOL2 void	HashByPointer_DestructAndFree(struct HashByPointer* a_hash)
{
	size_t i;
	struct WlacListItem* pItemNext;
	struct HashByPointerItem* pHashItem;

	for(i=0;i<a_hash->tableSize;++i){
		if(a_hash->table[i]){
			pItemNext = a_hash->table[i]->next;
			while(pItemNext != a_hash->table[i]){
				WlacListItem_RemoveEntry(a_hash->table[i]);
				pHashItem = container_of_wlac(a_hash->table[i],struct HashByPointerItem,listItem);
				free(pHashItem);
				a_hash->table[i] = pItemNext;
			}
			pHashItem = container_of_wlac(a_hash->table[i], struct HashByPointerItem, listItem);
			free(pHashItem);
		}
	}

	free(a_hash->table);
	free(a_hash);
}


HIDDEN_SYMBOL2 int HashByPointer_AddNew(struct HashByPointer* a_hash, void* a_key, void* a_data)
{
	size_t unIndex = HashByPointer_GetIndexByKey(a_hash, a_key);
	struct HashByPointerItem* pItemNew = STATIC_CAST2(struct HashByPointerItem*,malloc(sizeof(struct HashByPointerItem)));
	HANDLE_MEM_DEF(pItemNew, "Unable to get memory for HashByPointer_AddNew");

	pItemNew->key = a_key;
	pItemNew->data = a_data;

	if(UNLIKELY2(a_hash->table[unIndex])){
		WlacListItem_AddBefore(a_hash->table[unIndex], &pItemNew->listItem);
	}
	else{
		WlacListItem_Construct(&pItemNew->listItem);
		a_hash->table[unIndex] = &pItemNew->listItem;
	}

	return 0;
}


struct HashByPointerItem* HashByPointer_GetItemByKey(struct HashByPointer* a_hash, void* a_key, size_t* ARGNONULL2 a_pIntex)
{
	*a_pIntex = HashByPointer_GetIndexByKey(a_hash, a_key);

	if(LIKELY2(a_hash->table[*a_pIntex])){
		struct WlacListItem *pItem = a_hash->table[*a_pIntex] , *pItemFirst = a_hash->table[*a_pIntex];
		struct HashByPointerItem* pHashItem;

		do {
			pHashItem = container_of_wlac(pItem, struct HashByPointerItem, listItem);
			if (pHashItem->key == a_key) {
				return pHashItem;
			}
			pItem = pItem->next;
		} while (pItem != pItemFirst);
	}

	return NEWNULLPTR2;
}


HIDDEN_SYMBOL2 void* HashByPointer_GetValueByKey(struct HashByPointer* a_hash, void* a_key)
{
	size_t unIndex;
	struct HashByPointerItem* pHashItem = HashByPointer_GetItemByKey(a_hash,a_key,&unIndex);
	if(LIKELY2(pHashItem)){
		return pHashItem->data;
	}

	return NEWNULLPTR2;
}


HIDDEN_SYMBOL2 void HashByPointer_RemoveEntry(struct HashByPointer* a_hash, void* a_key)
{
	size_t unIndex;
	struct HashByPointerItem* pHashItem = HashByPointer_GetItemByKey(a_hash, a_key,&unIndex);
	if (LIKELY2(pHashItem)) {
		WlacListItem_RemoveEntry(&pHashItem->listItem);
		if(LIKELY2(pHashItem->listItem.next == pHashItem->listItem.prev)){
			a_hash->table[unIndex] = NEWNULLPTR2;
		}
	}
}
