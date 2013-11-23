#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace SimpleUTest
{
	[TestClass]
	public ref class SimpleUTest1
	{
	public: 
		[TestMethod]
		void TestMethod1()
		{
            Assert::AreEqual(true,false);
		}
	};
}
