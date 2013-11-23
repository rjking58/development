#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\VS2012UnitTestTesting\VS2012UnitTestTesting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestExample1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ExampleSubsystem_VS2012UnitTestTesting_DefaultConstructor)
		{
			// TODO: Your test code here
            ClassUnderTest cut;

            Assert::AreEqual(0,cut.GetI());
		}

		TEST_METHOD(ExampleSubsystem_VS2012UnitTestTesting_SingleIntConstructor)
		{
			// TODO: Your test code here
            ClassUnderTest cut(1);
            Assert::AreEqual(1,cut.GetI());

            ClassUnderTest cut2(2);
            Assert::AreEqual(2,cut2.GetI());

            ClassUnderTest cut3(100);
            Assert::AreEqual(100,cut3.GetI());

		}

		TEST_METHOD(ExampleSubsystem_VS2012UnitTestTesting_SetAndGet)
		{
			// TODO: Your test code here
            ClassUnderTest cut;
            Assert::AreEqual(0,cut.GetI());

            for(int x = 0; x < 2000; x++)
            {
                
                cut.SetI(x);
                Assert::AreEqual(x,cut.GetI());
            }
		}

	};
}