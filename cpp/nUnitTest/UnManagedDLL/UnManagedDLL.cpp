// UnManagedDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include "UnManagedDLL.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

TestClass::TestClass() : m_val (0)
{
}


void TestClass::SetVal(int p_val)
{
	m_val = p_val;
}

int TestClass::GetVal()
{
	return m_val;
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

