// StaticInFuncTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int GetStaticThingee()
{
	static int i = 0;
	if(i == 0)
	{
		i++;
	}
	return i;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << GetStaticThingee() << std::endl;
	std::cout << GetStaticThingee() << std::endl;
	std::cout << GetStaticThingee() << std::endl;

	return 0;
}

