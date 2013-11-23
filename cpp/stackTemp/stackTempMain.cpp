#include <FCStackTemp.h>
#include <iostream.h>
#include <afx.h>

struct TstStruct : public CObject
{
	TstStruct(int a, int b)
	:	x(a),
		y(b)
	{
	}
	TstStruct()
	:	x(0),
		y(0)
	{
	}
	int	x;
	int	y;

	TstStruct & operator=(const TstStruct &rhs)
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}

		return *this;
	}
};

void main(void)
{
	int a;

	FCStackTempl<int> theIntStack;
	FCStackTempl<TstStruct> theTSStack;

	for (a = 0; a < 200; a++)
	{
		theIntStack.Push(a);
	}

	for (a = 200; a >= 0; a--)
	{
		int b;
		if( FCStackTempl<int>::STACK_EMPTY == theIntStack.Pop(b) )
		{
			cout << "stack is EMPTY" << endl;
		}
		else
		{
			cout << "b = " << b << endl;
		}
	}

	for (a = 0; a < 200; a++)
	{
		TstStruct ts(a,200-a);

		theTSStack.Push(ts);
	}

	for (a = 200; a >= 0; a--)
	{
		TstStruct ts;

		if( FCStackTempl<TstStruct>::STACK_EMPTY == theTSStack.Pop(ts) )
		{
			cout << "stack is EMPTY" << endl;
		}
		else
		{
			cout 	<< "x = " << ts.x 
					<< "y = " << ts.y
					<< endl;

		}
	}
}

