/*
 *	File: gem_ipc_source.cpp
 *
 *	Created on: Dec 23, 2015
 *	Author    : Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements all functions connected to posix threading
 *		1) 
 *
 *
 */

#include <wlac_internal_private.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <.wlac_specific/redesigned/sys/types.h>
#include <.wlac_specific/redesigned/windows.h>
#include <malloc.h>
#include <stdio.h>

BEGIN_C_DECL2

#define		PLACE_FOR_MEM_SIZE	8

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmat_needed)
WLAC_EXPORT segment_t shmget(key_t a_key, size_t a_size, int a_shmflg)
{
	HANDLE hShared;
	char* pcShMemName = (char*)_alloca(IPC_STRING_DEF_LEN+1);

	PREPARE_STRING(pcShMemName,a_key, a_size, a_shmflg);
	
	hShared = OpenFileMappingA((DWORD)a_shmflg, TRUE, pcShMemName);
	if (hShared == NEWNULLPTR2)return (segment_t)-1;
	return (segment_t)hShared;
}
#endif


#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmat_needed)
WLAC_EXPORT void *shmat(segment_t a_shmid, const void *shmaddr, int shmflg)
{
	size_t unSize;
	char* pcRet = (char*)MapViewOfFile((HANDLE)a_shmid, shmflg,
		0,
		0,
		PLACE_FOR_MEM_SIZE);
	if (!pcRet) return (void*)-1;

	memcpy(&unSize, pcRet + 4, sizeof(size_t) < PLACE_FOR_MEM_SIZE ? sizeof(size_t) : PLACE_FOR_MEM_SIZE);
	UnmapViewOfFile((HANDLE)a_shmid);
	a_shmid = 0;
	if (!unSize)return (void*)-1;

	pcRet = (char*)MapViewOfFile((HANDLE)a_shmid, shmflg,
		0,
		0,
		unSize + PLACE_FOR_MEM_SIZE);
	if (!pcRet) return (void*)-1;

	return pcRet;
}
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmdt_needed)
WLAC_EXPORT int shmdt(const void *shmaddr)
{
	if (!UnmapViewOfFile(shmaddr)) return -1;
	return 0;
}
#endif

#if !defined(IGNORE_ALL_WLAC_SYMBOLS) || defined(shmctl_needed)
WLAC_EXPORT int shmctl(segment_t a_shmid, int a_cmd, struct shmid_ds *a_buf)
{
	switch (a_cmd)
	{
	case IPC_RMID:
		CloseHandle((HANDLE)a_shmid);
		break;
	default:
		break;
	}
	return 0;
}
#endif


#if 0


#endif  //  #if 0

END_C_DECL2
