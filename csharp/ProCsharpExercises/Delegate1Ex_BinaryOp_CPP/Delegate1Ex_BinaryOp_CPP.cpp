// Delegate1Ex_BinaryOp_CPP.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::Text;

ref class Program
{
public:
	Program()
	{
	}
    void DoProggy()
    {
        callBack = gcnew Program::BinaryOp(this,&Program::Add);
        callBack += gcnew Program::BinaryOp(this,&Program::Sub);

		array<Delegate^>^ invokeList = callBack->GetInvocationList();
		for(int currDelegate = 0; 
			currDelegate < invokeList->Length;
			currDelegate++)
		{
            Console::WriteLine("Method Name[" + invokeList[currDelegate]->Method + "]");
            Console::WriteLine("Type Name[" + invokeList[currDelegate]->Target + "]");

		}
        // do the responsible thing :)
        if(callBack != nullptr)
        {
            callBack->Invoke(4, 5);
        }
    }
private:
    delegate void BinaryOp(int x, int y);

    BinaryOp^ callBack;
    void Add(int first, int second)
    {
        Console::WriteLine(first + second);
    }

    void Sub(int first, int second)
    {
        Console::WriteLine(first - second);
    }
};



int main(array<System::String ^> ^args)
{
    Program^ p = gcnew Program();
    p->DoProggy();

	Console::ReadLine();
    return 0;
}



