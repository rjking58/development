// FloatingPointOutput.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdarg>
#include <strsafe.h>
void Myvsprintfx(char *format,va_list args)
{
	char output[100];

	size_t remaining;
	size_t sz = 100;
	StringCbVPrintfExA(output, sz, NULL, &remaining, STRSAFE_NULL_ON_FAILURE, format, args);

	std::cout << output << std::endl;
}

void Myvsprintf(char *format,...)
{
	va_list args;
	va_start(args,format);
	Myvsprintfx(format,args);
	va_end(args);
}

int _tmain(int argc, _TCHAR* argv[])
{
	double f = 3.14;
	Myvsprintf("%g",3.14);
	Myvsprintf("%.15g",f);
	return 0;
}

