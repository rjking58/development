using System;
using System.Collections.Generic;
using System.Text;

namespace virtualDemo
{
    public sealed class sld
    {
        public void Iam()
        {
            Console.WriteLine("sealed....");
        }
    }

    // illegal class declaration (its base is sealed)
    //public class sld_deriv : sld
    //{
    //}

    public abstract class Base
    {
        public virtual void who()
        {
            Console.WriteLine("who() in Base");
        }
        public abstract void zz();
    }

    public abstract class Derived1 : Base
    {
        public override void who()
        {
            Console.WriteLine("who() in Derived1");
        }
        public abstract void why();
        // this next (commented out) statement is illegal.. in C#, this is interpreted as 'hiding' the abstract method above it
        // public abstract void zz();
    }

    public class Derived2 : Derived1
    {
        public override void who()
        {
            Console.WriteLine("who in Derived2");
        }
        public override void why()
        {
            Console.WriteLine("who knows??");
        }
        public override void zz()
        {
            Console.WriteLine("zzzzzzzzzz");
        }
    }


}
