// PopulatingStructs.cpp : main project file.

#include "stdafx.h"

using namespace System;

using namespace PopulatingStructsCSharp;


int main(array<System::String ^> ^args)
{
    S1 l_s1;

    l_s1.pX = 1;
    l_s1.pY = 2;

    Console::WriteLine(l_s1.pX + " " + l_s1.pY);

    Console::WriteLine(L"Hello World");

    Console::ReadLine();

    return 0;
}
