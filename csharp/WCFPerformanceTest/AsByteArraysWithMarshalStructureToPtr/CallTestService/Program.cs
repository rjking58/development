#define BIN_SERIALIZE_TEST

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CallTestService.ServiceReference1;

using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

[DataContract]
[Serializable]
[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
public struct valToTransfer
{
    [DataMember]
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
    public string struct1_str1;
    [DataMember]
    public ulong struct1_ulong1;
    [DataMember]
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
    public string struct1_str2;
    [DataMember]
    public ushort struct1_ushort1;
    [DataMember]
    public ushort struct1_ushort2;

    [DataMember]
    public int struct2_data_len;
    [DataMember]
    [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I1, SizeConst = 4)]
    public byte[] struct2_data;
    [DataMember]
    public ushort struct2_ushort3;

    [DataMember]
    public uint timedata_uint1;
    [DataMember]
    public DateTime timedata_Timestamp;
    [DataMember]
    public int timedata_Value;
    [DataMember]
    [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I1, SizeConst = 4)]
    public byte[] timedata_struct2_data;
    [DataMember]
    public ushort timedata_struct2_value;
    [DataMember]
    public ushort timedata_struct2_datalen;
}



namespace CallTestService
{
    class Program
    {
        private const int TEST_COUNT = 20;
        private static int aggregateMilliseconds = 0;

        static void Main(string[] args)
        {
            ServiceReference1.Service1Client SvcProxy = new ServiceReference1.Service1Client("tcpWcfSvcLib1EP");
            SvcProxy.Open();

            //2,147,483,647
            byte[] valuesBytes;
            valToTransfer[] mivs = null;

            for (int x = 0; x < TEST_COUNT; x++)
            {
                DateTime startTime = DateTime.Now;
                valuesBytes = SvcProxy.GetData();
                mivs = HandDeserialize(valuesBytes);
                DateTime endTime = DateTime.Now;
                TimeSpan ts = new TimeSpan(endTime.Ticks - startTime.Ticks);
                aggregateMilliseconds += ts.Milliseconds;

                Console.WriteLine("time for call:[" + ts.Milliseconds + "]");
                Console.WriteLine("size of data passed [" + valuesBytes.Length + "]");
                Console.WriteLine("packet number[" + mivs[0].struct2_data_len + "]"); // hijacked for testing purposes..
                Console.WriteLine("500th item audit[" + mivs[499].struct1_ulong1 + "]");
                Console.WriteLine("9000th item audit[" + mivs[8999].struct1_ulong1 + "]");
            }
            Console.WriteLine("avg time per call [" + aggregateMilliseconds/TEST_COUNT + "]");

            SvcProxy.Close();
        }

        static valToTransfer[] HandDeserialize(byte [] byteSerializedData)
        {
            // Allocate a GCHandle of the Pinned Type
            // for the byteSerializedData byte array.
            // This is possible for a byte array
            // because it is a blittable type.

            GCHandle gch = GCHandle.Alloc(byteSerializedData, GCHandleType.Pinned);
            // Get a pointer to the byteSerializedData array.
            IntPtr pbyteSerializedData = gch.AddrOfPinnedObject();

            // size of structure..
            Int32 iSizeOfMonitoredItemValue = Marshal.SizeOf(typeof(valToTransfer));

            int itemsCnt = (int) Marshal.ReadIntPtr(pbyteSerializedData);

            valToTransfer[] miv_ary = new valToTransfer[itemsCnt];


            pbyteSerializedData = IntPtr.Add(pbyteSerializedData,4);

            // Convert the array data of byteSerializedData
            // directly into a MyDataStruct structure.
            // The interop marshaler will use the MarshalAsAttribute
            // of the fields of the MyDataStruct structure to
            // perform field data conversions.
            for (int currItem = 0; currItem < itemsCnt; currItem++)
            {
                miv_ary[currItem] = (valToTransfer)Marshal.PtrToStructure(pbyteSerializedData, typeof(valToTransfer));

                if (currItem != (itemsCnt - 1))
                {
                    pbyteSerializedData = IntPtr.Add(pbyteSerializedData, iSizeOfMonitoredItemValue);
                }
            }
            // Free the GCHandle.
            gch.Free();

            return miv_ary;
        }
    }
}
