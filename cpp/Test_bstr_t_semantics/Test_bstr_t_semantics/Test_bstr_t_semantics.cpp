// Test_bstr_t_semantics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <comdef.h>


int _tmain(int argc, _TCHAR* argv[])
{
    BSTR x = SysAllocString(L"woof woof");

    _bstr_t myBstr(x);  // ends up making a copy (different pointer values)


    _bstr_t myBstr2(myBstr);    // same pointer value.. but ref count is + 1.

    BSTR y = myBstr2.GetBSTR(); // returns the SAME pointer value as what is inside.. so its direct access to the pointer..

	return 0;
}

