using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ReferenceComparisons
{
    class X
    {
        private static int curr_ref = 0;
        private int m_ref = 0;
        public X()
        {
            m_ref = curr_ref;
            curr_ref++;
        }
            
        public int refNum
        {
            get
            {
                return curr_ref;
            }
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            X x1 = new X();
            X x2 = new X();
            X x3 = x1;

            Console.WriteLine("x1 == x1 {0}",(x1 == x1));
            Console.WriteLine("x1 == x2 {0}",(x1 == x2));
            Console.WriteLine("x1 == x3 {0}",(x1 == x3));
            Console.WriteLine("x2 == x1 {0}",(x2 == x1));
            Console.WriteLine("x2 == x2 {0}",(x2 == x2));
            Console.WriteLine("x2 == x3 {0}",(x2 == x3));
            Console.WriteLine("x3 == x1 {0}",(x3 == x1));
            Console.WriteLine("x3 == x2 {0}",(x3 == x2));
            Console.WriteLine("x3 == x3 {0}",(x3 == x3));
        }
    }
}
