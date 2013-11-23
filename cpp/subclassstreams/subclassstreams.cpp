
#include <strstrea.h>
#include <iomanip.h>

class Base
{
public:
	Base(int i)
		:	mI(i)
	{
	}
	virtual void Dump( ostream &str );
	friend ostream& operator<<(ostream &Strm, Base * b_r);
	friend ostream& operator<<(ostream &Strm, Base & b);

protected:
	int mI;
};

class Deriv : public Base
{
public:
	Deriv()
		:	Base(2),
			mJ(99)
	{
	}

	virtual void Dump( ostream &str );

private:
	int mJ;
};


//ostream& operator<<(ostream &Strm, Base * b_p)
//{
//	if (Strm.opfx())
//	{  
//		b_p->Dump(Strm);
//	}
//	Strm.osfx();
//									
//	return Strm;
//
//}

ostream& operator<<(ostream &Strm, Base & b)
{
	if (Strm.opfx())
	{  
		b.Dump(Strm);
	}
	Strm.osfx();
									
	return Strm;

}



void Base::Dump( ostream &str )
{
	str << "Base Dump" << mI << endl;
}
void Deriv::Dump( ostream &str )
{
	str << "Deriv Dump" << mI << mJ << endl;
}



void main()	// void so VC++ doesn't BARK at us
{
	Base b(1);
	Deriv d;

	Base *b_p = new Deriv;

//	cout << b << d << b_p << *b_p;
	cout << b << d << *b_p;
//	b.Dump(cout);
//	d.Dump(cout);
//	b_p->Dump(cout);

}