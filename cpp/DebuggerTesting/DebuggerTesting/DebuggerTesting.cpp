// DebuggerTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Y
{
    int m_z;
public:
    void doSomething(int i)
    {
        m_z = i + 20;
        std::cout << m_z;
    }
};

class X 
{
private:
    Y m_y;
    int m_q;
public:
    void doSomething(int i)
    {
        m_q = i + 10;
        m_y.doSomething(i);
    }


};

int _tmain(int argc, _TCHAR* argv[])
{
    X x;

    x.doSomething(44);
    x.doSomething(66);
	return 0;
}

