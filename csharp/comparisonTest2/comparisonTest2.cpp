// comparisonTest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	int a = 11;
	int b = 11;
	int c = 11;
	int d = 11;

	if((a == b) && (a == c) && (a == d))
	{
		std::cout << " all equal" << std::endl;
	}
	else
	{
		std::cout << " NOT equal!" << std::endl;
	}
	return 0;
}

