// STLIteratorFunnyBusiness.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <iostream>

class c
{
    int m_id;
public:
    c() : m_id(0) 
    {
        std::cout << "default constructor" << std::endl;
    }
    c(int id) : m_id(id) 
    {
        std::cout << "param constructor id[" << m_id << "]" << std::endl;
    }
    c( const c &ref)
    {
        m_id = ref.m_id;
        std::cout << "copy constructor id[" << m_id << "]" << std::endl;
    }
    ~c()
    {
        std::cout << "destructor [" << m_id << "]" << std::endl;
    }
    void setId(int id)
    {
        m_id = id;
    }
    void doCout()
    {
        std::cout << "output from doCout[" << m_id << "]" << std::endl;
    }
};

struct x
{
    c m_c;
};

int _tmain(int argc, _TCHAR* argv[])
{



#if 0
    std::map<int,x> longByX;

    x anX;
    anX.m_c.setId(20);

    anX.m_c.doCout();

    longByX.insert(std::make_pair<int,x>(1,anX));

    std::map<int,x>::iterator itr = longByX.find(3);

    // specifically WRONG.. and not reported in release mode.
    // the itr here is == longByX.end().. but this syntax is allowed.. and can result in BIG leaks 
    // depending on the situation.
    itr->second.m_c.doCout();
#endif

#if 1
    std::map<int,int> intByint;

    intByint.insert(std::make_pair<int,int>(1,1));
    intByint.insert(std::make_pair<int,int>(2,2));

    std::map<int,int>::iterator foundItem = intByint.find(2);

    foundItem->second--;

    for(std::map<int,int>::iterator curritem = intByint.begin();
        curritem != intByint.end();
        curritem++)
    {
        std::cout << "first[" << curritem->first << "] second[" << curritem->second << "]" << std::endl;
    }


#endif
	return 0;
}

