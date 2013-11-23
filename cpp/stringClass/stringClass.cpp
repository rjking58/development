// stringClass.cpp : main project file.

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace System;

void OutputStr(std::string s);

int main(array<System::String ^> ^args)
{
	std::string str("werble");


	OutputStr(str);

	std::string str2 = str + " snerve";

	OutputStr(str2);


	// in place test..
	str += " gerp";

	OutputStr(str);

	str2 = str + " snerve";

	OutputStr(str2);


    return 0;
}

void OutputStr(std::string s)
{
	std::cout << "size(" << s.size() << ") ";
	std::cout << s << std::endl;

	std::string::iterator end_o_s = s.end();
	end_o_s--;
	std::cout << "s.end() - 1='" << *end_o_s << "'" << std::endl;
	end_o_s--;
	std::cout << "s.end() - 2='" << *end_o_s << "'" << std::endl;
}
