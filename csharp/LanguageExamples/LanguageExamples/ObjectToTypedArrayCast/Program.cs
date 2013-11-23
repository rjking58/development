using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ObjectToTypedArrayCast
{
    class A 
    {
        private int m_ID;
        public A(int ID)
        {
            m_ID = ID;
        }
        
        public void PrintMe()
        {
            Console.WriteLine("I'm and A(" + m_ID + ")");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            object [] obj_ary = new object[3];
            obj_ary[0] = new A(1);
            obj_ary[1] = new A(2);
            obj_ary[2] = new A(3);
            
            A[] a_ary = (A[]) obj_ary;
            foreach (A an_a in a_ary)
            {
                an_a.PrintMe();
            }
        }
    }
}
