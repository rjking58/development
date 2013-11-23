using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

namespace GetType
{
    class Program
    {
        static void Main(string[] args)
        {
            FileInfo fi = new FileInfo(@"c:\temp\DeviceFile.cs");

            Console.WriteLine(fi.GetType().FullName);
        }
    }
}
