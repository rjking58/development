#define BIN_SERIALIZE_TEST

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

using System.Runtime.InteropServices;

namespace WcfServiceLibrary1
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface IService1
    {
        [OperationContract]
        byte[] GetData();

        // TODO: Add your service operations here
    }

    // Use a data contract as illustrated in the sample below to add composite types to service operations
    //[DataContract]
    //public class CompositeType
    //{
    //    bool boolValue = true;
    //    string stringValue = "Hello ";

    //    [DataMember]
    //    public bool BoolValue
    //    {
    //        get { return boolValue; }
    //        set { boolValue = value; }
    //    }

    //    [DataMember]
    //    public string StringValue
    //    {
    //        get { return stringValue; }
    //        set { stringValue = value; }
    //    }
    //}
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
}
