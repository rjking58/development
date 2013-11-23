// PointerX2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>
#include <stdio.h>

struct theStruc
{
    long x;
    long y;
};

void PrtX(theStruc **struc)
{
    printf("%X\n",(*struc)[0].x);
    printf("%X\n",(*struc)[1].x);
    printf("%X\n",(*struc)[2].x);

}

int _tmain(int argc, _TCHAR* argv[])
{
    theStruc *pTS = new theStruc[3];

    memset(pTS,0,sizeof(theStruc)*3);

    PrtX(&pTS);

	return 0;
}

