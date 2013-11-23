// breakMechanics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    int i = 0;
    while(i < 10)
    {
        std::cout << i << std::endl;
        if(i == 5)
        {
            break;
        }
        i++;
    }
	return 0;
}

