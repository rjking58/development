using System;
using System.Collections.Generic;
using System.Text;
using simpleAccessTest;

namespace SimpleAccessProg
{
    class Program
    {
        static void Main(string[] args)
        {
            extRef ef = new extRef();

            ef.makeEntry(1, 4);
            ef.makeEntry(2, 5);
            ef.makeEntry(3, 6);
            for (int i = 0;
                 i < ef.Count();
                 i++)
            {
                IInternalClass iic = ef[i];
                if (iic != null)
                {
                    Console.WriteLine("ef[" + i + "] Method1() (" + iic.Method1() + ")");
                }
                else
                {
                    Console.WriteLine("null returned!!");
                }
            }
        }
    }
}
