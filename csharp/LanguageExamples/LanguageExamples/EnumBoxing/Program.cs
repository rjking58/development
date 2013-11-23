using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace EnumBoxing
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] colornames = Enum.GetNames(typeof(KnownColor));

            Console.WriteLine("colornames.Length({0})",colornames.Length);
            for (int i = 0; i < colornames.Length; i++)
            {
                Console.WriteLine(colornames[i]);
            }
            
        }
    }
}
