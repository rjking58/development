using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Runtime.InteropServices;


namespace WcfServiceLibrary1
{
    public class Service1 : IService1
    {
        private int             startVal = 0;
        const int               CHUNK_SIZE = 10000;

        valToTransfer[]    m_values = new valToTransfer[CHUNK_SIZE];

        private int             currPacket = 0;

        public Service1()
        {
            for (ulong currval = 0; currval < CHUNK_SIZE; currval++)
            {
                valToTransfer miv = new valToTransfer();
                miv.timedata_struct2_data = new byte[4];
                miv.timedata_Timestamp = DateTime.Now;
                miv.struct2_data = new byte[4];
                miv.struct1_ulong1 = currval;
                m_values[currval] = miv;

            }

        }
        public byte [] GetData()
        {
            // this example just tests the raw speed of transferring a byte array of the size necessary to serialize our monitoreditemvalue array.
            return DoMIVSerialize();
        }

        byte[] DoMIVSerialize()
        {
            // Get the byte size of a MyDataStruct structure if it is to be
            // marshaled to unmanaged memory.
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);
            bw.Write(CHUNK_SIZE);

            // which one we are getting..
            m_values[0].struct2_data_len = currPacket++;

            for (int convertCnt = 0; convertCnt < CHUNK_SIZE; convertCnt++)
            {

                Int32 iSizeOfMonitoredItemValue = Marshal.SizeOf(typeof(valToTransfer));
                // Allocate a byte array to contain the bytes of the unmanaged version
                // of the MyDataStruct structure.
                byte[] byteArrayMonitoredItemValue = new byte[iSizeOfMonitoredItemValue];
                // Allocate a GCHandle to pin the byteArrayMyDataStruct array
                // in memory in order to obtain its pointer.
                GCHandle gch = GCHandle.Alloc(byteArrayMonitoredItemValue, GCHandleType.Pinned);
                // Obtain a pointer to the byteArrayMyDataStruct array in memory.
                IntPtr pbyteArrayMyDataStruct = gch.AddrOfPinnedObject();
                // Copy all bytes from the managed MyDataStruct structure into
                // the byte array.
                Marshal.StructureToPtr(m_values[convertCnt], pbyteArrayMyDataStruct, false);
                // Unpin the byteArrayMyDataStruct array in memory.
                gch.Free();
                // Return the byte array.
                // It contains the serialized bytes of the MyDataStruct structure.

                bw.Write(byteArrayMonitoredItemValue);
            }
            return ms.GetBuffer();
        }
    }
}
