// UsingUnmanagedInRefClasses.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace System;

class MyClass
{
public:
    MyClass()   :   m_str("std::string initialized properly"),
                    m_int(44)
    {
    }
    std::string m_str;
    int         m_int;
};

ref class MyRefClass
{
public:
    MyRefClass()
    {
        m_myclss = new MyClass;
    }
    ~MyRefClass()
    {
        delete m_myclss;
    }
    void TestOutput()
    {
        std::cout << "str[" << m_myclss->m_str.c_str() << "]" << std::endl;
        Console::WriteLine("int[{0}]",m_myclss->m_int);
    }
private:

    MyClass     *m_myclss;
};




int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");

    MyRefClass  mrc;
    
    mrc.TestOutput();

    Console::ReadLine();

    return 0;
}
