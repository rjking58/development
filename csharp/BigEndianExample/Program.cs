using System;
using System.Collections.Generic;
using System.Text;

namespace BigEndianExample
{
    class Program
    {
        static void Main(string[] args)
        {
            byte    b   = 0x32;
            ushort us   = 0x1234;
            uint   ui   = 0x12345678;
            
            byte [] byteAry = BitConverter.GetBytes(b);
            byte [] ushortAry = BitConverter.GetBytes(us);
            Array.Reverse(ushortAry);
            byte [] uintAry = BitConverter.GetBytes(ui);
            Array.Reverse(uintAry);
            
            Console.WriteLine("ushortAry.Length[" + ushortAry.Length + "]");
            OutputBytes(ushortAry);
            Console.WriteLine("uintAry.Length[" + uintAry.Length + "]");
            OutputBytes(uintAry);
        }
        
        private static void OutputBytes(byte [] ary)
        {
            for(int currByte = 0;
                currByte < ary.Length;
                currByte++)
            {
                if(((currByte % 16) == 0 )&& (currByte != 0))
                {
                    Console.WriteLine();
                }
                Console.Write(String.Format("{0,3:X2}",ary[currByte]));
            }
            Console.WriteLine();
        }
    }
}
