using System;
using System.Collections.Generic;
using System.Text;

namespace comparisonTestCsharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 11;
            int b = 11;
            int c = 11;
            int d = 11;

            if(a == b == c == d)
            {
                System.Console.WriteLine(" all equal");
            }
            else
            {
                System.Console.WriteLine(" NOT equal");
            }
        }
    }
}
