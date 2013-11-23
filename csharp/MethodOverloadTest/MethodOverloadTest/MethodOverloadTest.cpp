// MethodOverloadTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

enum E1
{
	E1_VAL1,
	E1_VAL2
};
enum E2
{
	E2_VAL1,
	E2_VAL2
};

class myclass
{
public:
	int DoSomething(E1 val)
	{
		return 0;
	}
	int DoSomething(E2 val)
	{
		return 1;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{

	myclass mc;

	std::cout << mc.DoSomething(E1_VAL1) << std::endl;
	std::cout << mc.DoSomething(E2_VAL2) << std::endl;

	return 0;
}

