#include <iostream.h>




class base_C1
{
	public:
		base_C1() {}      						            // default constructor...
		base_C1 (int BasePrivInt)  			            // pass in a value to initialize private...
		{ 
			mbaseC1PublicInt 	= 0;				            // set up public by default...
			mBasePrivInt 		= BasePrivInt;
		}
		virtual int GetPublicInt() 
		{ 
			return mbaseC1PublicInt; 
		}
		virtual int GetPrivateInt() 
		{ 
			return mBasePrivInt; 
		}
		int	mbaseC1PublicInt;
	private:
		int	mBasePrivInt;
};


class derive_C1 : public base_C1
{
	public:
		derive_C1() {}                      				// default constructor...
		derive_C1(int BasePrivInt,int DerivedC1Int) 
					: 	mderivedC1Int(DerivedC1Int),    		// initializer
						base_C1(BasePrivInt)  					// base class constructor
		{ 
			mbaseC1PublicInt = 9;	// the actual function body!
		}
		int GetPrivateInt() 
		{ 
			return mderivedC1Int; 
		}

	private:
		int	mderivedC1Int;
		
};


main()
{
	base_C1 obj_bC1(1);
	derive_C1 obj_dC1(2,3);
	derive_C1 obj_x;

	int 		x;
	int		y = 0;

	for (x = 0; x< 10; x++)
	{
		y = x;
	}

	cout 	<< "obj_bC1.GetPublicInt("
			<< obj_bC1.GetPublicInt()
			<< ")"
			<< "obj_bC1.GetPrivateInt("
			<< obj_bC1.GetPrivateInt() 
			<< ")"
			<< endl;
	cout 	<< "obj_dC1.GetPublicInt("
			<< obj_dC1.GetPublicInt()
			<< ")"
			<< "obj_dC1.GetPrivateInt("
			<< obj_dC1.GetPrivateInt() 
			<< ")"
			<< endl;
}
