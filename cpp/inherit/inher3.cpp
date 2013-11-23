#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

class  B1
{
	public:
		virtual void 	woof(void) { cout << "B1 woof" << endl; }	
		long	x;
};
class  B2
{
		virtual void	woof(void) {cout << "B2 woof" << endl;}
};

class D1 :  public B1,  public B2
{
	public:
		virtual void	woof(void) {cout << "D1 woof" << endl;}
		char x;
};


main()
{
	D1 a_D1;
	B1 a_B1;
	B2 a_B2;

	B1 * a_B1_p;

	a_B1_p = &a_D1;
	a_B1_p->woof();
	a_B1_p = &a_B1;
   a_B1_p->woof();
//	a_B1_p = &a_B2;		<<<< not legal
//   a_B1_p->woof();		<<<< not legal
						
	cout << "size of D1=" << sizeof(a_D1) << endl;
	cout << "size of B1=" << sizeof(a_B1) << endl;
	cout << "size of B2=" << sizeof(a_B2) << endl;

}


























