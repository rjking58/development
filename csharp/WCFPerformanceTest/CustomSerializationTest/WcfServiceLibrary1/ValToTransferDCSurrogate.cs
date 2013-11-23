using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace WcfServiceLibrary1
{
    public class ValToTransferDCSurrogate : IDataContractSurrogate
    {

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
                valToTransfer vtt = (valToTransfer) bf.Deserialize(ms);
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
