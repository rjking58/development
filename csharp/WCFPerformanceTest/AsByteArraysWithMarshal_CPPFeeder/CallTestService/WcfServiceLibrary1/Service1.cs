//#define BIN_SERIALIZE_TEST
#define ALL_BLITTABLE

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

namespace WcfServiceLibrary1
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public class Service1 : IService1
    {
        private int startVal = 0;
        const int CHUNK_SIZE = 10000;

        MonitoredItemValue[] m_values = new MonitoredItemValue[CHUNK_SIZE];
        public Service1()
        {
            for (int currval = 0; currval < CHUNK_SIZE; currval++)
            {
#if ALL_BLITTABLE
                MonitoredItemValue miv = new MonitoredItemValue();
                miv.RuntimeValue_Variant_Payload = new byte[4];
                miv.RuntimeValue_Timestamp = DateTime.Now;
                miv.Variant_Payload = new byte[4];
                m_values[currval] = miv;
#else
                MonitoredItemValue miv = new MonitoredItemValue();
                miv.Item = new ItemIdentity();
                miv.UserData = new Variant();
                miv.UserData.Payload = new byte[4];
                miv.Value = new RuntimeValue();
                miv.Value.Timestamp = DateTime.Now;
                miv.Value.Value = new Variant();
                miv.Value.Value.Payload = new byte[4];
                m_values[currval] = miv;
#endif
            }
        }
#if BIN_SERIALIZE_TEST
        public byte [] GetData()
        {
            BinaryFormatter bf = new BinaryFormatter();
            using (MemoryStream ms = new MemoryStream())
            {
                bf.Serialize(ms,m_values);
                byte[] buff = ms.GetBuffer();
                return buff;
            }
        }

        SerializeArrayOfMIV(MonitoredItemValue[] mivs)
        {
            int ItemCnt = mivs.Length;
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);

        }

#else
        public MonitoredItemValue[] GetData()
        {
            return m_values;
        }
#endif
    }
}
