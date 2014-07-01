// ComSafeArrayOfVariants.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
    SAFEARRAYBOUND sfb[1];
    sfb[0].lLbound = 0;
    sfb[0].cElements = 2;
    SAFEARRAY *m_pSafeArray = SafeArrayCreate(VT_VARIANT,1,sfb);


	return 0;
}

