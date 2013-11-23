
// will compile... we get a default constructor for free here.
class X
{
	// le emptie class.
};

// won't compile... use of parameterized constructor w/o default constructor means
// that default constructor is NOT CREATED.
//class X
//{
//	public:
//		X(int) {  }
//};

main()
{
	X x;
}