using System;
using System.Collections.Generic;
using System.Text;

using System.Reflection;

namespace AssemblyVersionTest
{
    class Program
    {
        static void Main(string[] args)
        {
            
            Console.WriteLine(AssemblyName.GetAssemblyName("AssemblyVersionTest.exe").Version );
        }
    }
}
