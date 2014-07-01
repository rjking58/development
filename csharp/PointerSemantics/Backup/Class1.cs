using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PointerSemantics
{

    public class X
    {
        private int m_id = 0;
        public X(int id)
        {
            m_id = id;
        }
        public override string ToString()
        {
            return "id(" + m_id + ")";
        }
    }
    
    public class Class1
    {
        static void Main()
        {
            X x1 = new X(1);
            X x2 = new X(1);
            X x3 = null;
            
            Console.WriteLine("x1 " + ((x1 == x2) ? "equals" : "does not equal") + " x2");
            Console.WriteLine("x1 " + ((x1 == x3) ? "equals" : "does not equal") + " x3");
            Console.WriteLine("x2 " + ((x2 == x3) ? "equals" : "does not equal") + " x3");
            
            x3 = x1;
            
            Console.WriteLine("x1 " + ((x1 == x2) ? "equals" : "does not equal") + " x2");
            Console.WriteLine("x1 " + ((x1 == x3) ? "equals" : "does not equal") + " x3");
            Console.WriteLine("x2 " + ((x2 == x3) ? "equals" : "does not equal") + " x3");
            
            x3 = x2;
            Console.WriteLine("x1 " + ((x1 == x2) ? "equals" : "does not equal") + " x2");
            Console.WriteLine("x1 " + ((x1 == x3) ? "equals" : "does not equal") + " x3");
            Console.WriteLine("x2 " + ((x2 == x3) ? "equals" : "does not equal") + " x3");
            x1 = x2;
            Console.WriteLine("x1 " + ((x1 == x2) ? "equals" : "does not equal") + " x2");
            Console.WriteLine("x1 " + ((x1 == x3) ? "equals" : "does not equal") + " x3");
            Console.WriteLine("x2 " + ((x2 == x3) ? "equals" : "does not equal") + " x3");
            x3 = new X(1);
            Console.WriteLine("x1 " + ((x1 == x2) ? "equals" : "does not equal") + " x2");
            Console.WriteLine("x1 " + ((x1 == x3) ? "equals" : "does not equal") + " x3");
            Console.WriteLine("x2 " + ((x2 == x3) ? "equals" : "does not equal") + " x3");
            
        }
    }
}
