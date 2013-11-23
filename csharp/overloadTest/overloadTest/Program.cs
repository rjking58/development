using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;

namespace overloadTest
{

    class copyable
    {
        private int     m_i;
        private string  m_id;
        public copyable(int i,string id)
        {
            m_i = i;
            m_id = id;
        }

        public copyable clone()
        {
            return new copyable(m_i,"copy of " + m_id);
        }

        public string getID()
        {
            return new string(String.Format("{0} {1}",m_i,m_id).ToCharArray());
        }
    }
    class A
    {
        private copyable m_c;

        public A(int i, string id)
        {
            m_c = new copyable(i,id);
        }

        public copyable GetCopyableClone()
        {
            return m_c.clone();
        }

        public void TargetOfCopy(A some_a)
        {
            Console.WriteLine("A->TargetOfCopy(A some_a) ");
            m_c = some_a.GetCopyableClone();
        }
        public void TargetOfCopy(B some_b)
        {
            Console.WriteLine("A->TargetOfCopy(B some_a) ");
            m_c = some_b.GetCopyableClone();
        }
        public string getID()
        {
            return m_c.getID();
        }

    }
    class B
    {
        private copyable m_c;

        public B(int i, string id)
        {
            m_c = new copyable(i,id);
        }

        public copyable GetCopyableClone()
        {
            return m_c.clone();
        }

        public void TargetOfCopy(A some_a)
        {
            Console.WriteLine("B->TargetOfCopy(A some_a) ");
            m_c = some_a.GetCopyableClone();
        }
        public void TargetOfCopy(B some_b)
        {
            Console.WriteLine("B->TargetOfCopy(B some_a) ");
            m_c = some_b.GetCopyableClone();
        }
        public string getID()
        {
            return m_c.getID();
        }
    }

    [TestFixture]
    public class testOverloads
    {
        private A a1;
        private A a2;
        private A a3;
        private A a4;
        private B b5;
        private B b6;
        private B b7;
        private B b8;

        [SetUp]
        public void Init()
        {
            a1 = new A(1,"A1");
            a2 = new A(2,"A2");
            a3 = new A(3,"A3");
            a4 = new A(4,"A4");
            b5 = new B(5,"B5");
            b6 = new B(6,"B6");
            b7 = new B(7,"B7");
            b8 = new B(8,"B8");
        }
        [Test]
        public void TestAtoA()
        {
            Assert.AreEqual("1 A1",a1.getID());
            Assert.AreEqual("2 A2",a2.getID());
            a2.TargetOfCopy(a1);
            Assert.AreEqual("1 A1", a1.getID());
            Assert.AreEqual("1 copy of A1", a2.getID());

        }
        [Test]
        public void TestAtoB()
        {
            Assert.AreEqual("1 A1",a1.getID());
            Assert.AreEqual("5 B5",b5.getID());
            b5.TargetOfCopy(a1);
            Assert.AreEqual("1 A1", a1.getID());
            Assert.AreEqual("1 copy of A1", b5.getID());
        }
        [Test]
        public void TestBtoA()
        {
            Assert.AreEqual("5 B5",b5.getID());
            Assert.AreEqual("1 A1",a1.getID());
            a1.TargetOfCopy(b5);
            Assert.AreEqual("5 B5", b5.getID());
            Assert.AreEqual("5 copy of B5", a1.getID());
        }
        [Test]
        public void TestBtoB()
        {
            Assert.AreEqual("5 B5",b5.getID());
            Assert.AreEqual("6 B6",b6.getID());
            b6.TargetOfCopy(b5);
            Assert.AreEqual("5 B5", b5.getID());
            Assert.AreEqual("5 copy of B5", b6.getID());
        }


    }
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
