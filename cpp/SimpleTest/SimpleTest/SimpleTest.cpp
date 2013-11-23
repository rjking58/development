// SimpleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int f(int i, int j)
{
    int l = 0;
    l = i + j;

    return l;
}

int _tmain(int argc, _TCHAR* argv[])
{

    int result = f(1,2);

	return 0;
}

