using System;
using System.Collections.Generic;
using System.Text;

namespace LinkedListsTests
{
    class MyObj
    {
        private string m_name = "";
        public MyObj(string name)
        {
            m_name = name;
        }
        public override string ToString()
        {
            return m_name;
        }
    }
    class Program
    {
    
        static void Main(string[] args)
        {
            List<MyObj> l = new List<MyObj>();
            
            // swap test.
            
            l.Add(new MyObj("A"));
            l.Add(new MyObj("B"));
            l.Add(new MyObj("C"));
            foreach (MyObj mo in l)
            {
                Console.WriteLine(mo);
            }

            Console.WriteLine();
            Console.WriteLine("inserting at 1");
                        
            l.Insert(1,new MyObj("inserted"));
            // try swapping A and C
            foreach (MyObj mo in l)
            {
                Console.WriteLine(mo);
            }
            
            Console.WriteLine();
            Console.WriteLine("inserting at 3");
            l.Insert(3,new MyObj("inserted2"));
            // try swapping A and C
            foreach (MyObj mo in l)
            {
                Console.WriteLine(mo);
            }
            Console.WriteLine();
            Console.WriteLine("inserting at 0");
            l.Insert(0,new MyObj("inserted3"));
            // try swapping A and C
            foreach (MyObj mo in l)
            {
                Console.WriteLine(mo);
            }
            
        }
    }
}
