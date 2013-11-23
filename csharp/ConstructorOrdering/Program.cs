using System;
using System.Collections.Generic;
using System.Text;

namespace ConstructorOrdering
{
    class A
    {
        public A ()
        {
            Console.WriteLine("A::A executing");
        }
    }
    class B : A
    {
        public B ()
        {
            Console.WriteLine("B::B executing");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            A inst = new B();
        }
    }
}
