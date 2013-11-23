using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ExportedTypes;

namespace TypeAssemblyUptakeTest
{
    class Program
    {
        static void Main(string[] args)
        {
            TypeOfInterest v = new TypeOfInterest();

            v.x = 1;
            v.y = 2;

            System.Console.WriteLine("v.x=" + v.x + " v.y=" + v.y);

            v.IAm();


        }
    }
}
