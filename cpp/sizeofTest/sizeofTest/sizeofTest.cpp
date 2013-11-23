// sizeofTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>


void SizeOfArrayRef(char x [])
{
	// this prints the size of the pointer, not the array.. since 
	// by definition the passing of an array is nothing more than 
	// the passing of a pointer type.
	std::cout << "SizeOfArrayRef[" << sizeof(x) << "]" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char my43array[43];

	char * myarrayPtr= new char[55];

	// as expected, prints out 43..
	std::cout << "my43array[" << sizeof(my43array) << "]"  << std::endl;
	// as expected, prints out 4 (size of the pointer)
	std::cout << "myarrayPtr[" << sizeof(myarrayPtr) << "]"  << std::endl;
	SizeOfArrayRef(my43array);

	return 0;
}

