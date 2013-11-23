// passedArySize.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

void myMethod(std::vector<std::vector<int>> v)
{
    std::cout << v.size() << std::endl;

}
int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<std::vector<int>> v_v;
    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> v3;
    for(int x = 0;
        x < 10;
        x++)
    {
        if(x < 3)
        {
            v1.push_back (x);
        }
        else if (x < 5)
        {
            v2.push_back (x);
        }
        else
        {
            v3.push_back (x);
        }

        v_v.push_back (v1);
        v_v.push_back (v2);
        v_v.push_back (v3);
    }

    myMethod(v_v);

	return 0;
}

