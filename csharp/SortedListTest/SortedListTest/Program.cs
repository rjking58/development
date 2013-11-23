using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;

namespace SortedListTest
{

    class ContainedClass
    {
        private uint m_GenericKeyID;
        private uint m_HardKeyID;
        public  ContainedClass(uint gkid, uint hkid)
        {
            m_GenericKeyID = gkid;
            m_HardKeyID    = hkid;   
        }
        public  uint GenericKeyID
        {
            get
            {
                return m_GenericKeyID;
            }
        }
        public  uint HardKeyID
        {
            get
            {
                return m_HardKeyID;
            }
        }
    }
    class Program
    {
        //                key ,value                                   key , value
        static SortedList<uint,ContainedClass> keymap = new SortedList<uint,ContainedClass>();

        static void Main(string[] args)
        {
            ContainedClass cc = new ContainedClass(444,1);
            addElement(cc);
            addElement(cc);
            cc = new ContainedClass(333,3);
            addElement(cc);
            addElement(cc);
            cc = new ContainedClass(222,5);
            addElement(cc);
            addElement(cc);
            cc = new ContainedClass(111,7);
            addElement(cc);
            addElement(cc);

            for(uint i = 0; i < 50; i++)
            {
                if(keymap.ContainsKey(i))
                {
                    Console.WriteLine("HKID({0}), GKID({1})",keymap[i].HardKeyID,keymap[i].GenericKeyID);
                }
            }

        }

        static void addElement(ContainedClass cc)
        {
            if(keymap.ContainsKey(cc.HardKeyID))
            {
                Console.WriteLine("oops.. already there..");
            }
            else
            {   
                //         key         ,value
                keymap.Add(cc.HardKeyID,cc);
            }
        }
    }
    
