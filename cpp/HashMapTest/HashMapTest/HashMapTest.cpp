// HashMapTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <hash_map>
#include <iostream>

class X
{
private:
    int m_i;
public:
    X(int i)
        :   m_i(i)
    {
        //std::cout << "creating X(" << m_i << ")" << std::endl;
    }
    ~X()
    {
        //std::cout << "destroying X(" << m_i << ")" << std::endl;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::hash_map<int,X*> myMap;


    std::cout << "bucket_count(" << myMap.bucket_count() << ")" << std::endl;
    std::cout << "load_factor(" << myMap.load_factor() << ")" << std::endl;
    std::cout << "max_load_factor(" << myMap.max_load_factor() << ")" << std::endl;
    std::cout << "max_bucket_count(" << myMap.max_bucket_count() << ")" << std::endl;

    ::_sleep(10000);


    myMap.rehash(100000);

    std::cout << "bucket_count(" << myMap.bucket_count() << ")" << std::endl;
    std::cout << "load_factor(" << myMap.load_factor() << ")" << std::endl;
    std::cout << "max_load_factor(" << myMap.max_load_factor() << ")" << std::endl;
    std::cout << "max_bucket_count(" << myMap.max_bucket_count() << ")" << std::endl;

    for(int x = 0; x < 100000; x++)
    {
        myMap.insert(std::pair<int,X*>(x,new X(x)));

        if( (x % 10000) == 0)
        {
            std::cout << x << std::endl;
            ::_sleep(10000);
        }
    }

    std::cout << "bucket_count(" << myMap.bucket_count() << ")" << std::endl;
    std::cout << "load_factor(" << myMap.load_factor() << ")" << std::endl;
    std::cout << "max_load_factor(" << myMap.max_load_factor() << ")" << std::endl;
    std::cout << "max_bucket_count(" << myMap.max_bucket_count() << ")" << std::endl;

    std::hash_map<int,X*>::iterator foundItem;

    foundItem  = myMap.find(1);

    if(foundItem != myMap.end())
    {
        // erase does NOT delete the pointer.. that must be manually done.
        delete foundItem->second;
        myMap.erase(foundItem);
    }


    std::cout << "size of myMap[" << myMap.size() << "]" << std::endl;

    ::_sleep(10000);

    // hash map size tests..


	return 0;
}

