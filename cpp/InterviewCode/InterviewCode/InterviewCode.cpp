// InterviewCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class X
{
private:
    int m_result;
public:
    X(int a) : m_result(a)
    {
        
    }
    void action(int a, int b)
    {
        m_result += a+b;
    }
    int getResult()
    {
        return m_result;
    }
};

X someMethod(X p_x)
{
    p_x.action(1,2);
    return p_x;
}

int _tmain(int argc, _TCHAR* argv[])
{

    X some_x(5);
    std::cout << some_x.getResult () << std::endl;

    X result_x = someMethod(some_x);

    std::cout << result_x.getResult () << std::endl;

	return 0;
}

