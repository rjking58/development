// streamstests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{


	for(unsigned int x = 0;
		x < 130;
		x++ )
	{
		std::cout << ">>" ;
		std::cout.width(4);
		std::cout.fill('0');
		std::cout << x << "<<" << std::endl;
	}



	return 0;
}

