//#define BIN_SERIALIZE_TEST

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CallTestService.ServiceReference1;

using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;




namespace CallTestService
{
#if BIN_SERIALIZE_TEST
    [Serializable]
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
    public struct MonitoredItemValue
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string ItemIdentity_ContextName;
        public ulong ItemIdentity_Id;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string ItemIdentity_Name;
        public ushort ItemIdentity_ReferenceType;
        public ushort ItemIdentity_Type;

        public int Variant_Length;
        //public long Variant_Payload;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I1, SizeConst = 4)]
        public byte[] Variant_Payload;
        public ushort Variant_Type;

        public uint RuntimeValue_Quality;
        public DateTime RuntimeValue_Timestamp;
        public int RuntimeValue_Variant_Length;
        //public long RuntimeValue_Variant_Payload;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I1, SizeConst = 4)]
        public byte[] RuntimeValue_Variant_Payload;
        public ushort RuntimeValue_Variant_Type;
    }


#endif

    class Program
    {
        private const int TEST_COUNT = 20;
        private static int aggregateMilliseconds = 0;

        static void Main(string[] args)
        {
            ServiceReference1.Service1Client SvcProxy = new ServiceReference1.Service1Client("tcpWcfSvcLib1EP");
            SvcProxy.Open();

            //2,147,483,647
            MonitoredItemValue [] values;
#if BIN_SERIALIZE_TEST
            byte[] valuesBytes;
#endif
            for (int x = 0; x < TEST_COUNT; x++)
            {
                DateTime startTime = DateTime.Now;
#if BIN_SERIALIZE_TEST
                valuesBytes = SvcProxy.GetData();
//                BinaryFormatter bf = new BinaryFormatter();
//                MonitoredItemValue []miv_ary = bf.Deserialize(
#else
                values = SvcProxy.GetData();
#endif
                DateTime endTime = DateTime.Now;
                TimeSpan ts = new TimeSpan(endTime.Ticks - startTime.Ticks);
                aggregateMilliseconds += ts.Milliseconds;

                Console.WriteLine("time for call:[" + ts.Milliseconds + "]");
#if BIN_SERIALIZE_TEST
                Console.WriteLine("size of data passed [" + valuesBytes.Length + "]");
#else
                Console.WriteLine("size of data passed [" + values.Length + "]");
                Console.WriteLine("first val [" + values[0] + "]");
#endif
            }
            Console.WriteLine("avg time per call [" + aggregateMilliseconds/TEST_COUNT + "]");

            SvcProxy.Close();
        }
    }
}
