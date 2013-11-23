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

int main()
{
    // TODO: Please replace the sample code below with your own.

    list<something*> my_list;
    list<something*>::iterator iter;

    my_list.push_back(new something(12));
    my_list.push_back(new something(5));
    my_list.push_back(new something(31));
    
    for(iter = my_list.begin();
        iter != my_list.end();
        iter++)
    {
        cout << "my_list[" << (*iter)->getI() << "]\n";
    }

    cout << "before sort\n";
    my_list.sort(greater<something*>());
    cout << "after sort\n";

    for(iter = my_list.begin();
        iter != my_list.end();
        iter++)
    {
        cout << "my_list[" << (*iter)->getI() << "]\n";
    }

	return 0;
}

