// StringSubStrTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <sstream>
#include <iostream>

std::string stripPath(std::string sTempName)
{
	size_t pos = sTempName.find_first_of('/');
	while( pos != std::string::npos)
	{

		sTempName = sTempName.substr(pos + 1,sTempName.size()- (pos + 1));
		pos = sTempName.find_first_of('/');

		{
			std::ostringstream oss;
			oss << sTempName;
		}
	}
	return sTempName;
}


int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << stripPath("/xx/yy/zzzz.ff");
	return 0;
}



