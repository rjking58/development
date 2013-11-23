using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AbstractFactory
{
    /// <summary>
    /// a product of our factory.. expressed abstractly
    /// </summary>
    abstract class AbstractProduct
    {
        public abstract void DoSomething();
    }

    /// <summary>
    /// a product of our factory.. concrete product 1
    /// </summary>
    class Product1 : AbstractProduct
    {
        public override void DoSomething()
        {
            System.Console.WriteLine("DoSomething Product1");
        }
    }
    
    /// <summary>
    /// a product of our factory.. concrete product 2
    /// </summary>
    class Product2 : AbstractProduct
    {
        public override void DoSomething()
        {
            System.Console.WriteLine("DoSomething Product2");
        }
    }
    
    /// <summary>
    /// our factory, expressed abstractly
    /// </summary>
    abstract class AbstractFactory
    {
        public abstract AbstractProduct MakeProduct();
    }

    /// <summary>
    /// a factory that generates product1s
    /// </summary>
    class Factory1 : AbstractFactory
    {
        public override AbstractProduct MakeProduct()
        {
            return new Product1();
        }
    }

    /// <summary>
    /// a factory that generates product2s
    /// </summary>
    class Factory2 : AbstractFactory
    {
        public override AbstractProduct MakeProduct()
        {
            return new Product2();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            AbstractFactory af = new Factory1();

            AbstractProduct ap = af.MakeProduct();
            ap.DoSomething();

            af = new Factory2();

            ap = af.MakeProduct();
            ap.DoSomething();

        }
    }
}
