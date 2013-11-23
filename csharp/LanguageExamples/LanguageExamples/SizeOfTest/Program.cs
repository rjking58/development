using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SizeOfTest
{
    class Program
    {
        static void Main(string[] args)
        {
            byte    b = 0;
            short   s = 0;
            ushort  us = 0;
            int     i = 0;
            uint    ui = 0;
            long    l = 0;
            ulong   ul = 0;
            
            Console.WriteLine("sizeof byte  : {0}",Marshal.SizeOf(b));
            Console.WriteLine("sizeof short : {0}",Marshal.SizeOf(s));
            Console.WriteLine("sizeof ushort: {0}",Marshal.SizeOf(us));
            Console.WriteLine("sizeof int   : {0}",Marshal.SizeOf(i));
            Console.WriteLine("sizeof uint  : {0}",Marshal.SizeOf(ui));
            Console.WriteLine("sizeof long  : {0}",Marshal.SizeOf(l));
            Console.WriteLine("sizeof ulong : {0}",Marshal.SizeOf(ul));
            
        }
    }
}
