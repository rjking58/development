// bases.h....
// class used as basic classes for manipulation in Design Patterns

class AbBaseX
{
	public:
		AbBaseX()
		{ }
		AbBaseX(int x)
		{ }

		virtual void ImHere() = 0;

};

class Derived1X : public AbBaseX
{
	public:
		Derived1X(int obj_num) 
		{ 
			mObj_Num = obj_num;
		}

		virtual void ImHere()
		{
			cout 
				<< "object " 
				<< mObj_Num 
				<< " of Derived1X here..." 
				<< endl;
		}

	private:
		int	mObj_Num;

};
class Derived2X : public AbBaseX
{
	public:
		Derived2X(int obj_num) 
		{ 
			mObj_Num = obj_num;
		}

		virtual void ImHere()
		{
			cout 
				<< "object " 
				<< mObj_Num 
				<< " of Derived2X here..." 
				<< endl;
		}

	private:
		int	mObj_Num;

};

class AbBaseY
{
	public:
		AbBaseY()
		{ }
		AbBaseY(int x)
		{ }

		virtual void ImHere() = 0;

};

class Derived1Y : public AbBaseY
{
	public:
		Derived1Y(int obj_num) 
		{ 
			mObj_Num = obj_num;
		}

		virtual void ImHere()
		{
			cout 
				<< "object " 
				<< mObj_Num 
				<< " of Derived1Y here..." 
				<< endl;
		}

	private:
		int	mObj_Num;

};
class Derived2Y : public AbBaseY
{
	public:
		Derived2Y(int obj_num) 
		{ 
			mObj_Num = obj_num;
		}

		virtual void ImHere()
		{
			cout 
				<< "object " 
				<< mObj_Num 
				<< " of Derived2Y here..." 
				<< endl;
		}

	private:
		int	mObj_Num;

};
