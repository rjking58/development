using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MemStreamTest
{
    public class Class1
    {
        public static void Main()
        {
            // 1K initial size.. expandable.
            MemoryStream mem_strm = new MemoryStream(1024);

            mem_strm.WriteByte(10);
            mem_strm.WriteByte(20);
            mem_strm.WriteByte(30);
            mem_strm.WriteByte(40);
            mem_strm.WriteByte(45);
            mem_strm.WriteByte(46);
            mem_strm.WriteByte(47);
            
            byte [] b_ary = mem_strm.GetBuffer();
            Console.WriteLine("mem_strm.Position(" + mem_strm.Position + ")");
            Console.WriteLine("mem_strm.Length(" + mem_strm.Length + ")" );
            for (int buff_ofst = 0; buff_ofst < mem_strm.Length; buff_ofst++)
            {
                Console.Write("{0:X2} ",b_ary[buff_ofst]);
            }
            Console.WriteLine();

        }
        
        
    }
}
