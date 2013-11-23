// UnManagedTests2.h

#pragma once

using namespace System;
using namespace NUnit::Framework;
using namespace System::Reflection;


namespace UnManagedDLLTests2
{

	[TestFixture]
	public ref class UnManagedTests2
	{
	public:
		[TestFixtureSetUp] void TestFixtureSetUp (){;}
		[SetUp] void Init() {;}

		[Test] void SimpleTest();

		[Test] void AnotherTest();
	};
}
