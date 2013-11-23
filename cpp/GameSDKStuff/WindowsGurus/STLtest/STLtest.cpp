// STLtest.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
   cout << "woohoo!" << endl;
   
   // create a vector and insert three items into it..
   vector<int> v1; // space for 3 items
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
   
   cout << "insert something (a one)" << endl;
   
   v1.push_back(1);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
   
   cout << "insert something (a two)" << endl;   
   
   v1.push_back(2);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something (a nine)" << endl;   
   v1.push_back(9);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something" << endl;   
   v1.push_back(8);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something" << endl;   
   v1.push_back(7);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something" << endl;   
   v1.push_back(6);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something" << endl;   
   v1.push_back(5);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
      
   cout << "insert something" << endl;   
   v1.push_back(4);
     
   cout << "v1.max_size()[" << v1.max_size()<< "]" << endl;
   cout << "v1.size()[" << v1.size() << "]" << endl;
   cout << "v1.capacity()[" << v1.capacity() << "]" << endl << endl; 
   
   // access examples..
   


   // via iterator access..
   vector<int>::iterator first   = v1.begin();
   vector<int>::iterator last    = v1.end();   
   
   while (first != last)
   {
      cout << "[" << *first << "] ";
      first++;
   }
   cout << endl;
   
   // sort the vector and reprint it..
   
   // sort it...
   
   cout << "sorting..." << endl << endl;
   sort(v1.begin(),v1.end());

   first   = v1.begin();
   last    = v1.end();   
   
   while (first != last)
   {
      cout << "[" << *first << "] ";
      first++;
   }

   cout << endl;
   // this is VERY IMPORTANT, since w/o it there will be a memory leak.
   v1.clear();
      
   _CrtDumpMemoryLeaks();
   
	return 0;
}

