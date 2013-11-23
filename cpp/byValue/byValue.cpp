// byValue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

struct my_s
{
	int		x;
	double	y;
};

namespace NS_ENUM_STRS
{
	enum ENUM_STRS
	{
		STR1,
		STR2,
		STR3
	};
}
char str1[] = "first string";
char str2[] = "second string";
char str3[] = "third string";

bool GiveMeString( NS_ENUM_STRS::ENUM_STRS	strToGet,
				   char *					strOut,
				   unsigned int				strOutLen)
{
	bool retval = false;
	switch (strToGet)
	{
	case NS_ENUM_STRS::STR1 :
		if(strOutLen >= strlen(str1) + 1)
		{
			strcpy_s(strOut,strOutLen,str1);
			retval = true;
		}
		break;
	case NS_ENUM_STRS::STR2 :
		if(strOutLen >= strlen(str2) + 1)
		{
			strcpy_s(strOut,strOutLen,str2);
			retval = true;
		}
		break;
	case NS_ENUM_STRS::STR3 :
		if(strOutLen >= strlen(str3) + 1)
		{
			strcpy_s(strOut,strOutLen,str3);
			retval = true;
		}
		break;
	}
	return retval;
}



int _tmain(int argc, _TCHAR* argv[])
{
	char *receiver = new char[13];
	bool retVal = false;
	
	retVal = GiveMeString(NS_ENUM_STRS::STR1,
						 receiver,
						 13);
	retVal = GiveMeString(NS_ENUM_STRS::STR2,
						 receiver,
						 13);
	retVal = GiveMeString(NS_ENUM_STRS::STR3,
						 receiver,
						 13);



	return 0;
}

