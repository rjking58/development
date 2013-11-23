#include <iostream.h>
#include <string.h>

// example template that intermixes generic function and 
// specialized function creation 


// template class passing one type...

template <class T> class MySpecialClass
{
	public:
	MySpecialClass();
	~MySpecialClass();
	void PrintAVal();

	private:

		T a_thing;
};

// special versions covering all aspects of possible templated classes
// NOTICE: absence of 'template <class T>' syntax. indicating a 
// specialiation
MySpecialClass<int>::MySpecialClass()
{
	a_thing = 22;
}
MySpecialClass<char *>::MySpecialClass()
{
	a_thing = new char[10];
	strcpy(a_thing,"whee");
}

MySpecialClass<char *>::~MySpecialClass()
{
	delete [] a_thing;
}
MySpecialClass<int>::~MySpecialClass()
{
	
}

// functions that need no specialization...
// here we use 'template <class T>' before the function def so that 
// the type used in class construction is passed in..
template <class T> void MySpecialClass<T>::PrintAVal()
{
	cout << "a_thing:" << a_thing << endl;
}


//void MySpecialClass<int>::PrintAVal()
//{
//	cout << "Integer version:" << a_thing << endl;
//}
//
//void MySpecialClass<char *>::PrintAVal()
//{
//	cout << "Char * version:" << a_thing << endl;
//}


void main(void)
{
	MySpecialClass<int>		MySpecialIntObj;
	MySpecialClass<char *>	MySpecialCharStarObj;
	// MySpecialClass<double>  MySpecialDoubleObj;	// should cause error...


	MySpecialIntObj.PrintAVal();
	MySpecialCharStarObj.PrintAVal();
}