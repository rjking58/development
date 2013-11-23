// BadException.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class myClass
{
public:
    int x;
};

int _tmain(int argc, _TCHAR* argv[])
{
    myClass *p_mc = NULL;

    int y = p_mc->x;

	return 0;
}

