using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;

namespace TestnUnit
{
    class myClass
    {
        private int m_Result;
        static void Main(string[] args)
        {
        }
        
        public int Result
        {
            get
            {
                return m_Result;
            }
        }
        public void AddNums(int a, int b)
        {
            m_Result = a + b;
        }
        public void MultNums(int a, int b)
        {
            m_Result = a * b;
        }
        public void SubNums(int a, int b)
        {
        }


    }
    [TestFixture]
    public class TestMyClass
    {
        myClass tstClss;

        [SetUp]
        public void Init()
        {
            tstClss = new myClass();
        }
        [Test]
        public void TestAddSimple()
        {
            tstClss.AddNums(10,10);
            Assert.AreEqual(tstClss.Result, 20);
        }
        [Test]
        public void TestMultSimple()
        {
            tstClss.MultNums(10, 10);
            Assert.AreEqual(tstClss.Result, 100);
        }  
        
    }
    
}




