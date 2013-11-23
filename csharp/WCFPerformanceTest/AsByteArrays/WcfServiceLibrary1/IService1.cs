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
}
