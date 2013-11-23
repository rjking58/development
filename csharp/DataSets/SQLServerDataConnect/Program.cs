using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace SQLServerDataConnect
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start read of db..");
            
            SqlConnection cn = new SqlConnection();
            // actually picked this up by clicking on the data connections entry for
            // the DB, and using the string from the properties pane.
            SqlConnectionStringBuilder csBuilder = 
                new SqlConnectionStringBuilder();
            csBuilder.DataSource = @"79-RKING2\RKING";
            csBuilder.InitialCatalog = "test_one";
            csBuilder.UserID = "RKING";
            csBuilder.Password = "rking5GGH@";

            cn.ConnectionString = csBuilder.ConnectionString;
            cn.Open();
            
            string strSQL = "select * from Devices";
            SqlCommand myCommand = new SqlCommand(strSQL,cn);
            //SqlDataAdapter myDataAdapter = new SqlDataAdapter(
            SqlDataReader myDataReader = 
                myCommand.ExecuteReader(CommandBehavior.CloseConnection);

            while(myDataReader.Read())
            {
#if false            
                Console.WriteLine("UserID: [{0}], ConfigID: [{1}], ConfigurationName: '{2}'",
                                  myDataReader["UserID"].ToString().Trim(),
                                  myDataReader["ConfigID"].ToString().Trim(),
                                  myDataReader["ConfigurationName"].ToString().Trim());
#endif
                // general access to all columns returned (so its not sensitive to table)
                for(int currField = 0; currField < myDataReader.FieldCount; currField++)
                {
                    Console.Write("{0} : {1}",
                                  myDataReader.GetName(currField),
                                  myDataReader.GetValue(currField));
                    if (currField != (myDataReader.FieldCount - 1))
                    {
                        Console.Write(",  ");
                    }
                }
                Console.WriteLine();
            }
            
            myDataReader.Close();
        }
    }
}
