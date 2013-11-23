// AutoLinkDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include "AutoLinkDLL.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif


void Testcall()
{
	std::cout << "hi!" << std::endl;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

