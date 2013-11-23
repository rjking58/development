using System;
using System.Collections.Generic;
using System.Text;

namespace StringFormatting
{
    class Program
    {
        static void Main(string[] args)
        {
            for(byte currchar = 65;
                currchar < 91;
                currchar++)
            {
                for(ushort currid = 0;
                    currid < 20;
                    currid++)
                {
                    Console.WriteLine(String.Format("{0}{1:D4}",(char) currchar,currid));
                }
                for(ushort currid = 9980;
                    currid < 10000;
                    currid++)
                {
                    Console.WriteLine(String.Format("{0}{1:D4}",(char) currchar,currid));
                }
                
            }   
        }
    }
}
