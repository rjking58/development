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
                MonitoredItemValue miv = new MonitoredItemValue();
                miv.RuntimeValue_Variant_Payload = new byte[4];
                miv.RuntimeValue_Timestamp = DateTime.Now;
                miv.Variant_Payload = new byte[4];
                m_values[currval] = miv;
            }
        }
        public MonitoredItemValue[] GetData()
        {
            return m_values;
        }
    }
}
