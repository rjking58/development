// NumericLimits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <limits>
#include <iostream>


using std::cout;
using std::endl;
using std::numeric_limits;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "The range for type short is from "
		<< numeric_limits<short>::min()
		<< " to "
		<< numeric_limits<short>::max() << endl;
	cout << "The range for type int is from "
		<< numeric_limits<int>::min()
		<< " to "
		<< numeric_limits<int>::max() << endl;
	cout << "The range for type long is from "
		<< numeric_limits<long>::min()
		<< " to "
		<< numeric_limits<long>::max() << endl;
	cout << "The range for type float is from "
		<< numeric_limits<float>::min()
		<< " to "
		<< numeric_limits<float>::max() << endl;
	cout << "The range for type double is from "
		<< numeric_limits<double>::min()
		<< " to "
		<< numeric_limits<double>::max() << endl;
	cout << "The range for type long double is from "
		<< numeric_limits<long double>::min()
		<< " to "
		<< numeric_limits<long double>::max() << endl;
	cout << endl;


    //conversion limits int vs. float

    int adjustFor60Seconds = 0;

    for(int currTimePeriod = 50; 
        currTimePeriod < 3000; 
        currTimePeriod += 50)
    {
        adjustFor60Seconds = (int) (1000.0/(float)currTimePeriod * 60.0);

        std::cout   << "adjustFor60Seconds[" << adjustFor60Seconds << "] "
                    << "currTimePeriod[" << currTimePeriod << "] " 
                    << "multiplied together[" << adjustFor60Seconds * currTimePeriod << "] "
                    <<  std::endl;
    }

	return 0;
}