    [TestFixture]
    public class SortedListTests
    {
        SortedList<uint,ContainedClass> keymap;
        [SetUp]
        public void Init()
        {
            keymap = new SortedList<uint, ContainedClass>();
        }
        [TearDown]
        public void Dispose()
        {
    
        }
        [Test]
        public void MultipleInsertOfSameElementTest()
        {
            // version hist:
            //    1.0 2/21 @ 2pm
            //    1.1 2/21 @ 2:04pm changed addElement
            DateTime chgTime = new DateTime(2007,2,21,14,04,0);
            uint maj_v = 1;
            uint min_v = 1;

            Console.WriteLine("::::::::::::::::::::::::::::::::::::::::::::::");
            Console.WriteLine("MultipleInsertOfSameElementTest() v{0}.{1} {2}", maj_v, min_v,chgTime);

            ContainedClass cc = new ContainedClass(444, 1);
            addElement(cc);
            addElement(cc);
            // should only be one..
            Assert.IsTrue(keymap.Count == 1,"failed: keymap.Count == 1");
            Assert.IsTrue(keymap[1].HardKeyID == 1,"failed: keymap[1].HardKeyID == 1");
            Assert.IsTrue(keymap[1].GenericKeyID == 444,"failed: keymap[1].GenericKeyID == 444");

        }
        [Test]
        public void MultipleInsertOfSameKeyTest()
        {
            // version hist:
            //    1.0 2/21 @ 2pm
            //    1.1 2/21 @ 2:04pm changed addElement
            DateTime chgTime = new DateTime(2007, 2, 21, 14, 04, 0);
            uint maj_v = 1;
            uint min_v = 1;
            Console.WriteLine("::::::::::::::::::::::::::::::::::::::::::::::");
            Console.WriteLine("MultipleInsertOfSameKeyTest() v{0}.{1} {2}", maj_v, min_v,chgTime);
            
            ContainedClass cc = new ContainedClass(444, 1);
            ContainedClass cc1 = new ContainedClass(555,1);
            addElement(cc);
            addElement(cc1);
            // should only be one..
            Assert.IsTrue(keymap.Count == 1,"failed: keymap.Count == 1");
            Assert.IsTrue(keymap[1].HardKeyID == 1,"failed: keymap[1].HardKeyID == 1");
            Assert.IsTrue(keymap[1].GenericKeyID == 444,"failed: keymap[1].GenericKeyID == 444");
            Assert.IsFalse(keymap[1].GenericKeyID == 555,"failed: keymap[1].GenericKeyID == 555");


        }
        [Test]
        public void SparseKeyTest()
        {
            // version hist:
            //    1.0 2/21 @ 2pm
            //    1.1 2/21 @ 2:04pm changed addElement
            DateTime chgTime = new DateTime(2007, 2, 21, 14, 04, 0);
            uint maj_v = 1; 
            uint min_v = 1;
            Console.WriteLine("::::::::::::::::::::::::::::::::::::::::::::::");
            Console.WriteLine("SparseKeyTest() v{0}.{1} {2}", maj_v, min_v,chgTime);
            
            ContainedClass cc = new ContainedClass(444,1);
            addElement(cc);
            cc = new ContainedClass(333,3);
            addElement(cc);
            cc = new ContainedClass(222,5);
            addElement(cc);
            cc = new ContainedClass(111,7);
            addElement(cc);
            // should only be one..

            Assert.AreEqual(keymap.Count,4,"failed: keymap.Count == 4");
            Assert.IsFalse(keymap.ContainsKey(0),"failed keymap.ContainsKey(0)");
            Assert.IsFalse(keymap.ContainsKey(2),"failed keymap.ContainsKey(2)");
            Assert.IsFalse(keymap.ContainsKey(4),"failed keymap.ContainsKey(4)");
            Assert.IsFalse(keymap.ContainsKey(6),"failed keymap.ContainsKey(6)");
            Assert.IsFalse(keymap.ContainsKey(8),"failed keymap.ContainsKey(8)");
            Assert.AreEqual(keymap[1].HardKeyID    ,     1,"failed: keymap[1].HardKeyID    ,     1");
            Assert.AreEqual(keymap[1].GenericKeyID ,   444,"failed: keymap[1].GenericKeyID ,   444");
            Assert.AreEqual(keymap[3].HardKeyID    ,     3,"failed: keymap[3].HardKeyID    ,     3");
            Assert.AreEqual(keymap[3].GenericKeyID ,   333,"failed: keymap[3].GenericKeyID ,   333");
            Assert.AreEqual(keymap[5].HardKeyID    ,     5,"failed: keymap[5].HardKeyID    ,     5");
            Assert.AreEqual(keymap[5].GenericKeyID ,   222,"failed: keymap[5].GenericKeyID ,   222");
            Assert.AreEqual(keymap[7].HardKeyID    ,     7,"failed: keymap[7].HardKeyID    ,     7");
            Assert.AreEqual(keymap[7].GenericKeyID ,   111,"failed: keymap[7].GenericKeyID ,   111");

        }

        [Test]
        public void LargeSetTest()
        {
            // version hist:
            //    1.0 2/21 @ 5:19pm
            uint maj_v = 1; 
            uint min_v = 0;
            DateTime chgTime = new DateTime(2007, 2, 21, 17, 19, 0);

            Console.WriteLine("::::::::::::::::::::::::::::::::::::::::::::::");
            Console.WriteLine("LargeSetTest() v{0}.{1} {2}", maj_v, min_v,chgTime);

            const uint OBJ_COUNT = 100000;
            Console.WriteLine("Adding {0} objects to container", OBJ_COUNT);
            for(uint i = 0; i < OBJ_COUNT; i++)
            {
                ContainedClass cc = new ContainedClass(i+10,i);
                addElement(cc);
            }
            // should only be one..

            Assert.AreEqual(keymap.Count, OBJ_COUNT, "failed: keymap.Count == OBJ_COUNT");
            Console.WriteLine("Accessing {0} objects in container", OBJ_COUNT);
            for(uint i = 0; i < OBJ_COUNT; i++)
            {
                Assert.IsTrue(keymap.ContainsKey(i));
                Assert.AreEqual(keymap[i].HardKeyID,i);
                Assert.AreEqual(keymap[i].GenericKeyID,i+10);
            }

        }

        void addElement(ContainedClass cc)
        {
            if(!keymap.ContainsKey(cc.HardKeyID))
            {   
                //         key         ,value
                keymap.Add(cc.HardKeyID,cc);
            }
        }
    }
       
}
