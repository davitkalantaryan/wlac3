

#include <.wlac_specific/rfc2/wlac2_rfc2.h>
#include <iostream>
#include <stdlib.h>

int main(int a_argc, char* a_argv[])
{
	if(a_argc<2){
		::std::cerr << "Number of arguments must be more than 1" << ::std::endl;
		return 1;
	}

	void* pRetrn;
	int nPid = atoi(a_argv[1]);
	int nCall = CallFunctionOnRemoteProcessByPid(nPid, "librfc2_trojan_test", "PrintfSomething", nullptr, 0, &pRetrn);

	::std::cout << "nReturn=" << nCall << ", pRemoteRet=" << pRetrn << ::std::endl;

	return 0;
}
