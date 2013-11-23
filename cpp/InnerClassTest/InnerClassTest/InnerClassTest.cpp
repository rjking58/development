// InnerClassTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class OuterCls 
{
private:

    bool m_bSetting1;

    class InnerCls
    {
    public:
        void TestAccess(OuterCls &outer)
        {
            std::cout << "TestAccess:: m_bSetting1[" << outer.m_bSetting1 << "]" << std::endl;
            outer.PrivateMethod ();

        }
    };

    void PrivateMethod()
    {
        std::cout << "PrivateMethod:: m_bSetting1[" << m_bSetting1 << "]" << std::endl;
    }
public:
    void TestInner()
    {
        InnerCls inner;

        m_bSetting1 = false;
        inner.TestAccess (*this);

        m_bSetting1 = true;
        inner.TestAccess (*this);
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    OuterCls outer;

    outer.TestInner ();

	return 0;
}

