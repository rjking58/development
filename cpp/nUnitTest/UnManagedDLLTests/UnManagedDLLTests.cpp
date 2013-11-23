// This is the main DLL file.

#include "stdafx.h"
#include "..\UnManagedDLL\UnManagedDLL.h"
#include "..\UnManagedDLL\SMSingleton.h"
#include "UnManagedDLLTests.h"


namespace UnManagedDLLTests 
{
	void UnManagedTests::SimpleTest()
	{
		Assert::IsTrue(true);

		//TestClass &tc = TestClass::instance();

		TestClass::instance().SetVal(10);
		Assert::AreEqual(10,TestClass::instance().GetVal());
		TestClass::instance().SetVal(20);
		Assert::AreEqual(20,TestClass::instance().GetVal());
		TestClass::instance().SetVal(30);
		Assert::AreEqual(30,TestClass::instance().GetVal());

	}
}

