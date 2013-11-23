#include <iostream.h>

class Base
{
public:
  	Base() : i(1)
	{
	}
	void BaseOnly()
	{
		cout << "BaseOnly(" << i << ")" << endl;
	}

	void BaseCallHidden()
	{
		cout << "BaseCallHidden calls::" ;
  		Hidden();
	}

	void BaseCallVirt()
	{
		cout << "BaseCallVirt calls::" ;
  		Virt();
	}

	virtual void Virt()
	{
  		cout << "Base::Virt() (" << i << ")" << endl;
	}

	void Hidden()
	{
  		cout << "Base::Hidden() (" << i << ")" << endl;
	}
private:

	int	i;
};

class Deriv : public Base
{
public:
	Deriv() : i(2)
	{
	}
	void DerivCallHidden()
	{
		cout << "DerivCallHidden calls::" ;
  		Hidden();
	}

	void DerivCallBaseOnly()
	{
		cout << "DerivCallBaseOnly calls::";
		BaseOnly();
	}

	virtual void Virt()
	{
  		cout << "Deriv::Virt() (" << i << ")" << endl;
	}

	void Hidden()
	{
  		cout << "Deriv::Hidden() (" << i << ")" << endl;
	}
private:

	int 	i;
};

void main()
{

	Base 		b;
	Deriv 	d;

	cout << "Base calls:" << endl;
	cout << "========================" << endl;
	b.BaseOnly();
	b.BaseCallHidden();
	b.BaseCallVirt();

	cout << "Deriv calls:" << endl;
	cout << "========================" << endl;
	d.BaseOnly();
	d.BaseCallHidden();
	d.DerivCallHidden();
	d.DerivCallBaseOnly();
	d.BaseCallVirt();

}