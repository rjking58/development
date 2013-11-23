// ManagedCPPTest.cpp : main project file.

#include "stdafx.h"
#include <iostream>

using namespace System;


class MyReffedClass
{
public:
    void DoSomething()
    {
        //Console::WriteLine("woof");
        std::cout << "woof" << std::endl;
    }
};

class MyClass
{
public:
    MyClass( MyReffedClass &ref) : m_ref(ref)
    {

    }
    void DoSomething()
    {
        m_ref.DoSomething();
    }
private:
    MyReffedClass& m_ref;
};


int main(array<System::String ^> ^args)
{
    MyReffedClass mrc;
    MyClass mc(mrc);
    mc.DoSomething();

    Console::WriteLine(L"Hello World");
    Console::Read();
    return 0;
}
