// lambdas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

void outputI(int i)
{
    std::cout << i << " "; 
}

class myClass
{
private:
    int m_i;
public:
    myClass(int i) : m_i(i)
    {
    }

    void increment()
    {
        m_i++;
    }
    int get()
    {
        return m_i;
    }
};


int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<int> iv;

    for(int currVal = 0;
        currVal < 10;
        currVal++)
    {
        iv.push_back(currVal);
    }

    std::for_each(  iv.begin(),
                    iv.end(),
                    outputI);       // using function pointer

    std::cout << std::endl;

    std::for_each(  iv.begin(),
                    iv.end(),
                    [](int i)
                    { 
                        std::cout << i << " "; 
                    }                               );  // using lambda
    std::cout << std::endl;

    std::vector<int> ivSquares;
    // lambda's with return values..

    // int paramter returns double
    std::transform( iv.begin(),
                    iv.end(),
                    back_inserter(ivSquares),
                    [] (int n)  -> int
                    {
                        return n*n;
                    }                               );
    std::for_each(  ivSquares.begin(),
                    ivSquares.end(),
                    [](int i) 
                    { 
                        std::cout << i << " "; 
                    }                               );  // using lambda
    std::cout << std::endl;

    //use capture clause..
    int x = 3;
    int y = 7;

    // capture clause [x,y] 
    // makes copies of these local variables and makes those values
    // available to the lambda during execution..
    std::for_each(  iv.begin(),
                    iv.end(),
                    [x,y](int i)
                    {
                        if(i >= x && i <= y)
                        {
                            std::cout << "within range[" << i << "]" << std::endl;
                        }
                    }               );
    std::cout << std::endl;

    // capture 'all' semantically useful variables clause [=] 
    // makes copies of these local variables and makes those values
    // available to the lambda during execution..
    x =4;
    y=6;
    std::for_each(  iv.begin(),
                    iv.end(),
                    [=](int i)
                    {
                        if(i >= x && i <= y)
                        {
                            std::cout << "within range[" << i << "]" << std::endl;
                        }
                    }               );
    std::cout << std::endl;


    //change values in vector.. 
    // mutable + paramter reference..
    x =4;
    y=6;
    std::for_each(  iv.begin(),
                    iv.end(),
                    [=](int &r) mutable
                    {
                        const int old = r;
                        r *= 2;
                        x = y;
                        y = old;
                    }               );

    std::for_each(  iv.begin(),
                    iv.end(),
                    [](int i)
                    { 
                        std::cout << i << " "; 
                    }                               );  // using lambda
    std::cout << std::endl;

    std::cout << "x[" << x << "] y[" << y << "]" << std::endl;

    //change values in vector with references for captures..
    // mutable + paramter reference..
    x =4;
    y=6;
    std::for_each(  iv.begin(),
                    iv.end(),
                    [&x,&y](int &r) mutable
                    {
                        const int old = r;
                        r *= 2;
                        x = y;
                        y = old;
                    }               );

    std::for_each(  iv.begin(),
                    iv.end(),
                    [](int i)
                    { 
                        std::cout << i << " "; 
                    }                               );  // using lambda
    std::cout << std::endl;

    std::cout << "x[" << x << "] y[" << y << "]" << std::endl;

    // shorthand initialization of a vector using a reference lambda..

    iv.clear();
    int i = 0;
    std::generate_n(back_inserter(iv),
                    20,
                    [&i] 
                    { 
                        return i++; 
                    }                   );  // lambda is called once per insert operation...
                                            // notice no parameter list!

    std::for_each(  iv.begin(),
                    iv.end(),
                    [](int i)
                    { 
                        std::cout << i << " "; 
                    }                               );  // using lambda
    std::cout << std::endl;


    // example of updating a class iteratively using for_each and lambdas (vector)..
    std::vector<myClass> vmc;
    for(int i = 1; i <= 10; i++)
    {
        vmc.push_back(myClass(i));
    }

    std::for_each(  vmc.begin(),
                    vmc.end(),
                    [](myClass &mc)
                    {
                        std::cout << mc.get() << " ";
                    }
            );
    std::cout << std::endl;
    std::for_each(  vmc.begin(),
                    vmc.end(),
                    [](myClass &mc)
                    {
                        mc.increment();
                    }
            );
    std::for_each(  vmc.begin(),
                    vmc.end(),
                    [](myClass &mc)
                    {
                        std::cout << mc.get() << " ";
                    }
            );
    std::cout << std::endl;


    // example of updating a class iteratively using for_each and lambdas (vector)..
    std::map<int,myClass> mmc;
    for(int i = 1; i <= 10; i++)
    {
        mmc.insert(std::pair<int,myClass>(i,myClass(i)));
    }

    std::for_each(  mmc.begin(),
                    mmc.end(),
                    [](std::pair<int,myClass> mc)
                    {
                        std::cout << "myClass(f[" << mc.first << "] s[" << mc.second.get() << "]) " << std::endl;
                    }
            );
    std::cout << std::endl;
    std::for_each(  mmc.begin(),
                    mmc.end(),
                    [](std::pair<const int,myClass> &mc)    // this syntax allows for reference semantics on maps..
                    {
                        mc.second.increment();
                    }
            );

    std::for_each(  mmc.begin(),
                    mmc.end(),
                    [](std::pair<int,myClass> mc)
                    {
                        std::cout << "myClass(f[" << mc.first << "] s[" << mc.second.get() << "]) " << std::endl;
                    }
            );
    std::cout << std::endl;



    // simply boolean lambda..
    auto mod2func = 
        [](int x) -> bool
        {
            return (x % 2) == 0;
        };
    for(int x = 0; x < 4; x++)
    {

        if  (mod2func(x))
        {
            std::cout << "x[" << x << "] " << "is TRUE" << std::endl;
        }
        else
        {
            std::cout << "x[" << x << "] " << "is FALSE" << std::endl;
        }
    }


	return 0;
}

