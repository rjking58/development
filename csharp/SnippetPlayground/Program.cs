using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace SnippetPlayground
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("hello world!");
            Console.WriteLine("werble");
            Console.WriteLine("Hello World!"); Console.WriteLine("gorp");
            Console.WriteLine("Hello World!"); Console.WriteLine("Yo!");

            
            Console.WriteLine("one two");
            Console.WriteLine("three four");
        }

    }
    //SnipNUnitTestFile
    [TestFixture]
    public class BasicKeyEntry_Tests
    {
        [TestFixtureSetUp]
        public void TestFixtureSetUp()
        {
        }

        [SetUp]
        public void Setup()
        {
        }

        [TestFixtureTearDown]
        public void TestFixtureTearDown()
        {
        }

        [TearDown]
        public void Teardown()
        {
        }

        [Test]
        public void MyTest()
        {
        }
    }
       
}
