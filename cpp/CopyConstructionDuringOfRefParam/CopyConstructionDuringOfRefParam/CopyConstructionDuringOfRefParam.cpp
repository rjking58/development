// CopyConstructionDuringOfRefParam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class X
{
    int m_myint;
public:
    X()
    {}
    X( X &ref)  
    {
        std::cout << "copy constructor called on X" << std::endl;
    }
};

class ContainsX
{
    X m_x;

public:
    ContainsX(X &x) : m_x(x)  // no copy on initial call, but copy during assignment to member var.
    {}
};


int _tmain(int argc, _TCHAR* argv[])
{
    X x;
    ContainsX *cx;

    std::cout << "newing up ContainsX" << std::endl;
    cx = new ContainsX(x);

    std::cout << "declaring ContainsX on function stack" << std::endl;
    ContainsX cx2(x);


	return 0;
}

