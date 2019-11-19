//  
// file:			src/include_p/wlac_internal_private.h  
// created on:		2019 Aug 24  
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)  
//  

#ifndef WLAC_SRC_INCLUDE_P_WLAC_INTERNAL_PRIVATE_H
#define WLAC_SRC_INCLUDE_P_WLAC_INTERNAL_PRIVATE_H

#include <.wlac_specific/first_includes/wlac2_common_internal.h>
#include <stddef.h>
#include <.wlac_specific/redesigned/signal.h>

#define MAX_SEMAPHORE_COUNT	1024

#ifdef snprintf
#define snprintfs_defined
#pragma push_macro (snprintf)
#undef snprintf
#endif
#define PREPARE_STRING_PRIVATE(_string_,_str_len_,_key_,_size_,_flag_) \
	(snprintf((_string_), (_str_len_), "01234567898765432____key=%d__size=%d__flag=%d", \
		(int)(_key_), (int)(_size_), (int)(_flag_)))

#define	IPC_STRING_DEF_LEN	127
#define PREPARE_STRING(_string_,_key_,_size_,_flag_) \
	PREPARE_STRING_PRIVATE(_string_,IPC_STRING_DEF_LEN,_key_,_size_,_flag_)

#ifdef snprintfs_defined
#undef snprintfs_defined
#pragma pop_macro (snprintf)
#endif

BEGIN_C_DECL2

extern HIDDEN_SYMBOL3 int		gh_nErrorsAccured;
extern HIDDEN_SYMBOL3 DWORD		gh_tlsPthreadDataKey;
extern HIDDEN_SYMBOL3 char		gh_path[];

// list API
//HIDDEN_SYMBOL2 void							WlacListItem_Construct(struct WlacListItem* ARGNONULL2 item);
HIDDEN_SYMBOL3 int IsDescriptorASocket(int a_d);


END_C_DECL2


#endif  // #ifndef WLAC_SRC_INCLUDE_P_WLAC_INTERNAL_PRIVATE_H
