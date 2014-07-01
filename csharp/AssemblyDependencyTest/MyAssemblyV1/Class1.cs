using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MyAssembly
{
    public static class MyClassRetrieve
    {
        public static MyClass GetMyClass()
        {
            return new MyClassImpl();
        }
    }
    public interface MyClass
    {
        void DoSomething();
    }

    internal class MyClassImpl : MyClass
    {
        public void DoSomething()
        {
            Console.WriteLine("version1");
        }

    }

}

