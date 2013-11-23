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
    int refnum;
public:
    something(int i)
        :   m_i(i),
            refnum(0)
    {
    }

    something (something const &x)
    {
        m_i = x.m_i;
        refnum = x.refnum + 1;

    }
    int getI()const
    {
        return m_i;
    }
    int getRefnum()const
    {
        return refnum;
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

//void printSomething (something *x)
//{
//    cout << "something(" << x->getI() << ")" << endl;
//}

// now as a functor
struct printSomething
{
    void operator() (something *x)
    {
        cout << "something(" << x->getI() << ") [" << x->getRefnum() << "]" << endl;
    }
};
class copySomething
{
private:
    list<something *> *m_list;
public:
    copySomething(list<something *> *list)
        :   m_list(list)
    {
    }
    void operator() (something *x)
    {
        m_list->push_back(new something(*x));
    }
};

class deletePtr
{
public:
    void operator() (something *x)
    {
        delete x;
    }
};



int main()
{
    // TODO: Please replace the sample code below with your own.

    list<something*> my_list;
    list<something*> my_list2;
    list<something*>::iterator iter;

    my_list.push_back(new something(12));
    my_list.push_back(new something(5));
    my_list.push_back(new something(31));
    
    for_each(my_list.begin(),
             my_list.end(),
             printSomething());

    // as expected.. this doesn't work on pointers as is required..
    // so instead create a foreach that will do the same thing..
    
    // copy(my_list.begin(),my_list.end(), my_list2.begin());
    
    for_each(my_list.begin(),
             my_list.end(),
             copySomething(&my_list2));
    for_each(my_list.begin(),
             my_list.end(),
             printSomething());
    for_each(my_list2.begin(),
             my_list2.end(),
             printSomething());
    
    for_each(my_list.begin(),
             my_list.end(),
             deletePtr());
    my_list.clear();
    for_each(my_list2.begin(),
             my_list2.end(),
             deletePtr());
    my_list2.clear();

    cout << "my_list.empty(" << my_list.empty() << ")" << endl;
    cout << "my_list2.empty(" << my_list2.empty() << ")" << endl;
    
    
    return 0;
}

