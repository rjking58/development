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
    public class Service1 : IService1
    {
        private int             startVal = 0;
        const int               CHUNK_SIZE = 10000;

        MonitoredItemValue[]    m_values = new MonitoredItemValue[CHUNK_SIZE];

        private byte[]          m_buffer = null;

        public Service1()
        {
            for (int currval = 0; currval < CHUNK_SIZE; currval++)
            {
                MonitoredItemValue miv = new MonitoredItemValue();
                miv.Item = new ItemIdentity();
                miv.UserData = new Variant();
                miv.UserData.Payload = new byte[4];
                miv.Value = new RuntimeValue();
                miv.Value.Timestamp = DateTime.Now;
                miv.Value.Value = new Variant();
                miv.Value.Value.Payload = new byte[4];
                m_values[currval] = miv;

            }
            BinaryFormatter bf = new BinaryFormatter();
            using (MemoryStream ms = new MemoryStream())
            {
                bf.Serialize(ms, m_values);
                m_buffer = ms.GetBuffer();
            }

        }
        public byte [] GetData()
        {
            // this example just tests the raw speed of transferring a byte array of the size necessary to serialize our monitoreditemvalue array.
            return m_buffer;
        }

    }
}
