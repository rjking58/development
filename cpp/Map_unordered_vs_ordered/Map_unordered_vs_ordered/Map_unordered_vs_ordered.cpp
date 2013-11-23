// Map_unordered_vs_ordered.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <unordered_map>
#include <hash_map>
#include <iostream>
#include <ctime>

int _tmain(int argc, _TCHAR* argv[])
{
	std::hash_map<long,long> m_uno_map;
	std::map<long,long> m_map;

	const int InsertCount = 100000;
	const int AccessMultipler = 100;

	//m_uno_map.max_load_factor(5.0);
	m_uno_map.rehash(200000);

	clock_t startUnOrderedInserts(clock());

	for(long valToInsert = 0; valToInsert < InsertCount; valToInsert++)
	{
		m_uno_map.insert(std::make_pair<long,long>(valToInsert,valToInsert+200000000));
#if 0
		if(		(valToInsert > 0) 
			&&	((valToInsert % 1000) == 0)	)
		{
			std::cout << valToInsert << std::endl;
		}
#endif
	}
	clock_t endUnOrderedInserts(clock());

	std::cout << "currentSize:" << m_uno_map.size() << std::endl; // << " bucket_count:" << m_uno_map.bucket_count() << std::endl;

	clock_t startOrderedInserts(clock());
	for(long valToInsert = 0; valToInsert < InsertCount; valToInsert++)
	{
		m_map.insert(std::make_pair<long,long>(valToInsert,valToInsert+300000000));
#if 0
		if(		(x > 0) 
			&&	((x % 1000) == 0)	)
		{
			std::cout << "++" << x << std::endl;
		}
#endif
	}
	clock_t endOrderedInserts(clock());


	

	clock_t startUnOrderedAccesses(clock());
	for(int accessCount = 0; accessCount < AccessMultipler; accessCount++)
	{
		for(int valToAccess = 0; valToAccess < InsertCount; valToAccess++)
		{
			std::hash_map<long,long>::iterator unoIter = m_uno_map.find(valToAccess);
			//std::cout << unoIter->second << std::endl;
		}
	}
	clock_t endUnOrderedAccesses(clock());

	clock_t startOrderedAccesses(clock());
	for(int accessCount = 0; accessCount < AccessMultipler; accessCount++)
	{
		for(int valToAccess = 0; valToAccess < InsertCount; valToAccess++)
		{
			std::map<long,long>::iterator orIter = m_map.find(valToAccess);
			//std::cout << orIter->second << std::endl;
		}
	}
	clock_t endOrderedAccesses(clock());



    std::cout << "insert count per value[1] total inserts[" << InsertCount << "]" << std::endl;
    std::cout << "access count per value[" << AccessMultipler << "] total accesses[" << AccessMultipler * InsertCount << "]" << std::endl;
	std::cout << "hash inserts in ms:" << (endUnOrderedInserts - startUnOrderedInserts) << std::endl;
	std::cout << "ordered inserts in ms:" << (endOrderedInserts - startOrderedInserts) << std::endl;
	std::cout << "hash accesses in ms:" << (endUnOrderedAccesses - startUnOrderedAccesses) << std::endl;
	std::cout << "ordered accesses in ms:" << (endOrderedAccesses - startOrderedAccesses) << std::endl;
	std::cout << "end" << std::endl;

	return 0;
}

