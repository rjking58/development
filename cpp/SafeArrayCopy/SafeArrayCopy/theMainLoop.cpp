// SafeArrayCopy.cpp : Defines the entry point for the console application.
//
#define _ATL_APARTMENT_THREADED


#include "stdafx.h"

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

    SAFEARRAY * psa;
    SAFEARRAY * psa2;

    SAFEARRAYBOUND rgsabound[1];
    rgsabound[0].lLbound = 0;
    rgsabound[0].cElements = 4;
    psa = SafeArrayCreate(VT_INT, 1, rgsabound);

    SafeArrayLock(psa);
    int dims = SafeArrayGetElemsize(psa);
    std::cout << "dims[" << dims << "]" << std::endl;


	SafeArrayCopy(psa, &psa2);

    std::cout << "psa[" << (unsigned long) psa << "] psa2[" << (unsigned long) psa2 << "]" << std::endl;


	return 0;
}

