// PluralExceptions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

class DemoClass
{
public:
    DemoClass()
    {
        cout << "DemoClass()" << std::endl;
    }
    ~DemoClass()
    {
        cout << "~DemoClass()" << std::endl;
    }
};

void SimpleThrowExample(int i)
{
    if(i == 0)
    {
        throw invalid_argument("oops, 0 passed to SimpleThrowExample");
    }
}
void SimpleExceptionTest()
{
    try 
    {
        // destructor is called after block exit before catch execution..
        auto_ptr<DemoClass> apdc(new DemoClass);
        vector <int> v;
        v.push_back(1);

        int j =  v.at(99);
    }
    // first MATCHING block gets the exception..
    catch ( out_of_range &e)
    {
        cout << "<out_of_range> " << e.what() << endl;
    }
    // more general exception comes AFTER the more specific..
    // do NOT use by value here.. since object slicing will come into play
    catch ( exception &e)
    {
        cout << "<exception> " << e.what() << endl;
    }

}


int _tmain(int argc, _TCHAR* argv[])
{
    SimpleExceptionTest();

    try
    {
        SimpleThrowExample(0);
    }
    catch(invalid_argument &e)
    {
        cout << "SimpleThrowExample failed: " << e.what() << endl;
    }

	return 0;
}

