// WinDbgLearn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#if 0
#define SZ_MAX_LEN 10

WCHAR* pszCopy = NULL;

BOOL DupString(WCHAR* psz);

int _tmain(int argc, _TCHAR* argv[])
{
	int iRet = 0;

	if(argc = 2)
	{
		printf("Press any key to start \n");
		_getch();
		DupString(argv[1]);
	}
	else
	{
		iRet = 1;
	}

	return iRet;
}

BOOL DupString(WCHAR* psz)
{
	BOOL bRet = FALSE;

	if(psz != NULL)
	{
		pszCopy=(WCHAR*) HeapAlloc(GetProcessHeap(),
									0,
									SZ_MAX_LEN*sizeof(WCHAR));
		if(pszCopy)
		{
			wcscpy(pszCopy,psz);
			wprintf(L"Copy of string: %s", pszCopy);
			HeapFree(GetProcessHeap(), 0 ,pszCopy);
			bRet = TRUE;
		}
	}

	return bRet;
}
#endif
int _tmain(int argc, _TCHAR* argv[])
{
	char * ptr1 = new char[20];
	delete ptr1;
	delete ptr1;

	return 0;
}
