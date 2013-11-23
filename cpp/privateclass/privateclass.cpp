#include <iostream.h>


class Outer
{
public:
	void Action();
private:
	class Inner
	{
	public:
		void Action();
	};

	Inner mInnerObj;
};

void Outer::Action()
{
	mInnerObj.Action();
}

void Outer::Inner::Action()
{
	cout << "we got there!" << endl;
}

void main()
{
	Outer OuterObj;

	OuterObj.Action();
}