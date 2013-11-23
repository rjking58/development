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

bool operator==(simpleStruc const &x,simpleStruc const &y)
{
    return x.m_i == y.m_i;
}
bool operator==(simpleStruc &x,simpleStruc &y)
{
    return x.m_i == y.m_i;
}

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

struct printSimpleStruc
{
    void operator() (simpleStruc x)
    {
        cout << "simpleStruc(" << x.m_i << ")" << endl;
    }
};

// this code was moved to a function from main because
// we wish to not accidentally detect 'leaks' that would simply
// be reasonably allocated memory in the stack automatic variables
// declared in this function (which used to be in main).
void VectorTest()
{
    // on non pointer stuff..
    vector<simpleStruc> my_vec;
    vector<simpleStruc>::const_iterator my_vec_cIter;
    vector<simpleStruc>::const_iterator my_vec_cLast;
    my_vec.push_back(simpleStruc(20));
    my_vec.push_back(simpleStruc(10));
    my_vec.push_back(simpleStruc(25));

    // simple loop support.
    my_vec_cIter = my_vec.begin();
    my_vec_cLast = my_vec.end();
    while(my_vec_cIter != my_vec_cLast)
    {
        cout << "my_vec(" << (*my_vec_cIter).m_i << ")" << endl;
        my_vec_cIter++;
    }

    //inserting into a vector..
    my_vec.insert(my_vec.begin(),simpleStruc(99));
    // using for_each instead of looping (more efficient)..
    for_each(my_vec.begin(),
             my_vec.end(),
             printSimpleStruc());

    //insert '13' after '10'
    vector<simpleStruc>::iterator result;
	result = find(my_vec.begin(),my_vec.end(),simpleStruc(10));

    if (result != my_vec.end())
    {
        result++;
        cout << "found: simpleStruc(" << (*result).m_i << ")" << endl;
        // this is NOT performant.. but an example of vector insert..
        my_vec.insert(result,simpleStruc(13));
        // using for_each instead of looping (more efficient)..
        for_each(my_vec.begin(),
                 my_vec.end(),
                 printSimpleStruc());
    }
    else
    {
        cout << "not found!!" << endl;
    }
	result = find(my_vec.begin(),my_vec.end(),simpleStruc(25));

    if (result != my_vec.end())
    {
        result++;
        cout << "found: simpleStruc(" << (*result).m_i << ")" << endl;
        // this is NOT performant.. but an example of vector insert..
        my_vec.insert(result,simpleStruc(26));
        // using for_each instead of looping (more efficient)..
        for_each(my_vec.begin(),
                 my_vec.end(),
                 printSimpleStruc());
    }
    else
    {
        cout << "not found!!" << endl;
    }

}

int main()
{
    // TODO: Please replace the sample code below with your own.

    VectorTest();
//    _CrtDumpMemoryLeaks();

    return 0;
}

