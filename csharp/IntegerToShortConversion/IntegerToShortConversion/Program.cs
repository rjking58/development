using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IntegerToShortConversion
{
    class Program
    {

        private static void ConvertToUShort(Int32 val, out UInt16 lowerPart, out UInt16 upperPart)
        {
            lowerPart = 0;
            upperPart = 0;

            byte[] totalBits = BitConverter.GetBytes(val);

            byte[] lowerBits = new byte[2];
            lowerBits[0] = totalBits[0];
            lowerBits[1] = totalBits[1];

            byte[] upperBits = new byte[2];
            upperBits[0] = totalBits[2];
            upperBits[1] = totalBits[3];

            lowerPart = BitConverter.ToUInt16(lowerBits, 0);
            upperPart = BitConverter.ToUInt16(upperBits, 0);
        }

        private static void SimpleConvertToUShort(Int32 val, out UInt16 lowerPart, out UInt16 upperPart)
        {
            lowerPart = 0;
            upperPart = 0;

            lowerPart = (ushort) (val & 0xFFFF);
            upperPart = (ushort) ((val >> 16) & 0xFFFF);
        }
        
        static void Main(string[] args)
        {
            Int32 val = 0x01020304;
            UInt16 lower;
            UInt16 upper;
            ConvertToUShort(val, out lower, out upper);

            lower = 0;
            upper = 0;
            SimpleConvertToUShort(val, out lower, out upper);

            val = 0;


        }

    }
}
