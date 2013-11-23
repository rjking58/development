#include <iostream.h>


void f1();
void f2();


void main()

{
	void (*p_f[20]) ()  ;
	void (*p_oneF) ();

	p_f[0] = f1;
	p_f[1] = f2;
	p_oneF = f1;

	(*p_f[0])();


	(*p_f[1])();

	(*p_oneF)();

	cout << "end" << endl;

}

void f1()
{
	cout << "f1" << endl;
}

void f2()
{
	cout << "f2" << endl;
}