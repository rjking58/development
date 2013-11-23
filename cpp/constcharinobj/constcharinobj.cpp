
#include <iostream.h>

class A
{
public:
	A()	: mWHEE("whee!!")
	{
	}

	void PrintIt()
	{
		cout << mWHEE << endl;
	}
private:
	const char	*mWHEE;

};



void main()
{
	A a;

	a.PrintIt();
}