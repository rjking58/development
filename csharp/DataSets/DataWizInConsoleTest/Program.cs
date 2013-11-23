using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace DataWizInConsoleTest
{
    [Serializable]
    class ContainedBase
    {
        private int m_id;
        public ContainedBase(int passed_id)
        {
            m_id = passed_id;
        }
        public int id
        {
            get
            {
                return m_id;
            }
        }
    }
    [Serializable]
    class Contained1 : ContainedBase
    {
        public Contained1(int passed_id) : base(passed_id)
        {
        }
        public override string ToString()
        {
            return "Contained1[" + id + "]";
        }
    }
    
    [Serializable]
    class Contained2 : ContainedBase
    {
        public Contained2(int passed_id) : base(passed_id)
        {
        }
        public override string ToString()
        {
            return "Contained2[" + id + "]";
        }
    }
    [Serializable]
    class MyContainer
    {
        List<Contained1> m_c1Ary = new List<Contained1>();
        List<Contained2> m_c2Ary = new List<Contained2>();
        public MyContainer()
        {
            for(int currval = 0;
                currval < 10;
                currval++)
            {
                m_c1Ary.Add(new Contained1(currval));
                m_c2Ary.Add(new Contained2(currval+40));
            }
        }
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            foreach(Contained1 c1 in m_c1Ary)
            {
                sb.Append(c1.ToString());
                sb.Append("\n");
            }
            foreach(Contained2 c2 in m_c2Ary)
            {
                sb.Append(c2.ToString());
                sb.Append("\n");
            }
            return sb.ToString();
        }
    }


    class Program
    {
        private static int BIN_COLUMN_SIZE = 0;
        static void Main(string[] args)
        {
        
            
            SerializedTestDS stDS = new SerializedTestDS();
            
            // retrieve the size of our binary data column using metadata..
            // sql used by this table adapter:
            //
            // select character_maximum_length from test_one.information_schema.columns 
            // where table_name = 'SerializedTest' and column_name = 'ObjectData';
                
            SerializedTestDSTableAdapters.SerializedTest_ObjectData_widthTableAdapter st_odwTA = 
                new DataWizInConsoleTest.SerializedTestDSTableAdapters.SerializedTest_ObjectData_widthTableAdapter();
            // get the width of the binary column..
            st_odwTA.Fill(stDS.SerializedTest_ObjectData_width);
            
            SerializedTestDS.SerializedTest_ObjectData_widthRow odw_row = 
                (SerializedTestDS.SerializedTest_ObjectData_widthRow)
                    stDS.SerializedTest_ObjectData_width.Rows[0];
            
            BIN_COLUMN_SIZE = odw_row.character_maximum_length;
            
        
#if true    
            WriteItOut();
#endif            
            // reading it back..
            ReadItBack();
        }
        
        static void WriteItOut()
        {
            // create or contained classes..
            // 
            MyContainer mc = new MyContainer();
            Console.WriteLine(mc.ToString());  
            // serialize our classes to a byte array
            MemoryStream serializeStream = new MemoryStream();
            IFormatter formatter = new BinaryFormatter();
            formatter.Serialize(serializeStream,mc);

            byte [] strm_buff = serializeStream.GetBuffer();
            Console.WriteLine("stream length[" + serializeStream.Length + "]");
            Console.WriteLine("buffer length[" + strm_buff.Length + "]");
            int buff_len = (int) Math.Min(serializeStream.Length,
                                          strm_buff.Length);
            DumpBuffer(strm_buff);
            
            
            // pop it to DB..
            SerializedTestDS stDS = new SerializedTestDS();
            SerializedTestDSTableAdapters.SerializedTestTableAdapter stTA = 
                new SerializedTestDSTableAdapters.SerializedTestTableAdapter();
            
            // for this test, we assume that we are editing user #1..
            // get all userID 1 rows into DS..
            stTA.Fill(stDS.SerializedTest,1);

            SerializedTestDS.SerializedTestDataTable stTbl = 
                stDS.SerializedTest;
            
            // since we are writing, delete the old rows since we are now replacing the old w/ the new.
            foreach(SerializedTestDS.SerializedTestRow row in stTbl.Rows)
            {
                row.Delete();
            }
            // write out our buffer to the DB..
            int bytes_to_write = buff_len;
            int curr_offset = 0;
            int curr_sequence = 1;
            byte [] write_buff = null;
            while (bytes_to_write > 0)
            {
                // we need a new buffer for each row, since the
                // dataset doesn't do a copy of the buffer, but 
                // obviously just keeps a reference to the buffer 
                // before writing.
                write_buff = new byte [BIN_COLUMN_SIZE];
                for(int currByte = 0;
                    currByte < write_buff.Length;
                    currByte++)
                {
                    write_buff[currByte] = strm_buff[currByte + curr_offset];
                }
                // write it..
                SerializedTestDS.SerializedTestRow stRow = 
                    stTbl.NewSerializedTestRow();
                stRow.UserID = 1;
                stRow.ObjectData = write_buff;
                stRow.sequence = curr_sequence;
                stTbl.AddSerializedTestRow(stRow);
                Console.WriteLine("Writing @ current_offset[" 
                                  + curr_offset 
                                  + "] "
                                  + write_buff.Length
                                  + " bytes "
                                  + "into row sequence["
                                  + curr_sequence
                                  + "] ");
                // adjust offsets.
                curr_offset += write_buff.Length;
                bytes_to_write -= write_buff.Length;
                curr_sequence++;
            }
            stTA.Update(stDS);
            Console.WriteLine();
            Console.WriteLine();
        }
        static void ReadItBack()
        {
            // get our data..
            SerializedTestDS stDS = new SerializedTestDS();
            SerializedTestDSTableAdapters.SerializedTestTableAdapter stTA = 
                new SerializedTestDSTableAdapters.SerializedTestTableAdapter();
            
            
            stTA.Fill(stDS.SerializedTest,1);

            SerializedTestDS.SerializedTestDataTable stTbl = 
                stDS.SerializedTest;
            byte [] final_buff = new byte[stTbl.Rows.Count * BIN_COLUMN_SIZE];
            int curr_offset = 0;
            foreach(SerializedTestDS.SerializedTestRow stRow in stTbl.Rows)
            {
                byte[] currBuff = stRow.ObjectData;
                Console.Write("UserID[" + stRow.UserID + "] ");
                Console.Write("sequence[" + stRow.sequence + "] ");
                Console.WriteLine("buffsize[" + currBuff.Length + "]");
                
                DumpBuffer(currBuff);
                
                for (int currByte = 0;
                     currByte < currBuff.Length;
                     currByte++)
                {
                    final_buff[curr_offset] = currBuff[currByte];
                    curr_offset++;
                }
                Console.WriteLine();
                Console.WriteLine();
            }
            
            // deserialize and print..
            MemoryStream ms = new MemoryStream(final_buff);
            IFormatter formatter = new BinaryFormatter();
            MyContainer my_c = (MyContainer) formatter.Deserialize(ms);
            Console.WriteLine(my_c.ToString());
        
        }
        static void DumpBuffer(byte [] buffer)
        {
            for (int currByte = 0;
                 currByte < buffer.Length;
                 currByte++)
            {
                if(     (currByte != 0      )
                    &&  ((currByte %16) == 0)   )
                {
                    Console.WriteLine();
                }
                Console.Write(String.Format("{0:X2} ",buffer[currByte]));
            }
            Console.WriteLine();
            Console.WriteLine();
        }
    }
}
