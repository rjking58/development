#include <iostream.h>

class X
{
		int		mcode;

	public:

		X(int thecode) :	mcode(thecode)
		{ }

		int getcode()
		{
			return mcode;
		}
};

class Y
{
	public:
		X x;

		Y(): x(7) { }

//		int showmeX()
//		{
//			return x.getcode();
//		}
};

class Z
{
	public:
		X x;
		Z(): x(666) { }
//		int showmeX()
//		{
//			return x.getcode();
//		}
};



main()
{
	X		*x_p;
	int		*i_p;

	Y y;
	Z z;

	// burp...
    *((int *) ((void *) &y)) = 1;
    *((int *) ((void *) &z)) = 2;

	// gag...
	x_p =  (X*) ((void*) &y);

	cout << x_p->getcode() << endl;

	// wretch...
	x_p =  (X*) ((void*) &z);

	cout << x_p->getcode() << endl;
}
