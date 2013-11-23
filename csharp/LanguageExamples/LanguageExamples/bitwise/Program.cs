using System;
using System.Collections.Generic;
using System.Text;

namespace bitwise
{
    class Program
    {
        static void Main(string[] args)
        {
        
            byte b = 0x02;
            Console.Write(String.Format("b({0:X4})    ",b)); 
            ByteInBinary(b);
                        

            
            b ^= 0xFF;
            Console.Write(String.Format("b({0:X4})    ",b)); 
            ByteInBinary(b);            
            
            ushort w = 0x02;
            Console.Write(String.Format("b({0:X4})    ",w));
            WordInBinary(w);            
                        
            w ^= 0xFFFF;
            Console.Write(String.Format("b({0:X4})    ",w));
            WordInBinary(w);            
            
            
        }
        private static void ByteInBinary(byte b)
        {
            byte mask = 0x80;
            for (int bit = 0;
                 bit < 8;
                 bit++)
            {
                if ((b & mask) != 0)
                {
                    Console.Write("1");
                }
                else
                {
                    Console.Write("0");
                }
                mask >>= 1;
            }
            Console.WriteLine();
        
        }
        private static void WordInBinary(ushort w)
        {
            ushort mask = 0x8000;
            for (int bit = 0;
                 bit < 16;
                 bit++)
            {
                if ((w & mask) != 0)
                {
                    Console.Write("1");
                }
                else
                {
                    Console.Write("0");
                }
                mask >>= 1;
            }
            Console.WriteLine();

        }
        
    }
}
