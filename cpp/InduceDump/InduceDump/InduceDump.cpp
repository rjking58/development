// InduceDump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


class myclass
{
public:
	int x;
};
int _tmain(int argc, _TCHAR* argv[])
{
	myclass *instance_myclass = NULL;

	// **boom**
	int y = instance_myclass->x;
	std::cout << "test val y[" << y << "]" << std::endl;
	// std::cout << "test" << std::endl;
	return 0;
}

