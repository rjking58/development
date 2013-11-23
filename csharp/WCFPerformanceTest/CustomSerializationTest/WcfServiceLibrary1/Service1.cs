
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

        valToTransfer[] m_values = new valToTransfer[CHUNK_SIZE];
        public Service1()
        {
            for (int currval = 0; currval < CHUNK_SIZE; currval++)
            {
                valToTransfer miv = new valToTransfer();
                miv.Item = new struct1();
                miv.UserData = new struct2();
                miv.UserData.data = new byte[4];
                miv.Value = new timedata();
                miv.Value.Timestamp = DateTime.Now;
                miv.Value.Value = new struct2();
                miv.Value.Value.data = new byte[4];
                m_values[currval] = miv;
            }
        }
        public valToTransfer[] GetData()
        {
            return m_values;
        }
    }
}
