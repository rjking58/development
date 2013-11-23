// This is the Cmain project file for VC++ application project 
// generated using an Application Wizard.
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
// required by Linux.. Linux includes must not auto-magically include this?
#include <stl_function.h>
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

// This routine place comments at the head of a section of debug output 




using namespace std;

class simpleStruc
{
public:
    simpleStruc(int i)
        :   m_i(i)
    {
    }
    int m_i;
};

// comparison functor for simpleStruc* so that it works with sort, etc.
namespace std
{
	template <> class greater<simpleStruc *>
	{
	public:
		// results in an ascending sort in a list.
		bool operator()(const simpleStruc * p1, const simpleStruc * p2)
		{
			if (!p1)
				return true;
			if (!p2)
				return false;
			return p1->m_i < p2->m_i;
		}
	};
}


// this code was moved to a function from main because
// we wish to not accidentally detect 'leaks' that would simply
// be reasonably allocated memory in the stack automatic variables
// declared in this function (which used to be in main).
void IterTest()
{
    vector<int> my_vec;
    vector<int>::const_iterator my_vec_cIter;
    vector<int>::const_iterator my_vec_cLast;
    my_vec.push_back(10);
    my_vec.push_back(20);
    my_vec.push_back(25);

    my_vec_cIter = my_vec.begin();
    my_vec_cLast = my_vec.end();
    while(my_vec_cIter != my_vec_cLast)
    {
        cout << "my_vec(" << *my_vec_cIter << ")\n";
        my_vec_cIter++;
    }

    list<int> my_list;
    list<int>::iterator my_list_iter;
    list<int>::iterator my_list_last;
    list<int>::iterator my_list_result;
    my_list.push_back(10);
    my_list.push_back(30);
    my_list.push_back(50);
    
    my_list_last = my_list.end();
    my_list_iter = my_list.begin();
    cout << "my_list.size() = " << my_list.size() << "\n";
    while(my_list_iter != my_list_last)
    {
        cout << "my_list(" << *my_list_iter << ")\n";
        my_list_iter++;
    }

    my_list_last = my_list.end();
    my_list_result = find(my_list.begin(),
                          my_list.end(),
                          30);
    if (my_list_result != my_list_last)
    {
        my_list.erase(my_list_result);
    }
    
    my_list_last = my_list.end();
    my_list_iter = my_list.begin();
    cout << "my_list.size() = " << my_list.size() << "\n";
    while(my_list_iter != my_list_last)
    {
        cout << "my_list(" << *my_list_iter << ")\n";
        my_list_iter++;
    }


    // pointer list test..
    list<simpleStruc *> my_ptr_list;
    list<simpleStruc *>::iterator my_ptr_list_iter;
    list<simpleStruc *>::iterator my_ptr_list_end;

    my_ptr_list.push_back(new simpleStruc(20));
    my_ptr_list.push_back(new simpleStruc(10));
    my_ptr_list.push_back(new simpleStruc(30));
    
    my_ptr_list_iter = my_ptr_list.begin();
    my_ptr_list_end = my_ptr_list.end();

    while (my_ptr_list_iter != my_ptr_list_end)
    {
        cout << "my_ptr_list(" << (*my_ptr_list_iter)->m_i << ")\n";
        my_ptr_list_iter++;
    }

    cout << "my_ptr_list starting sort of pointers..\n";
    my_ptr_list.sort();
    cout << "my_ptr_list sort of pointers complete..\n";

    my_ptr_list_iter = my_ptr_list.begin();
    my_ptr_list_end = my_ptr_list.end();

    while (my_ptr_list_iter != my_ptr_list_end)
    {
        cout << "my_ptr_list(" << (*my_ptr_list_iter)->m_i << ")\n";
        my_ptr_list_iter++;
    }


    // sort'em.
    cout << "my_ptr_list starting sort of derefed pointers..\n";
    my_ptr_list.sort(greater<simpleStruc *>());
    cout << "my_ptr_list sort of derefed pointers complete..\n";

    my_ptr_list_iter = my_ptr_list.begin();
    my_ptr_list_end = my_ptr_list.end();

    while (my_ptr_list_iter != my_ptr_list_end)
    {
        cout << "my_ptr_list(" << (*my_ptr_list_iter)->m_i << ")\n";
        my_ptr_list_iter++;
    }

    // remove all pointers now (lets be clean! :D)
    my_ptr_list_iter = my_ptr_list.begin();
    my_ptr_list_end = my_ptr_list.end();

    while (my_ptr_list_iter != my_ptr_list_end)
    {
        delete (*my_ptr_list_iter);
        my_ptr_list_iter++;
    }
}

int main()
{
    // TODO: Please replace the sample code below with your own.

    IterTest();
//    _CrtDumpMemoryLeaks();

    return 0;
}

