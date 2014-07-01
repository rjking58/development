using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AssemblyDependencyTest
{
    class Program
    {
        static void Main(string[] args)
        {
            MyAssembly.MyClass mc = MyAssembly.MyClassRetrieve.GetMyClass();

            mc.DoSomething();
        }
    }
}
