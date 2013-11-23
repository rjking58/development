// arrayTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <iomanip>
#include <memory>
#include <vector>

void passAry(int *anAry);

int _tmain(int argc, _TCHAR* argv[])
{

	int myArray[10];

    std::cout << "sizeof(myArray[10]) = " << sizeof(myArray) << std::endl;
	for(int x = 0; x < 10; x++)
	{
		myArray[x] = x+10;
	}
	passAry(myArray);
	return 0;
}

// a reminder, since its been SO long.. :)
void passAry(int *anAry)
{
	int sz = sizeof(anAry);

	std::cout << sizeof(anAry) << std::endl;

	for(int x = 0; x < sz; x++)
	{
		std::cout << anAry[x] << " ";
	}
	std::cout << std::endl;
}

