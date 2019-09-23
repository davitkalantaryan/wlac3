/*********************************************************************
 * RPC for the Windows NT Operating System
 * 1993 by Martin F. Gergeleit
 * Users may use, copy or modify Sun RPC for the Windows NT Operating 
 * System according to the Sun copyright below.
 *
 * RPC for the Windows NT Operating System COMES WITH ABSOLUTELY NO 
 * WARRANTY, NOR WILL I BE LIABLE FOR ANY DAMAGES INCURRED FROM THE 
 * USE OF. USE ENTIRELY AT YOUR OWN RISK!!!
 *********************************************************************/

/*
 *  bcopy.c --
 *      Implements bcopy(2) and bzero(2) byte operations.
 *
 *  Author:
 *      See-Mong Tan, 6/26/88
 */

#include <stdio.h>

/*
 *  bcopy(char *s1, char *s2, int len) --
 *      Copies len bytes from s1 to s2
 */
_declspec(dllexport) void
bcopy(s1, s2, len)
	const void *s1;
	void* s2;
	size_t len;
{
	const char* scr = (const char*)s1;
	char* dest = (char*)s2;
	for(; len > 0; len--)
		*dest++ = *scr++;
}

/*
 *  bzero(char *s, int len) --
 *      Places len zero byes in s
 */
void
bzero(s, len)
	void *s;
	size_t len;
{
	char* pcS = (char*)s;
	for(; len > 0; len--)
		*pcS++ = (char) 0;
}

/*
 *  bcmp() compares byte  string  b1  against  byte  string  b2, 
 *  returning  zero  if  they are identical, non-zero otherwise. 
 *  Both strings are assumed to be length bytes long.  bcmp() of 
 *  length zero bytes always returns zero.                       
*/
int
bcmp(sv1, sv2, len)
	const void *sv1, *sv2;
	size_t len;
{
	const char* s1 = (const char*)sv1;
	const char* s2 = (const char*)sv2;
	for(; len > 0; len--, s1++, s2++)
		if (*s1 != *s2)
			return 1;
	return 0;
}
	
