// ConstructorInheritanceOrderTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class InitializerTestSuper
{
private:
	bool m_privVar;
public:
	InitializerTestSuper()
		: m_privVar(true)
	{
	}
	bool GetPrivVar()
	{
		return m_privVar;
	}
	void SetPrivVar(bool privVar)
	{
		m_privVar = privVar;
	}
};

class InitializerTestSub : public InitializerTestSuper
{
public:
	InitializerTestSub()
	{
		SetPrivVar(false);
	}

};


int _tmain(int argc, _TCHAR* argv[])
{
	InitializerTestSub sub1;
	std::cout << sub1.GetPrivVar() << std::endl;
	return 0;
}

