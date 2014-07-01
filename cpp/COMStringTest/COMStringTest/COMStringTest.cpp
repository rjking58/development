// COMStringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "atlbase.h"
#include "comdef.h"
#include "AAComBSTR.h"

#include <map>
#include <iostream>
#include <sstream>

void BstrAsKeyInMapTest()
{
    int *x = new int;
    ::Sleep(30000);

    std::wostringstream constructedString;
    std::map<_bstr_t, int> bstr_t_by_int_map;

    std::cout << "start..." << std::endl;
    for(int currStr = 0;currStr < 1000; currStr++)
    {
        constructedString << L"a_bstr_" << currStr;


        AAComBSTR constructedCComBSTR;
        // this MUST be an Attach.. if used during construction it expects that
        // the user retains ownership of the string passed in and then must 
        // manually remove it..
        constructedCComBSTR.Attach(SysAllocString(constructedString.str().c_str()));
        constructedCComBSTR.ToUpper();

        // here, reference counting of the contained BSTR is what is keeping track of
        // how many references are outstanding.. deleting of the constructedBSTR removes
        // one reference, clearing of the map at the end removes the other..
        bstr_t_by_int_map.insert(std::pair<_bstr_t, int>(constructedCComBSTR.m_str,currStr));

        // clear before next time through the loop.
        constructedString.str(L"");
    }

    std::cout << "end..." << std::endl;

    for(std::map<_bstr_t, int>::iterator currPair = bstr_t_by_int_map.begin();
        currPair != bstr_t_by_int_map.end();
        currPair++)
    {
        std::wcout << currPair->first << L" " << currPair->second << std::endl;
    }

    std::cout << "before clean..." << std::endl;

    ::Sleep(30000);

    bstr_t_by_int_map.clear();


    std::cout << "after clean..." << std::endl;
    ::Sleep(30000);

}

// copy leak test
void CopyLeakTest()
{
    std::cout << " before test " << std::endl;
    ::Sleep(30000);
    for(int x = 1; x < 1000000; x++)
    {
        int *z = new int[4];

        BSTR myBstr = SysAllocString(L"weeeeeee  wooho yo yo yo");

        // copy sematics, AAComBSTR
        //AAComBSTR selfDeleting = myBstr;
        // copy semantics _bstr_t
        //_bstr_t selfDeleting2;
        //selfDeleting2.Assign(myBstr);

        //SysFreeString(myBstr);
    }
    std::cout << " after test " << std::endl;
    ::Sleep(30000);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //BstrAsKeyInMapTest();
    CopyLeakTest();


	return 0;
}

