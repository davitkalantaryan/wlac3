
#pragma comment (lib, "wlac2.lib")

#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <Windows.h>

int main()
{
	//pthread_t myThread;
	HMODULE hModule = LoadLibraryA("wlac2.5.0.0.dll");

	//ftok("C:\\test.txt", 1);

	Sleep(10000);

	if(hModule){
		FreeLibrary(hModule);
	}

	return 0;
}
