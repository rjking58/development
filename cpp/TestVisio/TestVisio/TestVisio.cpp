// TestVisio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


enum zippy
{
	z1 = 1,
	z2,
	z3
};

class x2
{
	void method4() { }
};

class i1a 
{
	public:
		virtual void method1() = 0;
		virtual int method2() = 0;
		virtual bool method3(zippy e) = 0;
};
class i1b 
{
	public:
		virtual void method9() = 0;
};

class x1 : public i1a,i1b
{
private:
	x2	*m_x2;
public:
	x1()
	{
		m_x2 = new x2;
	}

	void method1() { }
	int method2() { return 1; }
	bool method3(zippy e) { return true; }
	void method9() { }
	x2 * method10() { return 0; }

};



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

