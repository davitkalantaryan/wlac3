
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>


int main()
{
	DWORD dwPid = GetCurrentProcessId();

	::std::cout << "pid=" << dwPid << ::std::endl;

	while (1) {
		SleepEx(INFINITE, TRUE);
	}

	return 0;
}
