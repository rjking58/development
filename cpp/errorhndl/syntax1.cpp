#include <iostream.h>
#include <string.h>

#include <new.h>
#include <stdlib.h>

class MemoryAllocDemo
{

	char * c_arr;
	char * a_c;

	public:
		MemoryAllocDemo()
		{
			// array vs. non array news and deletes...
			c_arr = new char [30];	//array of 30 chars
			a_c	= new char;			//a single char...
			
			strcpy(c_arr,"hi there");
			*a_c = 'a';
		
		}
		~MemoryAllocDemo()
		{
			// always delete an array pointer with array delete
			delete [] c_arr;
			// never delete a single item pointer with an array delete!!!
			delete a_c;
		}


};


// the only purpose of this class is the exercise the bad new handler...
class TooMuchMemory
{	
	private:
		char * a_str;

   public:
		TooMuchMemory()
		{
			a_str = new char[1000000000000000];
		}
		~TooMuchMemory()
		{
			delete [] a_str;		
		}

};

// example bad new handler...
int badnew(size_t size)
{
	cerr << "boy, did you do a bad new" << endl;
	abort();

	return 0; // don't retry ....
}

void main()											
{
	// setup the new error handler...
	// NOTE that MSVC++ uses _set_new_handler and NOT set_new_handler!!!
	_set_new_handler(badnew);

	// instantiate this humongous amount of memory and cause an abort...
	// leave this out unless the program is supposed to crash...
	// TooMuchMemory TMM;


	MemoryAllocDemo	mad,
							*mad_p;



	mad_p = new MemoryAllocDemo;

	delete mad_p;

}
