// sharedPtr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>


std::shared_ptr<int> getAnInt()
{
    std::shared_ptr<int> myInt(new int);

    *myInt = 11;

    std::cout << "PointerVal[" << myInt.get() << "]" << " value[" << *myInt << "]" << std::endl;

    return myInt;
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::shared_ptr<int> myInt;

    myInt = getAnInt();

    std::cout << "PointerVal[" << myInt.get() << "]" << " value[" << *myInt << "]" << std::endl;

	return 0;
}

