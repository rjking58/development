using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace ObjectsToDB
{
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
                m_c2Ary.Add(new Contained2(currval+10));
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
       
        
        static void Main(string[] args)
        {
            MyContainer mc = new MyContainer();
            Console.WriteLine(mc.ToString());
            
            Console.WriteLine("Start read of db..");
            
            // actually picked this up by clicking on the data connections entry for
            // the DB, and using the string from the properties pane.
            SqlConnectionStringBuilder csBuilder = 
                new SqlConnectionStringBuilder();
            csBuilder.DataSource = @"79-RKING2\RKING";
            csBuilder.InitialCatalog = "test_one";
            csBuilder.UserID = "RKING";
            csBuilder.Password = "rking5GGH@";
            SqlConnection cn = new SqlConnection(csBuilder.ConnectionString);
            
            DataSet SerializedTestDS = new DataSet("SerializedTest");

            SqlDataAdapter SerializedTestAdapter = 
                new SqlDataAdapter("select UserID,Sequence,ObjectData from test_one.dbo.SerializedTest order by sequence",
                                   cn);
      
//            SqlCommandBuilder cb = new SqlCommandBuilder(SerializedTestAdapter);   
            
//            Console.WriteLine(cb.GetInsertCommand().CommandText);
//            Console.WriteLine(cb.GetUpdateCommand().CommandText);
                                   
#if true
            string STInsert = 
                    "insert into test_one.dbo.SerializedTest "
                +   "  (userID,sequence,objectData) "
                +   "values (@userID,@objectData,@sequence);";
            SerializedTestAdapter.InsertCommand = new SqlCommand(STInsert,cn);
            SqlParameterCollection pc = SerializedTestAdapter.InsertCommand.Parameters;
            pc.Add("@userID",SqlDbType.Decimal,0,"userID");
            pc.Add("@sequence",SqlDbType.Decimal,0,"sequence");
            pc.Add("@objectData",SqlDbType.Binary,4000,"objectData");
            
            string STUpdate = 
                    "update test_one.dbo.SerializedTest "
                +   " set objectData = @objectData, sequence = @sequence_new, userID = @userID_new"
                +   " where userID = @userID_old and sequence = @sequence_old;";
            SerializedTestAdapter.UpdateCommand = new SqlCommand(STUpdate,cn);
            pc = SerializedTestAdapter.UpdateCommand.Parameters;
            pc.Add("@userID_new",SqlDbType.Decimal,0,"userID");
            pc.Add("@sequence_new",SqlDbType.Decimal,0,"sequence");
            pc.Add("@objectData",SqlDbType.Binary,4000,"objectData");
            SqlParameter p = pc.Add("@sequence_old",SqlDbType.Decimal,0,"sequence");
            p.SourceVersion = DataRowVersion.Original;
            p = pc.Add("@userID_old",SqlDbType.Decimal,0,"userID");
            p.SourceVersion = DataRowVersion.Original;

            string STDelete = 
                    "delete from test_one.dbo.SerializedTest "
                    + "where userID = @userID and sequence = @sequence;";
            SerializedTestAdapter.DeleteCommand = new SqlCommand(STDelete,cn);
            pc = SerializedTestAdapter.DeleteCommand.Parameters;
            pc.Add("@userID",SqlDbType.Decimal,0,"userID");
            pc.Add("@sequence",SqlDbType.Decimal,0,"sequence");
                      
            
#endif
            SerializedTestAdapter.Fill(SerializedTestDS,"SerializedTest");
            SerializedTestAdapter.FillSchema(SerializedTestDS,SchemaType.Source);

            PrintDataSet(SerializedTestDS);
            
            DataTable SerializeTestTbl = SerializedTestDS.Tables["SerializedTest"];
            DataRow [] drows = SerializeTestTbl.Select("UserID = 1");
            foreach(DataRow dr in drows)
            {
                dr.Delete();
            }
            DataRow row_to_insert = SerializeTestTbl.NewRow();
            row_to_insert["UserID"] = 1;
            row_to_insert["ObjectData"] = new byte [] {1,2,3,4};
            row_to_insert["sequence"] = 1;
            SerializeTestTbl.Rows.Add(row_to_insert);
            // accept changes is for OFFLINE behavior only.
            //SerializeTestTbl.AcceptChanges();
            
            cn.Open();
            SerializedTestAdapter.Update(SerializedTestDS.Tables["SerializedTest"]);
            cn.Close();
            
            PrintDataSet(SerializedTestDS);
        }
        
        static void PrintDataSet(DataSet ds)
        {
            Console.WriteLine("Tables in '{0}' DataSet.\n",ds.DataSetName);
            foreach(DataTable dt in ds.Tables)
            {
                Console.WriteLine("{0} Table.\n",dt.TableName);
                for(int curCol = 0; curCol < dt.Columns.Count; curCol++)
                {
                    Console.Write(
                        String.Format("{0,15}",dt.Columns[curCol].ColumnName.Trim()));
                }
                Console.WriteLine();
                Console.WriteLine("-------------------------------------------------------------");
                for(int curRow = 0; curRow < dt.Rows.Count; curRow++)
                {
                    for(int curCol = 0; curCol < dt.Columns.Count; curCol++)
                    {
                        Console.Write(
                            String.Format("{0,15}",dt.Rows[curRow][curCol].ToString().Trim()));
                    }
                    Console.WriteLine();
                }
            }
        }
        
    }
}
