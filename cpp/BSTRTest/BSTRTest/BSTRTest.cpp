// BSTRTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <comutil.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	BSTR myStr = SysAllocString(L"woof woof");

	for(int x = 0; x < 30; x++)
	{
		_bstr_t my_bstrT;
		my_bstrT.Attach(myStr);
		//my_bstrT = myStr;

		std::cout << (char*) my_bstrT << std::endl;
	}
	*/

	_bstr_t first(L"woof woof");
	_bstr_t second;

	second = first;


	return 0;
}

