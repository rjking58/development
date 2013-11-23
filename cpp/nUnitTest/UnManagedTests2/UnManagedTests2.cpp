// This is the main DLL file.

#include "stdafx.h"
#include "..\UnManagedDLL\UnManagedDLL.h"
#include "UnManagedTests2.h"
#include "..\UnManagedDLL\SMSingleton.h"

namespace UnManagedDLLTests2
{
	void UnManagedTests2::SimpleTest()
	{
		Assert::IsTrue(true);


		TestClass::instance().SetVal(10);
		Assert::AreEqual(10,TestClass::instance().GetVal());
		TestClass::instance().SetVal(20);
		Assert::AreEqual(20,TestClass::instance().GetVal());
		TestClass::instance().SetVal(30);
		Assert::AreEqual(30,TestClass::instance().GetVal());

	}
	void UnManagedTests2::AnotherTest()
	{

		Assert::IsTrue(false);
	}
}

