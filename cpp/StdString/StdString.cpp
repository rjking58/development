// StdString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>

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

	return 0;
}

