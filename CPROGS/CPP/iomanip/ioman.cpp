#include <iostream.h>
#include <iomanip.h>

void main(void)
{
	// set up for fixed precision so that 
	// 'setprecision' is interpreted the as 'number of
	// decimal numbers'	
	cout << setiosflags(ios::fixed);

	// one number to right of the decimal point
	cout << setprecision(1) ;

   // test it to make sure!
	cout << 1.001 << " " << 1.01 << " " << 1.1 ;
}