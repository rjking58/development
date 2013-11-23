
#include "UnmanagedPiece.h"
#include "ManagedUnmanagedCPP.h"
#include <iostream>
#include <ctime>

#define CALLS_TO_MEASURE 1000000

void IntPassTest(int i)
{
    ReceiveInt(i);
}

void StringPassTest(std::string &std_str)
{
    ReceiveString(std_str);
}

void DoStringPerfTest()
{
    clock_t startStringTest(clock());
    for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
    {
        std::string std_str = "1234567890";

		ReceiveString(std_str);
    }
    clock_t stopStringTest(clock());
    std::cout << "DoStringPerfTest::  call count:" << CALLS_TO_MEASURE << " in " << (stopStringTest - startStringTest) << " mSec" << std::endl;
}

void DoIntPerfTest()
{
    clock_t startIntTest(clock());
    for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
    {
		ReceiveInt(currCall);
    }
    clock_t stopIntTest(clock());
    std::cout << "DoIntPerfTest::  call count:" << CALLS_TO_MEASURE << " in " << (stopIntTest - startIntTest) << " mSec" << std::endl;
}

void DoNativeToManagedTest()
{
    std::cout << "start DoNativeToManagedTest" << std::endl;
    DoStringPerfTest();
    DoIntPerfTest();
    std::cout << "end DoNativeToManagedTest" << std::endl;
}

void StringPassTestOneWay(std::string &std_str)
{
    std::string mystr = std_str;
}
void IntPassTestOneWay(int i)
{
    int x = i;
}
