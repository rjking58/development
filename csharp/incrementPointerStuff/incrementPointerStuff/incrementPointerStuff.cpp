// incrementPointerStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
    __int8 *c_ptr = new __int8[200];
    __int8 *c_ptr2 = c_ptr;
    c_ptr[0] = 0;
    c_ptr[1] = 1;
    c_ptr[2] = 2;

    *c_ptr++ = 9;    
    *c_ptr++ = 10;
    *c_ptr++ = 11;
    
    // for some reason delete has an issue with __int8
    //delete [] c_ptr;

	return 0;
}

