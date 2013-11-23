#include <iostream.h>

unsigned int a = 0;

class Cl
{
	int m_i;
	Cl() { }
public:
	Cl (int i) : m_i(i) { } 
	int GetI() { return m_i; }
};


int tester()
{
	return (int) a;
}


void main(void)
{
	Cl cl1(1);
	Cl cl2(2);

	cl1 = cl2;

	cout << cl1.GetI() << " " << cl2.GetI() << endl;

	for (a = 0 ; a<64000 ; a++)
	if (!tester())
	{
		cout << "true side of if #1" << "a=" << a << " !a=" << (!a) << endl;
	}
	else
	{
//		cout << "false side of if #1" << "a=" << a << " !a=" << (!a) << endl;
	}
	a++;

}
