// EncodingUsageCPP.cpp : main project file.

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace System;

void MarshalString ( String ^ s, std::wstring& os ) 
{
   using namespace Runtime::InteropServices;
   const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}


int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");

    //String mystr = "1234";

    //Encoding unicode = Encoding.Unicode;

    //byte [] asBytes = unicode.GetBytes(mystr);

    //byte[] nullTermedAsBytes = new byte[asBytes.Length + 2];
    //nullTermedAsBytes.Initialize();
    //asBytes.CopyTo(nullTermedAsBytes, 0);

    String ^mystr = "1234";

    std::wstring mywstr;
    MarshalString(mystr,mywstr);

    wprintf(L"str is[%s]",mywstr.c_str());

    Console::ReadLine();

    return 0;
}
