// ManagedUnmanagedCPP.cpp : main project file.

#include <Windows.h>

using namespace System;

#include <msclr\marshal_cppstd.h>
#include <string>
#include <ctime>

#include "UnmanagedPiece.h"
#define CALLS_TO_MEASURE 1000000

void ReceiveString(std::string &std_str)
{
        String^ mngd_str = msclr::interop::marshal_as<String ^>(std_str);
        //Console::WriteLine(mngd_str);
}

void ReceiveInt(int i)
{
    int x = i;
    //Console::WriteLine(x);

}
public ref class MixedModeIF
{

public: 

	static void DoStringPerfTest()
	{
        clock_t startStringTest(clock());
        for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
        {
		    String^ mngd_str = "1234567890";

            std::string std_str = msclr::interop::marshal_as<std::string>(mngd_str);

		    StringPassTest(std_str);
        }
        clock_t stopStringTest(clock());
        Console::WriteLine("DoStringPerfTest::  call count:" + CALLS_TO_MEASURE + " in " + (stopStringTest - startStringTest) + " mSec");
	}
	static void DoIntPerfTest()
	{
        clock_t startIntTest(clock());
        for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
        {
		    IntPassTest(currCall);
        }
        clock_t stopIntTest(clock());
        Console::WriteLine("DoIntPerfTest::  call count:" + CALLS_TO_MEASURE + " in " + (stopIntTest - startIntTest) + " mSec");
	}
	static void DoStringPerfTestOneWay()
	{
        clock_t aggregateAllocs;
        clock_t aggregateConverts;
        clock_t aggregateCalls;

        clock_t startStringTest(clock());
        for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
        {
            clock_t startStringAllocTest(clock());
		    String^ mngd_str = "1234567890";
            clock_t stopStringAllocTest(clock());

            clock_t startStringConvertTest(clock());
            std::string std_str = msclr::interop::marshal_as<std::string>(mngd_str);
            clock_t stopStringConvertTest(clock());

            clock_t startStringCallTest(clock());
		    StringPassTestOneWay(std_str);
            clock_t stopStringCallTest(clock());
            
            aggregateAllocs += stopStringAllocTest - startStringAllocTest;
            aggregateConverts += stopStringConvertTest - startStringConvertTest;
            aggregateCalls += stopStringCallTest - startStringCallTest;
        }
        clock_t stopStringTest(clock());
        Console::WriteLine("DoStringPerfTestOneWay::  call count:" + CALLS_TO_MEASURE + " in " + (stopStringTest - startStringTest) + " mSec");
        Console::WriteLine("DoStringPerfTestOneWay::  aggregate allocs:" + aggregateAllocs + " mSec");
        Console::WriteLine("DoStringPerfTestOneWay::  aggregate converts:" + aggregateConverts + " mSec");
        Console::WriteLine("DoStringPerfTestOneWay::  aggregate calls:" + aggregateCalls + " mSec");

	}
	static void DoIntPerfTestOneWay()
	{
        clock_t startIntTest(clock());
        for(int currCall = 0; currCall < CALLS_TO_MEASURE; currCall++)
        {
		    IntPassTestOneWay(currCall);
        }
        clock_t stopIntTest(clock());
        Console::WriteLine("DoIntPerfTestOneWay::  call count:" + CALLS_TO_MEASURE + " in " + (stopIntTest - startIntTest) + " mSec");
	}

};



int main(array<System::String ^> ^args)
{
    MixedModeIF::DoStringPerfTest();
    MixedModeIF::DoIntPerfTest();
    
    DoNativeToManagedTest();

    MixedModeIF::DoStringPerfTestOneWay();
    MixedModeIF::DoIntPerfTestOneWay();

    Console::Read();
    return 0;
}
