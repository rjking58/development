// ifbreaktest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

    for(int x = 0; x < 10; x++)
    {
        if(x == 5)
        {
            break;
        }

        std::cout << "x[" << x << "]" << std::endl;
    }
	return 0;
}

