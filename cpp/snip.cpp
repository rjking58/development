#include <iostream.h>

class A
{
public:
	A(int i, int j, int k) {  cout << "1";   A a(i,j); }
	A(int i, int j) { cout << "2";  A a(i); }
	A(int i) { cout << "3"; A a; }    /* calls the default constructor! */
	A() { cout << "...boom!" << endl; }
};

int
main()
{
	A  apple(0,0,0);
	A  x;
	return 0;
}
