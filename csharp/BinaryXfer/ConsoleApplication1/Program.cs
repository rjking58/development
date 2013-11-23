using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BinaryXfer;

using System.Runtime.InteropServices;

namespace ConsoleApplication1
{

    [StructLayout(LayoutKind.Sequential,Pack=1)]
    public struct MySimple
    {
        public byte m_byte;
        public short m_short;
        public int m_int;
    }

    public struct MySimpleUnified
    {
        public byte m_byte;
        public short m_short;
        public int m_int;

        public byte[] m_str1;
        public byte[] m_str2;
    }

    class Program
    {
        private static List<MySimpleUnified> m_BulkResult = new List<MySimpleUnified>();

        static void Main(string[] args)
        {
            byte [] theAry = BinaryXfer.BinaryXfer.GetTheAry();

            MySimple ms;
            GCHandle theAryHandle = GCHandle.Alloc(theAry,GCHandleType.Pinned);
            IntPtr theAryHandleAddr = theAryHandle.AddrOfPinnedObject();

            // now get the structured data from this puppy.
            ms = (MySimple) Marshal.PtrToStructure(theAryHandleAddr, typeof(MySimple));

            // size of our structured data...
            int szOfms = Marshal.SizeOf(ms);
            
            // jump past our structure data.
            theAryHandleAddr = IntPtr.Add(theAryHandleAddr,Marshal.SizeOf(ms));

            // ///////////////////////////////////////////////////
            // first array
            // ///////////////////////////////////////////////////
            // get size of our first array.
            byte [] str1 = GetByteArray(ref theAryHandleAddr);
            // ///////////////////////////////////////////////////
            // second array
            // ///////////////////////////////////////////////////
            byte[] str2 = GetByteArray(ref theAryHandleAddr);

            theAryHandle.Free();

            // <><><><><><><><><><><><><><><><><><><><><><><><><><>
            // bulk example
            // <><><><><><><><><><><><><><><><><><><><><><><><><><>
            theAry = BinaryXfer.BinaryXfer.GetBulkTransfer();

            theAryHandle = GCHandle.Alloc(theAry, GCHandleType.Pinned);
            theAryHandleAddr = theAryHandle.AddrOfPinnedObject();

            // get the count..
            int structCount = Marshal.ReadInt32(theAryHandleAddr);
            // jump past the length word
            theAryHandleAddr = IntPtr.Add(theAryHandleAddr, 4);

            for (int currStruct = 0; 
                 currStruct < structCount;
                 currStruct++)
            {
                // properly initialized..
                GetMyStructUnifiedData(ref theAryHandleAddr);
            }
            theAryHandle.Free();

        }
        private static void GetMyStructUnifiedData(ref IntPtr theAryHandleAddr)
        {
            MySimpleUnified msu = new MySimpleUnified();

            // now get the structured data from this puppy.
            MySimple ms = (MySimple)Marshal.PtrToStructure(theAryHandleAddr, typeof(MySimple));
            msu.m_byte = ms.m_byte;
            msu.m_short = ms.m_short;
            msu.m_int = ms.m_int;
           
            // size of our structured data...
            int szOfms = Marshal.SizeOf(ms);

            // jump past our structure data.
            theAryHandleAddr = IntPtr.Add(theAryHandleAddr, szOfms);

            msu.m_str1 = GetByteArray(ref theAryHandleAddr);
            msu.m_str2 = GetByteArray(ref theAryHandleAddr);
          
            m_BulkResult.Add(msu);
        }

        private static byte [] GetByteArray(ref IntPtr theAryHandleAddr)
        {
            short str1sz = Marshal.ReadInt16(theAryHandleAddr);

            // jump past the length word
            theAryHandleAddr = IntPtr.Add(theAryHandleAddr, 2);

            // marshal the array by its size..
            byte[] str1 = new byte[str1sz];
            Marshal.Copy(theAryHandleAddr, str1, 0, str1sz);

            // jump past the array data
            theAryHandleAddr = IntPtr.Add(theAryHandleAddr, str1sz);
            
            return str1;
        }
    }
}
