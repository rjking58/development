#include <iostream.h>

// Adapter... adapt a desired implementation to an existing interface.
// This example uses object composition to achieve the goal...

class DesiredImplementation
{
private:
	int m_square_inches;
public:
	void SetSize(int square_inches)
	{
		cout << "DesiredImplementation::SetSize ENTER" << endl;
		m_square_inches = square_inches;
		cout << "DesiredImplementation::SetSize EXIT" << endl;
	}
	int GetSize()
	{
		cout << "DesiredImplementation::GetSize ENTER/EXIT" << endl;
		return m_square_inches;
	}
};


class DesiredInterface
{
private:
	int	m_x_inch;
	int	m_y_inch;

public:

	virtual void SetSides(int x_inch, int y_inch)
	{
		cout << "DesiredInterface::SetSides ENTER" << endl;
		m_x_inch = x_inch;
		m_y_inch = y_inch;
		cout << "DesiredInterface::SetSides EXIT" << endl;
	}

	virtual int GetSize()
	{
		cout << "DesiredInterface::GetSize ENTER/EXIT" << endl;
		return (m_x_inch * m_y_inch);
	}	

};

// NOTE:	The adapter publicly inherits its interface and then
//			is passed the implementation object during object
//			construction.
class Adapter : public DesiredInterface
{
	DesiredImplementation *m_DesiredImplementationObject;
public:
	Adapter(DesiredImplementation *DesiredImplementationObject) :
		m_DesiredImplementationObject(DesiredImplementationObject)
	{
	}

	virtual void SetSides(int x_inch, int y_inch)	
	{ 
		cout << "Adapter::SetSides ENTER" << endl;
		m_DesiredImplementationObject->SetSize( x_inch*y_inch );
		cout << "Adapter::SetSides EXIT" << endl;
	}

	virtual int GetSize()
	{
		cout << "Adapter::GetSize ENTER/EXIT" << endl;
		return m_DesiredImplementationObject->GetSize();
	}	
};

void main(void)
{
	DesiredImplementation	DImp;
	Adapter					a(&DImp);

	a.SetSides(5,4);

	cout << a.GetSize() << endl;
}