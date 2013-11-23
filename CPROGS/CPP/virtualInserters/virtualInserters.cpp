#include <iostream.h>

// this setup shows use of base class inserter
// for generalized use by all subclasses.  

// it involves using a virtual method that 
// takes the ostream and inserts its own
// stuff into it.  

class Base
{
	private:
		int	base_i;	

	public:
		// our virtual method that can be called from
		// ostream operator<< method.
		// const so that we can call w/ const objects.
		virtual void Inserter(ostream &s) const 
		{
			s << "[Base::" << "base_i = " << base_i << "]";
		}
		Base(	int	i) 
			: base_i(i) 
		{ 
		}
		
};

class Deriv : public Base
{
	private:
		int	deriv_i;	//real part

	public:
		// our virtual method that can be called from
		// ostream operator<< method.
		// const so that we can call w/ const objects.
		virtual void Inserter(ostream &s) const
		{
			s << "[Deriv::" << "deriv_i = " << deriv_i << "]";
			
			Base::Inserter(s);
		}
		Deriv(int bi,int	di) 
			: 	Base(bi),
				deriv_i(di) 
		{ 
		}

};

class Deriv2 : public Deriv
{
	private:
		int	deriv2_i;	//real part

	public:
		// our virtual method that can be called from
		// ostream operator<< method.
		// const so that we can call w/ const objects.
		virtual void Inserter(ostream &s) const
		{
			s << "[Deriv2::" << "deriv2_i = " << deriv2_i << "]";
			
			Deriv::Inserter(s);
		}
		Deriv2(int bi,int	di, int d2i) 
			: 	Deriv(bi,di),
				deriv2_i(d2i) 
		{ 
		}

		
};


ostream& operator<<(ostream &s, const Base &b_obj)
{
	// call virtual method..
	b_obj.Inserter(s);

	// normal return from inserter.
	return s;
}

void main()
{
	Base 	a_base1(1);
	Base 	a_base2(2);
	Deriv	a_deriv1(3,30);
	Deriv	a_deriv2(4,40);
	Deriv2	a_deriv3(5,50,500);
	Deriv2	a_deriv4(6,60,600);

	cout << "a_base1 >>> " << a_base1 << " <<<" << endl;
	cout << "a_base2 >>> " << a_base2 << " <<<" << endl;
	cout << "a_deriv1 >>> " << a_deriv1 << " <<<" << endl;
	cout << "a_deriv2 >>> " << a_deriv2 << " <<<" << endl;
	cout << "a_deriv3 >>> " << a_deriv3 << " <<<" << endl;
	cout << "a_deriv4 >>> " << a_deriv4 << " <<<" << endl;
}

