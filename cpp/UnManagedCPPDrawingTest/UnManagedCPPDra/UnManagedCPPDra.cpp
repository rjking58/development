// UnManagedCPPDra.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


namespace Test1
{
	class TestClass 
	{
	public:
		void Method1();
		int Method2(int i);
		bool Method3();
	};
	void TestClass::Method1()
	{
	}
	int TestClass::Method2(int i)
	{
		return 1;
	}
	bool TestClass::Method3()
	{
		return true;
	}

	class TestDerivedClass : public TestClass
	{
		void Method4();
	};

	void TestDerivedClass::Method4()
	{
	}


}


