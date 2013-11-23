using System;

namespace Literals
{
    class DecimalDemo
    {
        // private variables
        decimal amount;
        decimal rate_of_return;
        int years;
        int i;

        // public interface
        public void DoFutureVal()
        {
            amount = 1000.0m;
            rate_of_return = 0.07m;
            years = 10;

            Console.WriteLine("Original Investment: $" + amount);
            Console.WriteLine("Rate of return: %" + (100*rate_of_return));
            Console.WriteLine("Over " + years + " years");
            for (i = 0; i < years; i++)
            {
                amount = amount + (amount * rate_of_return);
            }
            Console.WriteLine("Future value is $" + amount);
        }
    }
    /// <summary>
    /// Summary description for Class1.
    /// </summary>
    class LiteralTest
    {                   
        static sbyte    m_sbyte     = -127;          // signed byte
        static byte     m_byte      = 255;          // unsigned byte
        static short    m_short     = -32767;        // signed 16 bit 
        static ushort   m_ushort    = 65535;        // unsigned 16 bit
        static int      m_int       = -2147483647;   // signed integer 32 bit
        static uint     m_uint      = 4294967295;   // unsigned integer 32 bit
        static long     m_long      = -9223372036854775807;  // signed long 64 bit
        static ulong    m_ulong     = 18446744073709551615; // unsigned long 64 bit
        static float    m_flt       = 12.334455f;   // single precision floating point
        static double   m_dbl       = 12.334455f;   // double precision floating point
        static decimal  m_deci = 12.43m;
        static bool     m_bool = true;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>


        static void OutputBinaryAlgo(ulong ul,uint width)
        {
            uint  four_bit_cnt = 0;
            ulong bitmask = 1;
            for (int curbit = 0;
                 curbit < (width - 1);
                 curbit++ )
            {
                bitmask = bitmask << 1;
//                System.Console.WriteLine("shifting bitmask:" + bitmask);
            }
            System.Console.Write("binary: ");
            for (int curbit = 0;
                 curbit < width;
                 curbit++ )
            {
                if ((ul & bitmask) != 0)
                {
                    System.Console.Write("1");
                }
                else
                {
                    System.Console.Write("0");
                }
                four_bit_cnt++;
                if (four_bit_cnt >= 4)
                {
                    four_bit_cnt = 0;
                    System.Console.Write(" ");
                }
                
                bitmask = bitmask >> 1;
            }
            System.Console.WriteLine();
        }
        static void OutputBinary(sbyte sb)
        {
            OutputBinaryAlgo((ulong) sb,8);
        }
        static void OutputBinary(byte b)
        {
            OutputBinaryAlgo((ulong) b,8);
        }
        static void OutputBinary(short s)
        {
            OutputBinaryAlgo((ulong) s,16);
        }
        static void OutputBinary(ushort us)
        {
            OutputBinaryAlgo((ulong) us,16);
        }
        static void OutputBinary(int i)
        {
            OutputBinaryAlgo((ulong) i,32);
        }
        static void OutputBinary(uint ui)
        {
            OutputBinaryAlgo((ulong) ui,32);
        }
        static void OutputBinary(long l)
        {
            OutputBinaryAlgo((ulong) l,64);
        }
        static void OutputBinary(ulong ul)
        {
            OutputBinaryAlgo((ulong) ul,64);
        }

        [STAThread]
        static void Main(string[] args)
        {
            System.Console.WriteLine("m_sbyte(" + m_sbyte + ")");
            OutputBinary(m_sbyte);
            System.Console.WriteLine("m_byte(" + m_byte + ")");
            OutputBinary(m_byte);            
            System.Console.WriteLine("m_short(" + m_short + ")");
            OutputBinary(m_short);            
            System.Console.WriteLine("m_ushort(" + m_ushort + ")");
            OutputBinary(m_ushort);
            System.Console.WriteLine("m_int(" + m_int + ")");
            OutputBinary(m_int);
            System.Console.WriteLine("m_uint(" + m_uint + ")");
            OutputBinary(m_uint);
            System.Console.WriteLine("m_long(" + m_long + ")");
            OutputBinary(m_long);
            System.Console.WriteLine("m_ulong(" + m_ulong + ")");
            OutputBinary(m_ulong);

            System.Console.WriteLine("m_flt(" + m_flt + ")");
            System.Console.WriteLine("m_dbl(" + m_dbl + ")");
            System.Console.WriteLine("m_deci(" + m_deci + ")");
            System.Console.WriteLine("m_bool(" + m_bool + ")");
            //
            // TODO: Add code to start application here
            //
            {
                DecimalDemo m_futureval = new DecimalDemo();
                m_futureval.DoFutureVal();
            }

            //wierd side affect of integer promotion...
            {
                byte b = 10;
                //b = b+b;          // this doesn't compile!
                //b = (byte) b+b;   // nor this..
                b = (byte) (b+b); // but this does..
                System.Console.WriteLine("byte b(" + b + ")");
            }
        }
    }
}
