// detectMinutesPassing.cpp : main project file.

#include "stdafx.h"

#include <Windows.h>
#include <ctime>
#include <iostream>


using namespace System;
using namespace System::IO;

// 1 minute as a test..
#define MILLSECONDS_PER_MINUTE 60000

// class that allows detection of no activity
// for a specific timeperiod.
// use of this class is relatively simple..
// 1. instantiate it with the time period you are interested in..
//    the value to pass to the constructor is in milliseconds..
//    so if you want to detect 10 minutes of inactivity, you would
//    pass in 600000
// 2. In your code, place calls to 'ShowActivity' anywhere where you
//    want to reset the inactivity timer.. 
// 3. In the place in your code where you wish to detect inactivity, 
//    use the 'InactivityDetected' call.  Make sure to call this periodically,
//    since otherwise your detection may be way off (usage of this class in 
//    the consumer is in a loop that runs every few hundred milliseconds).

// locking is NOT provided here, since it is provide by the Consumer code itself.
class InactivityDetector
{
private:
    clock_t m_startTime;
    long    m_timePeriodToDetectInMilliseconds;
public:
    InactivityDetector(long timePeriodToDetectInMinutes) :  m_startTime(clock()),
                                                            m_timePeriodToDetectInMilliseconds(timePeriodToDetectInMinutes * 60000)
    {
    }

    void ShowActivity()
    {   
        m_startTime = clock();
    }

    bool InactivityDetected()
    {
        bool inactivityDetected = false;
        clock_t endTime(clock());
        
        // in a multi threaded environment it is possible to get it the other way.. 
        // and its an 'activity' detected for the purposes of this algorithm.
        if(endTime > m_startTime)
        {
            if( (endTime - m_startTime) > m_timePeriodToDetectInMilliseconds )
            {
                inactivityDetected = true;
            }
        }
        return inactivityDetected;
    }
};

int main()
{
    InactivityDetector id(1); // 1 minute..
    

    Console::WriteLine("No activity for entire period");
    int count = 0;
    while( ! id.InactivityDetected() )
    {
        ::Sleep(1000);
        count ++;
        std::cout << count << " ";
    }

    Console::WriteLine();
    Console::WriteLine("exited loop at count above..");

    Console::WriteLine("activity after 30 seconds, then none");
    id.ShowActivity();
    count = 0;
    while( ! id.InactivityDetected() )
    {
        ::Sleep(1000);
        count ++;
        if(count == 30)
        {
            id.ShowActivity();
        }
        std::cout << count << " ";
    }

    Console::WriteLine();
    Console::WriteLine("exited loop at count above..");
    Console::WriteLine("activity after 10,20,30,40,50 seconds, then none");
    id.ShowActivity();
    count = 0;
    while( ! id.InactivityDetected() )
    {
        ::Sleep(1000);
        count ++;
        switch(count)
        {
        case 10:
        case 20:
        case 30:
        case 40:
        case 50:
            id.ShowActivity();
            break;
        default:
            break;
        }
        std::cout << count << " ";
    }

    Console::ReadLine();

    return 0;
}
