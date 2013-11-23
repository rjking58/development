#include <iostream.h>

class B 
{
	public:
		B() { cout << "constructor for B" << endl ;	}
		~B() { cout << "destructor for B" << endl;	}
};

class D : public B
{
	public:
		D() { cout << "constructor for D" << endl ;	}
		~D() { cout << "destructor for D << endl;	}
};

main()
{
	D a_D;


	cout << "hi out there" << endl;
}

