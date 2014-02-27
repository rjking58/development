// LambdaStructs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <algorithm>
#include <iostream>

class C1
{
public:
	int m_x;
	int m_y;
};

typedef std::map<int,C1> C1map;

int _tmain(int argc, _TCHAR* argv[])
{
	C1map c1map;
	typedef std::pair<int,C1> c1mapPairByValue;
	typedef std::pair<const int,C1>& c1mapPairByRef;

	for(int x = 0; x < 10; x++)
	{
		C1 c1;
		c1.m_x = x;
		c1.m_y = x*2;

		c1map.insert(std::make_pair(x,c1));
	}

	// copy of element passed.
	std::for_each(	c1map.begin(),
					c1map.end(),
					[](c1mapPairByValue currElem)
					{
						std::cout << "x[" << currElem.second.m_x << "]  y[" << currElem.second.m_y << "]" << std::endl;
					}
					);

	// reference to element passed.
	// notice that it requires you to make the key constant.. 
	std::for_each(	c1map.begin(),
					c1map.end(),
					[](c1mapPairByRef currElem)
					{
						currElem.second.m_y *=  2;
					}
					);

	// copy of element passed.
	std::for_each(	c1map.begin(),
					c1map.end(),
					[](c1mapPairByValue currElem)
					{
						std::cout << "x[" << currElem.second.m_x << "]  y[" << currElem.second.m_y << "]" << std::endl;
					}
					);

	return 0;
}

