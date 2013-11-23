// binarysearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


bool binary_s(int my_ary[],unsigned int my_ary_sz,int srch, int &found_ofst)
{
	bool found = false;
	found_ofst = 1;
	if (my_ary_sz < 2)
	{
		// 0 case covered by fall through..
		if (my_ary_sz == 1)// one case..
		{
			if (srch == my_ary[0])
			{
				found = true;
			}
		}
	}
	else
	{
		bool exhausted = false;
		int low = 0;
		int high = my_ary_sz - 1;
		found_ofst = (((high - low) + 1)/2) + low;
		while (! found  && ! exhausted)
		{
			if(my_ary[found_ofst] == srch)
			{
				found = true;
			}
			else
			{
				if(my_ary[found_ofst] < srch) // go high
				{
					low = found_ofst + 1;
				}
				else
				{
					high = found_ofst - 1;
				}
				if(low > high)
				{
					exhausted = true;
				}
				found_ofst = (((high - low) + 1)/2) + low;
			}
		}
	}

	return found;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int test1[10] = {1,3,5,7,9,11,13,15,17,19};
	int test1_sz = (sizeof test1)/(sizeof (int));
	int test2[11] = {1,2,3,4,5,6,7,8,9,10,11};
	int test2_sz = (sizeof test2)/(sizeof (int));

	for (int ofst = 0; ofst < test1_sz; ofst++)
	{
		std::cout << "test1[" << ofst << "]==" << test1[ofst] << std::endl;
	}

	int found_ofst;
	bool found = false;
	for (int test_val = 0; test_val < 25; test_val++)
	{
		found = binary_s(test1,test1_sz,test_val,found_ofst);
		if (found)
		{
			std::cout << "    found " << test_val << "@ " << "ofst(" << found_ofst << ")" << std::endl;
		}
		else
		{
			std::cout << "NOT found " << test_val << std::endl;
		}
	}
	for (int test_val = 0; test_val < 25; test_val++)
	{
		found = binary_s(test2,test2_sz,test_val,found_ofst);
		if (found)
		{
			std::cout << "    found " << test_val << "@ " << "ofst(" << found_ofst << ")" << std::endl;
		}
		else
		{
			std::cout << "NOT found " << test_val << std::endl;
		}
	}

	return 0;
}

