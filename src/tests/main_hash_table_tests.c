

#include <stddef.h>
#include <stdio.h>
#include <wlac_list_and_hashtables.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <memory.h>
#include <conio.h>

#define HASH_SIZE_TO_CHECK				8192
#define NUMBER_HANDLES_TO_CHECK			4096

static DWORD WINAPI ThreadFunctionStat(void* lpThreadParameter);

int main()
{
	struct HashByPointer* pHash = HashByPointer_CreateAndConstruct(HASH_SIZE_TO_CHECK);

	HANDLE vcHandles[NUMBER_HANDLES_TO_CHECK];
	size_t unIndex;
	char vcFlags[HASH_SIZE_TO_CHECK];
	size_t i;
	int nColisions;

	memset(vcFlags, 0, HASH_SIZE_TO_CHECK);

	for(nColisions=0,i=0;i< NUMBER_HANDLES_TO_CHECK;++i){
		vcHandles[i] = CreateThread(NEWNULLPTR2, 0, &ThreadFunctionStat, NEWNULLPTR2, 0, NEWNULLPTR2);
		unIndex = HashByPointer_GetIndexByKey(pHash, vcHandles[i]);
		// there is no need for unIndex%NUMBER_TO_CHECK
		if(vcFlags[unIndex]){
			printf("Colision for index %d\n", (int)unIndex);
			++nColisions;
		}
		else {
			vcFlags[unIndex] = 1;
		}
	}


	for (i = 0; i < NUMBER_HANDLES_TO_CHECK; ++i) {

		if(vcHandles[i]){
			WaitForSingleObject(vcHandles[i], INFINITE);
			CloseHandle(vcHandles[i]);
		}
	}

	printf("NumberOfCollisions=%d\n", nColisions);
	printf("Press any key to exit!"); fflush(stdout);

	_getch();
	printf("\n");

	return 0;
}

static DWORD WINAPI ThreadFunctionStat(void* lpThreadParameter)
{
	return 0;
}
