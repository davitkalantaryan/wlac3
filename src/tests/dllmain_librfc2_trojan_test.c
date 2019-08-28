
#include <stdio.h>

_declspec(dllexport)  void* PrintfSomething(void* a_ptr, int a_val)
{
	printf("Helo world arg1=%p, arg2=%d\n", a_ptr, a_val);
	return a_ptr;
}
