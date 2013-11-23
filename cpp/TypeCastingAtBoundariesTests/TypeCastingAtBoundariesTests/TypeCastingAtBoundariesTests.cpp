// TypeCastingAtBoundariesTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{

    // 8 bit
    char c_min = -128;
    char c_max = 127;

    unsigned char uc_max = 255;

    // 16 bit
    short s_min = -32768;
    short s_max = 32767;
    unsigned short us_max = 65535;

    // 32 bit 
    unsigned int ui_max = 4294967295;
    unsigned long ul_max = 4294967295;

    // 64 bit
    __int64 i64_min = -9223372036854775808;
    __int64 i64_max = 9223372036854775807;
    unsigned __int64 ui64_max = 18446744073709551615;
    

    // since this is testing input ONLY.. we will test all assignment behaviors to signed ints ONLY.
    // unsigned to signed
    int receiver = 0;

    receiver = (int) c_min;
    std::cout << "receiver = (int) c_min;[" << receiver << "]" << std::endl;
    receiver = (int) c_max;
    std::cout << "receiver = (int) c_max;[" << receiver << "]" << std::endl;
    receiver = (int) uc_max;
    std::cout << "receiver = (int) uc_max;[" << receiver << "]" << std::endl;
    receiver = (int) s_min;
    std::cout << "receiver = (int) s_min;[" << receiver << "]" << std::endl;
    receiver = (int) s_max;
    std::cout << "receiver = (int) s_max;[" << receiver << "]" << std::endl;
    receiver = (int) us_max;
    std::cout << "receiver = (int) us_max;[" << receiver << "]" << std::endl;

    receiver = (int) ui_max;
    std::cout << "receiver = (int) ui_max;[" << receiver << "]" << std::endl;
    receiver = (int) ul_max;
    std::cout << "receiver = (int) ul_max;[" << receiver << "]" << std::endl;

    // the 'most correct'
    if(ui_max > 2147483647)
    {
       ui_max = 2147483647; // force to max..
    }
    receiver = (int) ui_max & 0x7FFFFFFF;
    std::cout << "receiver = (int) ui_max & 0x7FFFFFFF;[" << receiver << "]" << std::endl;
    if(ul_max > 2147483647)
    {
       ul_max = 2147483647; // force to max..
    }
    receiver = (int) ul_max & 0x7FFFFFFF;
    std::cout << "receiver = (int) ul_max & 0x7FFFFFFF;[" << receiver << "]" << std::endl;

    if(i64_min < -2147483648)
    {
        i64_min = -2147483648;  // force to min.
    }
    receiver = (int) i64_min;
    std::cout << "receiver = (int) i64_min;[" << receiver << "]" << std::endl;
    if(i64_max > 2147483647)
    {
       i64_max = 2147483647; // force to max..
    }
    receiver = (int) i64_max;
    std::cout << "receiver = (int) i64_max;[" << receiver << "]" << std::endl;
    receiver = (int) ui64_max & 0x7FFFFFFF;
    std::cout << "receiver = (int) ui64_max;[" << receiver << "]" << std::endl;
    
    for(__int64 i = i64_min;
        i < i64_max;
        i++)
    {
    }
   std::cout << "ended" << std::endl;


    std::cout << "test" << std::endl;
	return 0;
}

