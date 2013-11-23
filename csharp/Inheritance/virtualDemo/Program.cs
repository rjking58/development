using System;
using System.Collections.Generic;
using System.Text;

namespace virtualDemo
{
    // A and B demonstrate hiding and use of the 'base' syntax.
    public class A
    {
        public int m_i = 0;
        public void show()
        {
            Console.WriteLine("i in base class: " + m_i);
        }

    }
    public class B : A
    {
        new int m_i;

        public B(int a,int b)
        {
            base.m_i = a;
            m_i = b;
        }

        new public void show()
        {
            base.show();
            Console.WriteLine("i in derived class: " + m_i);
        }
    }



    class Program
    {
        static void Main(string[] args)
        {
            B ob = new B(1,2);

            ob.show();

            Derived2 d = new Derived2();
            d.who();
            d.why();
            d.zz();
            Console.WriteLine("output of ToString for derived2: " + d.ToString());

            sld s = new sld();
            s.Iam();
        }
    }

}
