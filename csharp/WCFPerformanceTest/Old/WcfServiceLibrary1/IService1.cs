//#define BIN_SERIALIZE_TEST
#define ALL_BLITTABLE

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
#if BIN_SERIALIZE_TEST
        [OperationContract]
        byte[] GetData();
#else
        [OperationContract]
        MonitoredItemValue[] GetData();
#endif

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
#if ALL_BLITTABLE

    [DataContract]
    [Serializable]
    [StructLayout(LayoutKind.Sequential,CharSet=CharSet.Unicode,Pack=1)]
    public struct MonitoredItemValue
    {
        [DataMember]
        [MarshalAs(UnmanagedType.ByValTStr,SizeConst=20)]
        public string ItemIdentity_ContextName;
        [DataMember]
        public ulong ItemIdentity_Id;
        [DataMember]
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string ItemIdentity_Name;
        [DataMember]
        public ushort ItemIdentity_ReferenceType;
        [DataMember]
        public ushort ItemIdentity_Type;

        [DataMember]
        public int Variant_Length;
        [DataMember]
        //public long Variant_Payload;
        [MarshalAs(UnmanagedType.ByValArray,ArraySubType=UnmanagedType.I1,SizeConst=4)]
        public byte[] Variant_Payload;
        [DataMember]
        public ushort Variant_Type;

        [DataMember]
        public uint RuntimeValue_Quality;
        [DataMember]
        public DateTime RuntimeValue_Timestamp;
        [DataMember]
        public int RuntimeValue_Variant_Length;
        [DataMember]
        //public long RuntimeValue_Variant_Payload;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.I1, SizeConst = 4)]
        public byte[] RuntimeValue_Variant_Payload;
        [DataMember]
        public ushort RuntimeValue_Variant_Type;
    }
#else
    [DataContract]
    [Serializable]
    public struct ItemIdentity
    {
        [DataMember]
        public string ContextName;
        [DataMember]
        public ulong Id;
        [DataMember]
        public string Name;
        [DataMember]
        public ushort ReferenceType;
        [DataMember]
        public ushort Type;
    }

    [DataContract]
    [Serializable]
    public struct Variant
    {
        [DataMember]
        public int Length;
        [DataMember]
        public byte[] Payload;
        [DataMember]
        public ushort Type;
    }

    [DataContract]
    [Serializable]
    public struct RuntimeValue
    {
        [DataMember]
        public uint Quality;
        [DataMember]
        public DateTime Timestamp;
        [DataMember]
        public Variant Value;
    }

    [DataContract]
    [Serializable]
    public struct MonitoredItemValue
    {
        [DataMember]
        public ItemIdentity Item;
        [DataMember]
        public Variant UserData;
        [DataMember]
        public RuntimeValue Value;
    }
#endif
}
