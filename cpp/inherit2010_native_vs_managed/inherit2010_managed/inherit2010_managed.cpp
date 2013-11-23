// inherit2010_managed.cpp : main project file.

#include "stdafx.h"

using namespace System;

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

ref class  B1
{
	public:
	B1()
	{
		std::cout << "constructor for B1" << std::endl;
	}
	virtual ~B1() 	// the virtual mustd::st be here to work correctly
						// if this is removed then the compiler generates its own 
						// destructors and bypasses all destructors in the heirarchy.
	{
		std::cout << "destructor for B1" << std::endl;
	}
	virtual void woof_woof() 
    {
		std::cout << "B1 says: arf arf" << std::endl;
    }
};

ref class D1 : public B1
{
	public:
	D1()
	{
		std::cout << "constructor for D1" << std::endl;
	}
	~D1()
	{
		std::cout << "destructor for D1" << std::endl;
	}
	virtual void woof_woof() override;

};

void D1::woof_woof() 
{
	std::cout << " D1 says: woof woof " << std::endl;
}


ref class D2 : public D1
{
	public:
	D2()
	{
		std::cout << "constructor for D2" << std::endl;
	}
	~D2()
	{
		std::cout << "destructor for D2" << std::endl;
	}
	virtual void woof_woof() override;
};

void D2::woof_woof()
{
	std::cout << " D2 says: woof woof " << std::endl;
}


int main(array<System::String ^> ^args)
{
  	B1 ^a_B1_p;
	B1 ^a_B1_p2;

	a_B1_p = gcnew D1;
	a_B1_p2 = gcnew D2;

	a_B1_p->woof_woof();
	a_B1_p2->woof_woof();


    return 0;
}
