using System;

namespace OperatorSemantics
{
	/// <summary>
	/// Summary description for OperatorSemantics.
	/// </summary>

    public class BinaryOutputter
    {
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
        static public void OutputBinary(sbyte sb)
        {
            OutputBinaryAlgo((ulong) sb,8);
        }
        static public void OutputBinary(byte b)
        {
            OutputBinaryAlgo((ulong) b,8);
        }
        static public void OutputBinary(short s)
        {
            OutputBinaryAlgo((ulong) s,16);
        }
        static public void OutputBinary(ushort us)
        {
            OutputBinaryAlgo((ulong) us,16);
        }
        static public void OutputBinary(int i)
        {
            OutputBinaryAlgo((ulong) i,32);
        }
        static public void OutputBinary(uint ui)
        {
            OutputBinaryAlgo((ulong) ui,32);
        }
        static public void OutputBinary(long l)
        {
            OutputBinaryAlgo((ulong) l,64);
        }
        static public void OutputBinary(ulong ul)
        {
            OutputBinaryAlgo((ulong) ul,64);
        }

    }
	public class OperatorSem
	{

		public static void Main()
		{
		    
            // xor property
            // on/off demo            
            
            // third bit on..
            ushort sh = 4;
            // first, third, fifth bit..
            ushort mask = 1 + 4 + 16;
            System.Console.WriteLine("the mask is :" + mask);
            System.Console.Write(" and in ");
            BinaryOutputter.OutputBinary(mask);

            System.Console.WriteLine("xor demo::::::::::");
            // 20 passes.. turn those bits on and off!
            for (int cnt = 0;
                  cnt < 20;
                  cnt++)
            {
                sh ^= mask;
                BinaryOutputter.OutputBinary(sh);
            }
            
            System.Console.WriteLine("or demo::::::::::::");
            sh = 0;

            System.Console.WriteLine("before:" + sh);
            BinaryOutputter.OutputBinary(sh);
            sh |= mask;
            System.Console.WriteLine("after mask:" + sh );
            BinaryOutputter.OutputBinary(sh);            

            System.Console.WriteLine("and demo::::::::::");
            // all bits on..
            sh = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 512 + 1024 + 2048 + 4096 + 8192 + 16384 + 32768;
            System.Console.WriteLine("before:" + sh);
            BinaryOutputter.OutputBinary(sh);
            sh &= mask;
            System.Console.WriteLine("after mask:" + sh );
            BinaryOutputter.OutputBinary(sh);     
            

            System.Console.WriteLine("ones complement demo::::::::");
            // not demo..
            sh = mask; // set up as the mask first..
            System.Console.WriteLine("before:" + sh);
            BinaryOutputter.OutputBinary(sh);
            // not give it 4 strobes..
            for (int cnt = 0;
                  cnt < 4;
                  cnt++)
            {
                sh = (ushort)~sh;
                BinaryOutputter.OutputBinary(sh);
            }
		}
	}
}
