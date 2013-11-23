// bases2.h....
// class used as basic classes for manipulation in Design Patterns

class AbBaseX
{
	public:
		AbBaseX()
		{ }
		virtual void Initialize(int x)
		{ }

		virtual void ImHere() = 0;

		virtual AbBaseX *Clone(void) = 0;

};

class Derived1X : public AbBaseX
{
	public:
		Derived1X() 
		{ 
		}
		// copy constructor
		Derived1X( Derived1X &d1xRef) 
		{ 
			mObj_Num = d1xRef.mObj_Num;
		}


		void Initialize(int obj_num)
		{
			mObj_Num = obj_num;
		}
		AbBaseX *Clone()
		{
			return new Derived1X(*this);
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
		Derived2X() 
		{ 
		}
		// copy constructor
		Derived2X( Derived2X &d2xRef) 
		{ 
			mObj_Num = d2xRef.mObj_Num;
		}


		void Initialize(int obj_num)
		{
			mObj_Num = obj_num;
		}

		AbBaseX *Clone()
		{
			return new Derived2X(*this);
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
		virtual void Initialize(int x)
		{ }

		virtual void ImHere() = 0;

		virtual AbBaseY *Clone(void) = 0;


};

class Derived1Y : public AbBaseY
{
	public:
		Derived1Y() 
		{ 
		}
		// copy constructor
		Derived1Y( Derived1Y &d1yRef) 
		{ 
			mObj_Num = d1yRef.mObj_Num;
		}


		void Initialize(int obj_num)
		{
			mObj_Num = obj_num;
		}
		AbBaseY *Clone()
		{
			return new Derived1Y(*this);
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
		Derived2Y() 
		{ 	   
		}
		// copy constructor
		Derived2Y( Derived2Y &d2yRef) 
		{ 
			mObj_Num = d2yRef.mObj_Num;
		}


		void Initialize(int obj_num)
		{
			mObj_Num = obj_num;
		}
		AbBaseY *Clone()
		{
			return new Derived2Y(*this);
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
