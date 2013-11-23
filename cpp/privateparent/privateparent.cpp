#include <iostream.h>

class Base
{


protected:
	Base(int i): m_i(i)
	{
	}



	int m_i;

private:
	Base();

};

class Derived1 : public Base
{

public:
	Derived1(int i,int j) : Base(i), m_j(j)
	{
	}
	
	void DoAction()
	{
	  	cout << m_i << " " << m_j << endl;
	}
private:
	int m_j;	 
};

//class Derived2 : public Base
//{
//
//public:
//	Derived2(int i,int j) : m_j(j)
//	{
//	}
//	
//	void DoAction()
//	{
//	  	cout << m_i << " " << m_j << endl;
//	}
//private:
//	int m_j;	 
//};



void main(void)
{
	Derived1 d1(2,2);
	Derived1 d2(3,3);
	Derived1 d3(4,4);
	Derived1 d4(11,232);
//	Derived2 d2_1(6,6);
	
	d1.DoAction();
	d2.DoAction();
	d3.DoAction();
	d4.DoAction();
}

