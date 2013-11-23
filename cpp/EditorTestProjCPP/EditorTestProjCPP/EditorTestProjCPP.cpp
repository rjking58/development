// EditorTestProjCPP.cpp : Defines the entry point for the console application.
//


using namespace System;

#include "myY.h"

ref class X
{
public:
    void myFunc1()
    {
        myFunc2();
    }

    void myFunc2()
    {
        Console::WriteLine("woohoo calling y");
        int y = 11;
        m_y = new myY;
        m_y->doAnOutput(y);
        delete m_y;
    }

private:
    myY *m_y;
};

int main(int argc, char* argv[])
{
    X myX;

    myX.myFunc1();

	return 0;
}

