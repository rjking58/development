#include <iostream.h>


void const_away(const char * ccp)
{
	// this doesn't work either...
	char * str = ccp;

	ccp[3] = 'a';

}


void main(void)
{

	// constant int
	const i1 = 20;

	// constant pointer that points to constant int
	const int * const i1_p = &i1;

	
	// constant int
	const i2 = 10;
	// pointer that points to constant int
	const int * i2_p = &i2;

	// 
	const char ar[20] = {"12345"};

	const char * ar_p = ar;

	// legal... changing non-constant pointer...
	i2_p = &i1;
	
	// illegal.. changing a constant pointer to a constant int.
 //	i1_p = &i2;

	// oops, illegal!
//	ar_p[3] = 'z';

	const_away(ar_p);

	cout << ar << endl;



}