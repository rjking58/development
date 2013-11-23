#include <iostream.h>
#include <math.h>


void main()
{
	double d;
	double new_d;
	double d_exp;
	int x;

	d = 0.0;
	for (x = 1; x <400; x++)
	{
		d += 0.1;

		d_exp = int(log(d) / log( 2 ));	// Block exponent
		if ( pow(2, d_exp) < d )   // need to add one due to
			d_exp++;                        // truncation
		new_d = int(pow(2, d_exp));			// Set block size
		cout << "d=" << d << "   new_d=" << new_d << endl;
	}

}