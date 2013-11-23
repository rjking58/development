// UnManagedDLLTests.h

#pragma once

using namespace System;
using namespace NUnit::Framework;
using namespace System::Reflection;


namespace UnManagedDLLTests 
{

	[TestFixture]
	public ref class UnManagedTests
	{
	public:
		[TestFixtureSetUp] void TestFixtureSetUp (){;}
		[SetUp] void Init() {;}

		[Test] void SimpleTest();
	};
}
