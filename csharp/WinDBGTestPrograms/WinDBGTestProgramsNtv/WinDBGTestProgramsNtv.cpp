// WinDBGTestProgramsNtv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

class MethodWithLocals
{
private:
    int m_x;
    std::string m_z;
public:
    void method1()
    {
        int method1_int1 = 10;

        method2(method1_int1);
    }

    void method2(int int1)
    {
        int method2_int1 = 11;
        int method2_int2 = int1 + method2_int1;
            
        m_x = 44;
        m_z = "woof";

        int i;
        std::cin >> i; 
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    int i;
    //i = Console.Read();
    MethodWithLocals *mwl = new MethodWithLocals;
    mwl->method1();
	return 0;
}

