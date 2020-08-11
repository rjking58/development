// StdString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <string.h>

void doOut (const char *str)
{

	std::cout << str << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	for(double x = 0; x < 10; x += 0.1)
	{
		std::ostringstream myInt;

		myInt << x;

		doOut(myInt.str().c_str());
	}

    // test wstring compares..

    std::wstring wideone = L"wideString";
    std::wstring wideone2 = L"widestring";

    if(wcscmp(wideone.c_str(),wideone2.c_str()) == 0)
    {
        std::cout << "they shouldn't match but they do" << std::endl;
    }
    else
    {
        std::cout << "they don't match" << std::endl;
    }

    std::wstring widex = wideone.substr(0,5);
    std::wstring widex2 = wideone2.substr(0,5);

    if(wcscmp(widex.c_str(),widex2.c_str()) == 0)
    {
        std::cout << "they shouldn't match but they do" << std::endl;
    }
    else
    {
        std::cout << "they don't match" << std::endl;
    }

    if(_wcsicmp(widex.c_str(),widex2.c_str()) == 0)
    {
        std::cout << "they match!" << std::endl;
    }
    else
    {
        std::cout << "they don't match" << std::endl;
    }

	return 0;
}

