// templates1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

template <class T, int i> 
class myTemplClass
{
public:
	int getSizeOfSmallAryElement()
	{
		return sizeof(small_ary[0]);
	}
	int getSizeOfSmallAry()
	{
		return (sizeof(small_ary)/sizeof(small_ary[0]));
	}
private:
	T small_ary[i];
};

// Parameter typing example 1 (whole class template)
template <class T>
class templClass1
{
public:
	T some_method(T x)
	{
		// some pointless activity
		return x;
	}
};

// Parameter typing example 1 (method template)

class templClass2
{
public:
	template <class T> T some_method(T x)
	{
		// some pointless activity
		return x;
	}
};

// Template specialization

// explicit_specialization1.cpp
// compile with: /EHsc
#include <iostream>
using namespace std;

// Template class declaration and definition
template <class T> class Formatter
{
   T* m_t;
public:
   Formatter(T* t) : m_t(t) { }
   void print()
   {
      cout << *m_t << endl;
   }
};

// Specialization of template class for type char*
template<> // note here the empty template syntax.
class Formatter<char*> // this is a specialization for (char *)
{
   char** m_t;
public:
   Formatter(char** t) : m_t(t) { }
   void print()
   {
      cout << "Char value: " << **m_t << endl;
   }
};




int _tmain(int argc, _TCHAR* argv[])
{
	myTemplClass<char,10> mtc1;
    myTemplClass<int,10> mtc2;
    myTemplClass<myTemplClass<long,4>,10> mtc3;

	templClass2 tc2_a;

	std::cout << "mtc1.getSizeOfSmallAryElement()[" << mtc1.getSizeOfSmallAryElement() << "]" << std::endl;
	std::cout << "mtc1.getSizeOfSmallAry()[" << mtc1.getSizeOfSmallAry() << "]" << std::endl << std::endl;

	std::cout << "mtc2.getSizeOfSmallAryElement()[" << mtc2.getSizeOfSmallAryElement() << "]" << std::endl;
	std::cout << "mtc2.getSizeOfSmallAry()[" << mtc2.getSizeOfSmallAry() << "]" << std::endl << std::endl;

	std::cout << "mtc3.getSizeOfSmallAryElement()[" << mtc3.getSizeOfSmallAryElement() << "]" << std::endl;
	std::cout << "mtc3.getSizeOfSmallAry()[" << mtc3.getSizeOfSmallAry() << "]" << std::endl << std::endl;

	
	std::cout << tc2_a.some_method((int)5) << std::endl << std::endl;

	std::cout << tc2_a.some_method('z') << std::endl << std::endl;

	// test template specialization..

	int i = 157;
	// Use the generic template with int as the argument.
	Formatter<int>* formatter1 = new Formatter<int>(&i);

	char str[10] = "string1";
	char* str1 = str;
	// Use the specialized template.
	Formatter<char*>* formatter2 = new Formatter<char*>(&str1);

	formatter1->print();
	formatter2->print();


	return 0;
}

