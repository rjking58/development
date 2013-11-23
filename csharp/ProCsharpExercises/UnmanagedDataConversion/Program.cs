using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace UnmanagedDataConversion
{
    class Program
    {
        struct Message
        {
            public int id;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
            public string text;
            [MarshalAs(UnmanagedType.ByValArray, ArraySubType=UnmanagedType.I1,SizeConst = 10)]
            public byte [] someBytes;
            
        }
        static void Main(string[] args)
        {
            // //////////////////////////////////////////////////////
            // //////////////////////////////////////////////////////
            // //////////////////////////////////////////////////////
            // Deserialize example..
            byte [] sampleBinStream = {0x0a,0,0,0,
                                       (byte) 'h',(byte) 'e',(byte) 'l',(byte) 'l',(byte) 'o',(byte) ' ',(byte) 'w',(byte) 'o',(byte) 'r',(byte) 'l',(byte) 'd',0,0,0,0,0,0,0,0,0,
                                      1,2,3,4,5,6,7,8,9,10};
            Message msg;
            {
                // //////////////////////////////////////////////////////
                // pin it in memory to keep the GC from getting in our way..
                // 
                GCHandle pinnedPacket = GCHandle.Alloc(sampleBinStream, GCHandleType.Pinned);
                // //////////////////////////////////////////////////////
                // fast copy it to our msg object.
                // 
                msg = (Message)Marshal.PtrToStructure(pinnedPacket.AddrOfPinnedObject(),
                                                                typeof(Message));
                // //////////////////////////////////////////////////////
                // UNpin our memory.
                // 
                pinnedPacket.Free();
            }
            Console.WriteLine("msg just created");
            Console.WriteLine(msg.id);
            Console.WriteLine(msg.text);
            foreach (byte b in msg.someBytes)
            {
                Console.Write("{0:X} ", b);
            }
            Console.WriteLine();

            // //////////////////////////////////////////////////////
            // //////////////////////////////////////////////////////
            // //////////////////////////////////////////////////////
            // Serialize Example.
            // //////////////////////////////////////////////////////
            // make new msg..
            // 
            Message msg2 = new Message();
            msg2.id = 2041;
            msg2.someBytes = new byte[] {9,8,7,6,5,4,3,2,1,0};
            msg2.text = "hi there";

            // //////////////////////////////////////////////////////
            // get size of struct..
            // 
            Int32 szOfMsg = Marshal.SizeOf(typeof(Message));
            // //////////////////////////////////////////////////////
            // create container to receive serialized data..
            // 
            byte[] serializedMsg = new byte[szOfMsg];

            {
                // //////////////////////////////////////////////////////
                // pin it in memory to keep the GC from getting in our way..
                // 
                GCHandle gch = GCHandle.Alloc(serializedMsg, GCHandleType.Pinned);
                // //////////////////////////////////////////////////////
                // Get an pointer to it..
                // 
                IntPtr pSerializedMsg = gch.AddrOfPinnedObject();
                // //////////////////////////////////////////////////////
                // fast copy to the byte array..
                // 
                Marshal.StructureToPtr(msg2,pSerializedMsg,false);
                // //////////////////////////////////////////////////////
                // UNpin our memory.  Note that our IntPtr is now invalid!
                // 
                gch.Free();
            }
            Console.WriteLine("serialized msg");
            foreach (byte b in serializedMsg)
            {
                Console.Write("{0:X} ", b);
            }
            Console.WriteLine();
            //int szOfStruct = 
            //Marshal.StructureToPtr(
        }
    }
}
