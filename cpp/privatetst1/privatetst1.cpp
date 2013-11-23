#include <iostream.h>
#include <string.h>

// demonstration of principal that ALL objects of the same class have 
// access to each others private data.

class MyClass
{
private:

	int		m_number;	 
	char		*m_name;

public:
	MyClass(int number, char * name): m_number(number)
	{
		m_name = new char[(strlen(name)+1)];
		strcpy(m_name,name);
	}
	virtual ~MyClass()
	{
		delete m_name;
	}
	void PrintOtherNumber(MyClass * MyClassObj)
	{
		cout	<< m_name 
				<< " is printing " 
				<< MyClassObj->m_name
				<< "'s number:" 
				<< MyClassObj->m_number
				<< endl;
	}
};

void main(void)
{
	MyClass Obj1(1,"Obj1"),Obj2(2,"Obj2");
	
	Obj1.PrintOtherNumber(&Obj2);
	 
}
