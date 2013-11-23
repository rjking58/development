#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

class  B1
{
	public:
	B1()
	{
		cout << "constructor for B1" << endl;
	}
	virtual ~B1() 	// the virtual must be here to work correctly
						// if this is removed then the compiler generates its own 
						// destructors and bypasses all destructors in the heirarchy.
	{
		cout << "destructor for B1" << endl;
	}
	virtual void woof_woof() = 0;
};

class D1 : public B1
{
	public:
	D1()
	{
		cout << "constructor for D1" << endl;
	}
	~D1()
	{
		cout << "destructor for D1" << endl;
	}
	virtual void woof_woof()
	{
		cout << " D1 says: woof woof " << endl;
	}

};

class D2 : public D1
{
	public:
	D2()
	{
		cout << "constructor for D2" << endl;
	}
	~D2()
	{
		cout << "destructor for D2" << endl;
	}
	virtual void woof_woof()
	{
		cout << " D2 says: woof woof " << endl;
	}
};

main()
{
	B1 *a_B1_p;
	B1 *a_B1_p2;

	a_B1_p = new D1;
	a_B1_p2 = new D2;

	a_B1_p->woof_woof();
	a_B1_p2->woof_woof();

	delete a_B1_p;
	delete a_B1_p2;

}
