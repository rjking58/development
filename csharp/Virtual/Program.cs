using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Virtual
{
    class Base
    {
        public virtual void x()
        {
            Console.WriteLine("base::x");
        }
    }
    class Sub: Base
    {
        public override void x()
        {
            Console.WriteLine("sub::x");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Base b = new Sub();

            b.x();
        }
    }
}
