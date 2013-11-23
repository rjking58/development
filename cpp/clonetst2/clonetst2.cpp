#include <iostream.h>

// example showing how a class that is contained in another 
// class always has its copy constructor called during normal 
// object copy

class ContainedClass
{

public:
	ContainedClass()   
	{
		cout << "ContainedClass::Normal Constructor Call" << endl;
	}

	ContainedClass(ContainedClass& CCref)
	{
		cout << "ContainedClass::**COPY** Constructor Call" << endl;
	}

	ContainedClass& operator=(ContainedClass& CCref)
	{
		cout << "ContainedClass::**assignment** Called" << endl;
		return *this;
	}



	~ContainedClass()
	{
		cout << "ContainedClass::Normal Destructor Call" << endl;
	}

	void Printi()
	{
		cout << i << endl;
	}

private:
	int i;
};

class BaseClass
{
public:
	BaseClass() 
	{
		cout << "BaseClass::Normal Constructor Call" << endl;
	}

	BaseClass(BaseClass &bcr)
	{
		CCobj = bcr.CCobj;
	}
	virtual ~BaseClass()
	{
		cout << "BaseClass::Normal Destructor Call" << endl;
	}
	virtual BaseClass* Clone() = 0;
private:
	ContainedClass CCobj;
};

class SubClass : public BaseClass
{
public:
	SubClass() 
	{
		cout << "SubClass::Normal Constructor Call" << endl;
	}
	~SubClass()
	{
		cout << "SubClass::Normal Destructor Call" << endl;
	}
	virtual BaseClass* Clone()
	{

		cout << "SubClass::Clone Call" << endl;
		return new SubClass(*this);
	}
private:
	int i;
};

void main(void)
{
	SubClass sc1;
	SubClass sc2 = sc1;
	SubClass *p_sc3;
		
	p_sc3 = (SubClass *)sc1.Clone();

}