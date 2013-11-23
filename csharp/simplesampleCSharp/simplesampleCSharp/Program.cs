using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace simplesampleCSharp
{
    class Program
    {
        static int val = 0;
        static void Main(string[] args)
        {

            Console.WriteLine("Enter a number");
            while (CStandardLib.sscanf(Console.ReadLine(), "%d", ref val) != 0)
            {
                if ((val & 1) != 0)
                {
                    Console.WriteLine("odd!");
                }
                else
                {
                    Console.WriteLine("even!");
                }
            }
            Console.WriteLine("how rude!");
        }
    }

    public class CStandardLib
    {
        [DllImport("msvcrt.dll", CharSet = CharSet.Ansi)]
        public static extern int sscanf(string inp, string fmt,ref int val);
    }

    
}
