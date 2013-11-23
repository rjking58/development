// simpleExceptionTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>

void lockity(bool isStop)
{
    if(isStop)
    {
        std::cout << "stop" << std::endl;
    }
    else
    {
        std::cout << "start" << std::endl;
    }

}
void throwit(int x)
{
    if(x != 3)
    {
        throw (1);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    for(int x =0;
        x < 10;
        x++)
    {
        try
        {
            lockity(false);
            throwit(x);
            lockity(true);
        }
        catch (...)
        {
            std::cout << "failed for x[" << x << "]" << std::endl;
            lockity(true);
        }

    }
}

