
#include <iostream.h>

class A
{
public:
	A () { cout << "construct A" << endl; }
	~A () { cout << "destruct A" << endl; }
};

class B	: public A
{
public:
	B () { cout << "construct B" << endl; }
	~B () { cout << "destruct B" << endl; }

};

class C : public B
{
public:
	C () { cout << "construct C" << endl; }
	~C () { cout << "denstruct C" << endl; }

};

void main(void)
{
	C aC;

	cout << "wee" ;
}