/*********************************************************************
 * RPC for the Windows NT Operating System
 * 1993 by Martin F. Gergeleit
 *
 * RPC for the Windows NT Operating System COMES WITH ABSOLUTELY NO 
 * WARRANTY, NOR WILL I BE LIABLE FOR ANY DAMAGES INCURRED FROM THE 
 * USE OF. USE ENTIRELY AT YOUR OWN RISK!!!
 *********************************************************************/
#ifndef WLAC2_rpc__bcopy_h
#define WLAC2_rpc__bcopy_h

#include <rpc/wlac2_sunrpc_internal.h>
#include <stddef.h>

BEGIN_C_DECL2

void bcopy(const void *,void*,size_t);
//void bcopy_nf(char *,char *,int);
//void bcopy_fn(char *,char *,int);
//void bcopy_ff(char *,char *,int);
void bzero(void*,size_t);
int  bcmp(const void *, const void *, size_t);

END_C_DECL2

#endif  // #ifndef WLAC2_rpc__bcopy_h
