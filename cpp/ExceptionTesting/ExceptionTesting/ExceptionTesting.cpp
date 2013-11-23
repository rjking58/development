// ExceptionTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>


class makesIntExceptionOnDeconstruct
{
public:
    ~makesIntExceptionOnDeconstruct()
    {
        throw 10;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{

    makesIntExceptionOnDeconstruct *maker = new makesIntExceptionOnDeconstruct;

    try
    {
        delete maker;
    }
    catch(int val)
    {
        std::cout << "found exception int value[" << val << "]" << std::endl;
    }

	return 0;
}

