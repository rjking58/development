// StreamInserters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <iomanip>

int _tmain(int argc, _TCHAR* argv[])
{
    std::ostringstream oss;

    oss     << std::hex  
            << std::setfill('0') << std::setw(2) << 10 << " " 
            << std::setfill('0') << std::setw(2) << 3 << " " 
            << std::setfill('0') << std::setw(2)  << 4 << " "
            << std::setfill('0') << std::setw(2)  << 11 << " "
            << std::endl;

    std::cout << oss.str().c_str();
	return 0;
}

