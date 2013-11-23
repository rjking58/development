#include <iostream.h>

class Base
{
	public:
	virtual ~Base() = 0;
};

Base::~Base() { cout << "Base" << endl; }

class Derived : public Base
{
	public:
	~Derived() { cout << "Derived" << endl; }
};



void main( void ) 
{
	Base * bp = new Derived;

	delete bp;
}
