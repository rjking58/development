// HashMapTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <hash_map>
#include <iostream>

class X
{
public:
    X()
    {
        std::cout << "creating X" << std::endl;
    }
    ~X()
    {
        std::cout << "destroying X" << std::endl;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::hash_map<int,X*> myMap;

    myMap.insert(std::pair<int,X*>(1,new X));

    std::hash_map<int,X*>::iterator foundItem;

    foundItem  = myMap.find(1);

    if(foundItem != myMap.end())
    {
        // erase does NOT delete the pointer.. that must be manually done.
        delete foundItem->second;
        myMap.erase(foundItem);
    }


    std::cout << "size of myMap[" << myMap.size() << "]" << std::endl;

	return 0;
}

