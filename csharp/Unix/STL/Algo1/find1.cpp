// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

#include <stl_function.h>
using namespace std;

class something
{
private:
    int m_i;
public:
    something(int i)
        :   m_i(i)
    {
    }
    int getI()const
    {
        return m_i;
    }
};


bool operator<(const something & lhs,const something & rhs)
{
    return (lhs.getI() < rhs.getI());
}


template <>
struct greater<something *>
{
    // results in an ascending sort in a list.
    bool operator()(something const * p1, something const * p2)
    {
        if (!p1)
            return true;
        if (!p2)
            return false;
        return p1->getI() < p2->getI();
    }
};

class SomethingIsEqualPtr
{
private:
	int m_valToFind;
public:
	SomethingIsEqualPtr(int valToFind)
		:	m_valToFind(valToFind)
	{
	}

	bool operator() (something *x)
	{
		cout << "testing(" << x->getI() << ")\n";

		return ((x->getI()) == m_valToFind);
	}
};

int main()
{
    // TODO: Please replace the sample code below with your own.

    list<something*> my_list;
    list<something*>::iterator iter;

    my_list.push_back(new something(12));
    my_list.push_back(new something(5));
    my_list.push_back(new something(31));
    
	list<something*>::iterator result;
	
	result = find_if(my_list.begin(),my_list.end(),SomethingIsEqualPtr(5));

	cout << "found(" << (*result)->getI() << ")\n";
	
	return 0;
}

