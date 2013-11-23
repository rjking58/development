// VS2012UnitTestTesting.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"
#include "VS2012UnitTestTesting.h"

ClassUnderTest::ClassUnderTest()
    :   m_i(0)
{
}
ClassUnderTest::ClassUnderTest(int i)
    :   m_i(i)
{
}

void ClassUnderTest::SetI(int i)
{
    m_i = i;
}

int ClassUnderTest::GetI()
{
    return m_i;
}
