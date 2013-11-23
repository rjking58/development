
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

using System.Runtime.InteropServices;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

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

    [Serializable]
    public struct struct1 : ISerializable
    {
        public string str1;
        public ulong ulong1;
        public string str2;
        public ushort ushort1;
        public ushort ushort2;

        public struct1(SerializationInfo info, StreamingContext context)
        {
            str1 = info.GetString("str1");
            str2 = info.GetString("str2");
            ulong1 = info.GetUInt64("ulong1");
            ushort1 = info.GetUInt16("ushort1");
            ushort2 = info.GetUInt16("ushort2");
        }

        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("str1", str1);
            info.AddValue("str2", str2);
            info.AddValue("ulong1", ulong1);
            info.AddValue("ushort1", ushort1);
            info.AddValue("ushort2", ushort2);
        }
    }

    [Serializable]
    public struct struct2
    {
        public int data_len;
        public byte[] data;
        public ushort ushort3;

        public struct2(SerializationInfo info, StreamingContext context)
        {
            data_len = info.GetInt32("data_len");
            ushort3 = info.GetUInt16("ushort3");
            data = (byte []) info.GetValue("data", typeof(byte[]));

        }

        public void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            info.AddValue("data_len", data_len);
            info.AddValue("ushort3", ushort3);

            info.AddValue("data", data);
        }
    }

    [Serializable]
    public struct timedata
    {
        public uint uint1;
        public DateTime Timestamp;
        public struct2 Value;
    }

    [Serializable]
    public struct valToTransfer
    {
        public struct1 Item;
        public struct2 UserData;
        public timedata Value;
    }

    [DataContract(Name = "valToTransfer")]
    public struct valToTransferAsBytes : IDataContractSurrogate
    {
        [DataMember]
        public byte[] theBytes;

        public Type GetDataContractType(Type type)
        {
            if (typeof(valToTransfer).IsAssignableFrom(type))
            {
                return typeof(valToTransferAsBytes);
            }
            return type;
        }

        public object GetDeserializedObject(object obj, Type targetType)
        {
            if (obj is valToTransferAsBytes)
            {
                MemoryStream ms = new MemoryStream(((valToTransferAsBytes)obj).theBytes);
                BinaryFormatter bf = new BinaryFormatter();
                valToTransfer vtt = (valToTransfer)bf.Deserialize(ms);
                return vtt;
            }
            return obj;
        }


        public object GetObjectToSerialize(object obj, Type targetType)
        {
            if (obj is valToTransfer)
            {
                valToTransferAsBytes vab = new valToTransferAsBytes();
                MemoryStream ms = new MemoryStream();
                BinaryFormatter bf = new BinaryFormatter();

                bf.Serialize(ms, (valToTransfer)obj);
                vab.theBytes = ms.GetBuffer();
                return vab;
            }
            return obj;
        }

        public object GetCustomDataToExport(Type clrType, Type dataContractType)
        {
            return null;
        }

        public object GetCustomDataToExport(System.Reflection.MemberInfo memberInfo, Type dataContractType)
        {
            return null;
        }

        public void GetKnownCustomDataTypes(System.Collections.ObjectModel.Collection<Type> customDataTypes)
        {
        }

        public Type GetReferencedTypeOnImport(string typeName, string typeNamespace, object customData)
        {
            return null;
        }

        public System.CodeDom.CodeTypeDeclaration ProcessImportedType(System.CodeDom.CodeTypeDeclaration typeDeclaration, System.CodeDom.CodeCompileUnit compileUnit)
        {
            return typeDeclaration;
        }

    }
}
