// WinDbgBasicTraining.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class contained
{
public:
	contained(int x)	:	m_x(x)
	{}
	void incrementX()
	{
		m_x++;
	}
private:
	int	m_x;
};

class container
{
public:
	container()	:	m_c(1),
					m_pc(new contained(2))
	{}
	void incrementByValue()
	{
		m_c.incrementX();
	}
	void incrementByPtr()
	{
		m_pc->incrementX();
	}
private:
	contained m_c;
	contained *m_pc;
};


int _tmain(int argc, _TCHAR* argv[])
{

	container c;

	int x = 2;

	return 0;
}

