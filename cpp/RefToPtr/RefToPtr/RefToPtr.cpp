// RefToPtr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

class myclass
{
	int m_i;
public:
	myclass()	:	m_i(10)
	{
	}
	int get_i()
	{
		return m_i;
	}
};

// test of reference to pointer..
void make_myclass(myclass * &p_mc)
{
	p_mc = new myclass;
}

int _tmain(int argc, _TCHAR* argv[])
{
	myclass *	p_mc = 0;

	make_myclass(p_mc);
	if(p_mc)
	{
		std::cout << "p_mc->get_i()[" << p_mc->get_i() << "]" << std::endl;
	}
	else
	{
		std::cout << "p_mc not properly initialized" << std::endl;
	}


	return 0;
}

