using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FormatNumbers
{
    class Program
    {
        static void Main(string[] args)
        {
            // look for "formatting types"  for a LOT more info..
            // these specific codes can be found under the entry
            // "Standard Numeric Format Strings" and others at the end of the 
            // "Formatting Types" help page.
            Console.WriteLine("the value 99999 in various formats");

            Console.WriteLine("c format: {0:c}",99999);
            Console.WriteLine("d9 format: {0:d9}", 99999);
            Console.WriteLine("f3 format: {0:f3}", 99999);
            Console.WriteLine("n format: {0:n}", 99999);
            
            Console.WriteLine("e format: {0:e}", 99999);
            Console.WriteLine("E format: {0:E}", 99999);
            Console.WriteLine("x format: {0:x}", 99999);
            Console.WriteLine("X format: {0:X}", 99999);

            // now as an overt format..

            String fmtedString = String.Format("c format: {0:c}",99999);
            Console.WriteLine("from String.Format-----");
            Console.WriteLine(fmtedString);

        }
    }
}
