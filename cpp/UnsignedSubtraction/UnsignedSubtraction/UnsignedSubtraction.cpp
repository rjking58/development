// UnsignedSubtraction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
    unsigned int x = 0xffffffff;

    for(unsigned int subtrahend = 1;
        subtrahend < 20;
        subtrahend++)
    {
        std::cout << std::hex << subtrahend 
                    << "-"
                    << std::hex << x << 
                    "="
                    << std::hex << subtrahend - x << std::endl;
    }

	return 0;
}

