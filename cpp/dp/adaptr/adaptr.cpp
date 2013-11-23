#include <iostream.h>

// Adapter... adapt a desired implementation to an existing interface.
// This example uses multiple inheritance to achieve the goal.

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

// NOTE:	adapter inherits its interface publicly, and its
//			implementation privately...
class Adapter : public DesiredInterface, private DesiredImplementation
{
public:
	virtual void SetSides(int x_inch, int y_inch)	
	{ 
		cout << "Adapter::SetSides ENTER" << endl;
		SetSize( x_inch*y_inch );
		cout << "Adapter::SetSides EXIT" << endl;
	}

	virtual int GetSize()
	{
		cout << "Adapter::GetSize ENTER/EXIT" << endl;
		return DesiredImplementation::GetSize();
	}	
};

void main(void)
{
	Adapter a;

	a.SetSides(2,4);

	cout << a.GetSize() << endl;
}