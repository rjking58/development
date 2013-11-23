using System;
using System.Collections.Generic;
using System.Text;

namespace GlobalConstantsTest
{
    class GlobalConsts
    {
        public const int CONST1 = 1;
        public const int CONST2 = 2;
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(GlobalConsts.CONST1);
            Console.WriteLine(GlobalConsts.CONST2);            
        }
    }
}
