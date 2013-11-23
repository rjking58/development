using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EnvironmentClassExample
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Environment.CurrentDirectory);
            Console.WriteLine(Environment.MachineName);
            Console.WriteLine(Environment.OSVersion);
        }
    }
}
