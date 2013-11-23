using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace structToByte
{
    class Program
    {
        // pack=1 is required so that the structure is packed field to field without
        // intervening spaces
        [StructLayout(LayoutKind.Sequential,Pack = 1)]
        struct subfields
        {
            public byte m_sub_b;
            public uint m_sub_i;
        }   
        
        [StructLayout(LayoutKind.Sequential,Pack=1)  ]
        unsafe struct myStruct
        { 
            public subfields    m_sf;
            public byte         m_b1;
            public uint         m_ui;
            public ushort       m_us;
            public short        m_s;
            public byte         m_b2;
            public byte         m_b3;
            public fixed byte   m_c[3];
            public bool         m_boo;
        }
        
        static void Main(string[] args)
        {
            //myStruct my;
            // required so that compiler doesn't complain about 
            // non-initialized variable.
            //my.m_b1 = 0;
            //my.m_ui = 0;
            //my.m_us = 0;
            //my.m_b2 = 0;

            int mystruct_sz;
            // can't take size of this struct without using 'unsafe'...
            unsafe
            {
                mystruct_sz = sizeof(myStruct);
            }
            // byte array which can hold our information.
            // byte[] ar = new byte[Marshal.SizeOf(my)];
            byte[] ar = new byte[mystruct_sz];
            
            Console.WriteLine("ar.Length(" + ar.Length + ")");
            unsafe
            {
                // fix managed memory in place so we can take a pointer.
                fixed (byte* pArr =  ar)
                {
                    // convert byte * to myStruct *
                    myStruct* p_ms = (myStruct*) pArr;
                    // do assignment.
                    p_ms->m_sf.m_sub_b = 17;
                    p_ms->m_sf.m_sub_i = 19;
                    p_ms->m_b1 = 2;
                    p_ms->m_ui = 4;
                    p_ms->m_us = 6;
                    p_ms->m_s  = 8;
                    p_ms->m_b2 = 10;
                    p_ms->m_b3 = 12;
                    p_ms->m_boo = true;
                    p_ms->m_c[0] = 99;
                    p_ms->m_c[1] = 100;
                    p_ms->m_c[2] = 101;
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

