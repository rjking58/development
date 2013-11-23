using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace structToByte
{
    class Program
    {
        [StructLayout(LayoutKind.Explicit)]
        struct myStruct
        {   
            [FieldOffset(0)]
            public byte m_b1;
            [FieldOffset(1)]
            public uint m_ui;
            [FieldOffset(5)]
            public ushort m_us;
            [FieldOffset(7)]
            public byte m_b2;
        }
    
        static void Main(string[] args)
        {
            myStruct my;
            my.m_b1 = 5;
            my.m_ui = 10;
            my.m_us = 20;
            my.m_b2 = 30;

            byte[] ar = new byte[Marshal.SizeOf(my)];
            Console.WriteLine("ar.Length(" + ar.Length + ")");
            unsafe
            {

                fixed (byte* pArr = ar)
                {
                    *((myStruct*)pArr) = my;
                }
            }    
            for (int x = 0; x < ar.Length; x++)
            {
                Console.Write("{0:X2} ", ar[x]);
            }
            Console.WriteLine();            
        }
    }
}
