#include <iostream.h>


class ComplexInt
{
	private:
		int	r;	//real part
		int	i;	//imaginary part
	public:
		ComplexInt(	int	realPart = 0,
						int	imagPart = 0	): r(realPart),i(imagPart) { };

		friend ostream& operator<<(ostream &s, const ComplexInt &ci);
};


ostream& operator<<(ostream &s, const ComplexInt &ci)
{
	s << ci.r;	// output real part

	// print proper sign based on imaginary part sign...
	if(ci.i >= 0)
	{
		s << "+";
	}
	else
	{
		s << "-";
	}

	s << ci.i << "i";

	return s;
}

void main()
{
	ComplexInt a_CI(2,3);

	cout << "a_CI = " << a_CI << endl;
}