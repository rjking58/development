#include <iostream.h>

// bridge... decouple an abstracted interface from implementation..


class AbstractImplementation
{
public:
	virtual void impaction1(void) = 0;
	virtual void impaction2(void) = 0;
	
};

class ConcreteImpl1 : public AbstractImplementation
{
	void impaction1(void)
	{
		cout << "implementation 1 / action 1" << endl;
	}
	void impaction2(void)
	{
		cout << "implementation 1 / action 2" << endl;
	}
};

class ConcreteImpl2 : public AbstractImplementation
{
	void impaction1(void)
	{
		cout << "implementation 2 / action 1" << endl;
	}
	void impaction2(void)
	{
		cout << "implementation 2 / action 2" << endl;
	}
};

class Interface
{
	AbstractImplementation	*m_implementation;

	Interface() { }
public:
	Interface(AbstractImplementation *implementation) :
			m_implementation(implementation) { }

	virtual ~Interface()
	{
		delete m_implementation;
	}

	void action1( void )
	{
		m_implementation->impaction1();
	}
	void action2( void )
	{
		m_implementation->impaction2();
	}
};

void main(void)
{
	ConcreteImpl1	ci1;
	ConcreteImpl2	ci2;
	Interface		*interface_p;
	int				i;

	for(i = 1; i <=2 ; i++)
	{
		switch(i)
		{
		case 1:
			interface_p = new Interface( new ConcreteImpl1 );
			break;

		case 2:
			interface_p = new Interface( new ConcreteImpl2 );
			break;
		}

		interface_p->action1();
		interface_p->action2();

		delete interface_p;
	}


}
