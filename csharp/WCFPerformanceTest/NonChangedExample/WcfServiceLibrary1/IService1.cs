
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
        valToTransfer[] GetData();

        // TODO: Add your service operations here
    }

    [DataContract]
    [Serializable]
    public struct struct1
    {
        [DataMember]
        public string str1;
        [DataMember]
        public ulong ulong1;
        [DataMember]
        public string str2;
        [DataMember]
        public ushort ushort1;
        [DataMember]
        public ushort ushort2;
    }

    [DataContract]
    [Serializable]
    public struct struct2
    {
        [DataMember]
        public int data_len;
        [DataMember]
        public byte[] data;
        [DataMember]
        public ushort ushort3;
    }

    [DataContract]
    [Serializable]
    public struct timedata
    {
        [DataMember]
        public uint uint1;
        [DataMember]
        public DateTime Timestamp;
        [DataMember]
        public struct2 Value;
    }

    [DataContract]
    [Serializable]
    public struct valToTransfer
    {
        [DataMember]
        public struct1 Item;
        [DataMember]
        public struct2 UserData;
        [DataMember]
        public timedata Value;
    }
}
