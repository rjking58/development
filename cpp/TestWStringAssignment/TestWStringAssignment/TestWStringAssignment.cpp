// TestWStringAssignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <vcclr.h>
#include <comdef.h>

using namespace System;
using namespace System::Threading;

int _tmain(int argc, _TCHAR* argv[])
{

    String ^mystr = "1234";

    std::wstring os;
    std::wstring tempPlace;
    Console::WriteLine("before loop");

    Thread::Sleep(30000);
    Console::WriteLine("starting loop");

    for(int x = 0; x < 10000000; x++)
    {
        if((x % 100000) == 0)
        {
            Console::Write(".");
        }
        using namespace Runtime::InteropServices;
        const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(mystr)).ToPointer();
        os = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));

        pin_ptr<const wchar_t> pp_Var = PtrToStringChars(mystr);

        tempPlace = pp_Var;

        SysAllocString(L"woof");

    }

    Console::WriteLine("measure me");

    Thread::Sleep(180000);

    return 0;
}

