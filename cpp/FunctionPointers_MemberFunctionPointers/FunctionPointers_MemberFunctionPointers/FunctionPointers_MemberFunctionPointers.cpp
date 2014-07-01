// FunctionPointers_MemberFunctionPointers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// ////////////////////////////////////
// function pointer stuff.
// ////////////////////////////////////
int functionA(long x)
{
    std::cout << "you called functionA(" << x << ")" << std::endl;
    return x;
}

int functionB(long x)
{
    std::cout << "you called functionB(" << x << ")" << std::endl;
    return x;
}


// ////////////////////////////////////
// class function pointer stuff.
// ////////////////////////////////////

class myClass
{
public:
    int member1(long x)
    {
        std::cout << "you called member1(" << x << ")" << std::endl;
        return x;
    }
    int member2(long x)
    {
        std::cout << "you called member2(" << x << ")" << std::endl;
        return x;
    }

    static int member3(long x)
    {
        std::cout << "you called member3(" << x << ")" << std::endl;
        return x;
    }
};

// global function pointer..
typedef int (*myGFP)(long x);
// member function pointer..
typedef int(myClass::* myClassFP)(long x);

int _tmain(int argc, _TCHAR* argv[])
{
    myGFP gfp1 = functionA;

    // parenthesis around FP is NOT optional, since operator precedence will do the wrong things w/o the parenthesis.
    std::cout << "returns[" << (*gfp1)(22) << "]" << std::endl;;

    gfp1 = functionB;   // notice no & !  functions w/o the parenthesis = pointer to the function.

    std::cout << "returns[" << (*gfp1)(33) << "]" << std::endl;;

    myClass *mcp = new myClass;

    myClassFP mcFP = &myClass::member1;

    std::cout << "returns[" << (mcp->*mcFP)(44) << "]" << std::endl;;

    mcFP = &myClass::member2;  // confusingly.. address of syntax ( & ) is required here.

    std::cout << "returns[" << (mcp->*mcFP)(55) << "]" << std::endl;;

    gfp1 = &myClass::member3;   // here, we use the GFP syntax.. since this member function is a static one
                                // which says a lot about static member functions.. from the compiler's 
                                // perspective they are just global functions with 
                                // mangled names and restricted access to static member variables of
                                // of a specific class.

    std::cout << "returns[" << (*gfp1)(66) << "]" << std::endl;;

	return 0;
}

