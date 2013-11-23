// ExampleUseOfEncodings.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::Text;

int main(array<System::String ^> ^args)
{
	//simple char * to managed string conversion.. this one is easy :).
	char * mychar = {"woohoo"};

	String ^myStr = gcnew String(mychar);

    Console::WriteLine(myStr);


    return 0;
}
