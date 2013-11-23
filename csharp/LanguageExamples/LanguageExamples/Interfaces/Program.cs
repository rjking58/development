using System;
using System.Collections.Generic;
using System.Text;

namespace Interfaces
{

    public interface A
    {
        void methodA();
    }

    public interface B
    {
        void methodB();
    }

    // interface inheritance..
    public interface B2 : B
    {
        void methodB2();
    }

    // multiple interface implementation..
    public abstract class c1 : A, B2
    {
        // deferred implementation of A's method..
        public abstract void methodA();
        public virtual void methodB()
        {
            System.Console.WriteLine("methodB called..");
        }
        public virtual void methodB2()
        {
            System.Console.WriteLine("methodB2 called..");
        }
    }

    public class c2 : c1
    {
        public override void methodA()
        {
            System.Console.WriteLine("c2::methodA called..");            
        }
    }
    public class c3 : c1
    {
        public override void methodA()
        {
            System.Console.WriteLine("c3::methodA called..");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            c2 a_c2 = new c2();
            c3 a_c3 = new c3();
            a_c2.methodA();
            a_c2.methodB();
            a_c2.methodB2();
            a_c3.methodA();
            a_c3.methodB();
            a_c3.methodB2();

            B2 a_b2 = (B2) a_c2;
            a_b2.methodB2();

            A a_a1 = (A)a_c2;
            A a_a2 = (A)a_c3;
            a_a1.methodA();
            a_a2.methodA();

        }
    }
}
