// stlMapTest.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include <map>
#include <list>
#include <vector>

class SimpleClass
{
private:
	int		m_val;
public:
	SimpleClass(int p_val) : m_val(p_val)
	{
	}
	int GetVal()
	{
		return m_val;
	}

	bool operator < (const SimpleClass * rhs)
	{
		return m_val < rhs->m_val;
	}

	bool operator > (const SimpleClass * rhs)
	{
		return m_val > rhs->m_val;
	}
	bool operator < (const SimpleClass & rhs)
	{
		return m_val < rhs.m_val;
	}

	bool operator > (const SimpleClass & rhs)
	{
		return m_val > rhs.m_val;
	}
};

class SimpleClass2
{
public:
    SimpleClass2()
    {
        std::cout << "const::SimpleClass2" << std::endl;
    }
    ~SimpleClass2()
    {
        std::cout << "dest::SimpleClass2" << std::endl;
    }
};

void MultiDeleteTest()
{
    typedef std::map<int,int> integerMapType;
    typedef std::list<integerMapType::iterator> intMapIterListType;
    
    intMapIterListType iterList;
    integerMapType intMap;

    for(int x = 0; x < 30; x++)
    {
        intMap.insert(std::pair<int,int>(x,x));
    }

    for(integerMapType::iterator currEntry = intMap.begin();
        currEntry != intMap.end();
        currEntry++)
    {
        if((currEntry->first % 2) == 0)
        {
            iterList.push_back(currEntry);
        }
    }
    for(intMapIterListType::iterator currListEntry = iterList.begin();
        currListEntry != iterList.end();
        currListEntry++)
    {
        intMap.erase(*currListEntry);
    }

    for(integerMapType::iterator currEntry = intMap.begin();
        currEntry != intMap.end();
        currEntry++)
    {
        std::cout << currEntry->first << " ";
    }
    std::cout << std::endl;

    //note that this increases the map count because it causes an 'accidental insert'.. 
    // not prefered IMO, but how it works.
    std::cout << "entries left BEFORE accidental insert[" << intMap.size() << "]" << std::endl;
    intMap[100];
    std::cout << "entries left AFTER accidental insert[" << intMap.size() << "]" << std::endl;

}

void VectorTest()
{
    std::vector<int> myvec;

    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    myvec.push_back(5);

    for(int x =0 ; x < 7; x++)
    {
        std::cout << "myvec[" << myvec[x] << "]" << std::endl;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
	// dump memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	SimpleClass *sc1 = new SimpleClass(4);
	SimpleClass *sc2 = new SimpleClass(6);
	SimpleClass *sc3 = new SimpleClass(8);

	std::cout << "sc1(" << sc1->GetVal() << ") < sc2(" << sc2->GetVal() << ") = " << (sc1 < sc2) << std::endl;
	std::cout << "sc2(" << sc2->GetVal() << ") < sc1(" << sc1->GetVal() << ") = " << (sc2 < sc1) << std::endl;
	std::cout << "sc1(" << sc1->GetVal() << ") > sc2(" << sc2->GetVal() << ") = " << (sc1 > sc2) << std::endl;
	std::cout << "sc2(" << sc2->GetVal() << ") > sc1(" << sc1->GetVal() << ") = " << (sc2 > sc1) << std::endl;

	// now make a map using less<SimpleClass> which takes advantage of the "operator <" method on SimpleClass
	
	typedef std::map<int,SimpleClass *,std::less<int>> SimpleClassMap;
	typedef SimpleClassMap::iterator SimpleClassMapIterator;
	typedef std::pair<int,SimpleClass *> sc_pair;

	// map is declared as a pointer rather than a by value local because 
	// the memory leak detection spuriously reports leaks if this isn't done (probably due to
	// the STL's handling of iterators)
	SimpleClassMap *sc_map = new SimpleClassMap();
	SimpleClassMapIterator sc_map_iter;

	sc_map->insert(sc_pair(sc1->GetVal(),sc1));
	sc_map->insert(sc_pair(sc2->GetVal(),sc2));
	sc_map->insert(sc_pair(sc3->GetVal(),sc3));

	for(int i = 0; i < 10; i++)
	{
		sc_map_iter = sc_map->find(i);
		std::cout << "(" << i << ") ";
		if(sc_map_iter != sc_map->end())
		{
			std::cout << "found! " << sc_map_iter->second->GetVal() << std::endl;
		}
		else
		{
			std::cout << "NOT found!" << std::endl;
		}
	}

	// this could more easily be done by deleting the local 
	// variables directly.. so this is just for demonstration 
	// purposes.
	for(sc_map_iter = sc_map->begin();
		sc_map_iter != sc_map->end();
		sc_map_iter++)
	{
		delete sc_map_iter->second;
	}
	delete sc_map;

	typedef std::map<int,SimpleClass2 *> SimpleClass2Map;
	typedef SimpleClass2Map::iterator SimpleClass2MapIterator;
	typedef std::pair<int,SimpleClass2 *> sc2_pair;
    
    SimpleClass2Map sc2Map;

    sc2Map.insert(sc2_pair(1,new SimpleClass2));
    sc2Map.insert(sc2_pair(2,new SimpleClass2));
    sc2Map.insert(sc2_pair(3,new SimpleClass2));

    for(SimpleClass2MapIterator it = sc2Map.begin();
        it != sc2Map.end();
        it++)
    {
        std::cout << "loop" << std::endl;
        delete it->second;
    }

    // clear does NOT auto-magically delete pointers.. its blissfully unaware.
    sc2Map.clear();


    MultiDeleteTest();

    VectorTest();

	// trace the dump out.
	_CrtDumpMemoryLeaks();

	return 0;
}

