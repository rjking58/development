using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SByteArrayConversionTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SByte[] xx = new sbyte[10];

            for(int x = 0; x < 10; x++)
            {
                xx[x] = (sbyte) ('a' + x);
            }

            Byte[] byteArray = new byte[10];
            Buffer.BlockCopy(xx,0,byteArray,0,10);

            for(int x = 0; x < 10; x++)
            {
                Console.Write((char) byteArray[x]);
            }
            Console.WriteLine();

        }
    }
}
