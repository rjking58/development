// TrackingReferenceTest.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::IO;

ref class X
{
public:
    String^ m_str;
};

ref class MyClss
{
public:

    static void SetupClss(X^% an_x)
    {
        an_x = gcnew X;
        an_x->m_str = "woof";
    }
};


int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");

    X ^an_x = nullptr;

    MyClss::SetupClss(an_x);

    Console::WriteLine(an_x->m_str);
    Console::ReadLine();

    return 0;
}
