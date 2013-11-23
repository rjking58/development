// ILeakMemory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

class X
{
    int     int_val;
    long    long_ary[100];

};

int _tmain(int argc, _TCHAR* argv[])
{

    for (int currtick = 0; currtick < 1000; currtick++)
    {
        X* pX = new X;

        ::Sleep(500);
    }

	return 0;
}

