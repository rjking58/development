// modAndDiv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>

int _tmain(int argc, _TCHAR* argv[])
{
    std::list<std::string> nameList;

    for(int currId = 0; 
        currId < 200;
        currId++)
    {
        int currAttribute = (currId % 100) + 1;
        int currObject = (currId / 100) + 1;

        std::ostringstream generatedName;

        generatedName   << "PVDR50_"  
                        << std::setw(3) << std::setfill('0') << currObject 
                        << ".UDA" 
                        << std::setw(3) << std::setfill('0') << currAttribute << std::endl;
        nameList.push_back(generatedName.str());
    }

	return 0;
}

