// TestPragmas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#pragma warning(push)
#pragma warning(disable : 4189)
int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{
    {
        bool a = true;

        bool b = true;
    }
	return 0;
}
#pragma warning(pop)

int test2()
{
    bool c = true;
}

