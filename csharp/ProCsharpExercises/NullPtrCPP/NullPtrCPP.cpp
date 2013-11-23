// NullPtrCPP.cpp : main project file.

#include "stdafx.h"

using namespace System;

ref class MyClss
{
private:
    int m_simple;

public:
    MyClss() : m_simple(10)
    {
    }

    property int Simple
    {
        int get()
        {
            return m_simple;
        }
    }
};

int main(array<System::String ^> ^args)
{
    MyClss^ pMyClss = nullptr;

    if(pMyClss == nullptr)
    {
        Console::WriteLine("its a null");
    }

    pMyClss = gcnew MyClss();

    if(pMyClss == nullptr)
    {
        Console::WriteLine("its a null");
    }
    else
    {
        Console::WriteLine(pMyClss->Simple);
    }
    
    Console::ReadLine();

    return 0;
}
