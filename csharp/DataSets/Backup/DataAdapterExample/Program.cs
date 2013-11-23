using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace DataAdapterExample
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start read of db..");
            
            // actually picked this up by clicking on the data connections entry for
            // the DB, and using the string from the properties pane.
            SqlConnectionStringBuilder csBuilder = 
                new SqlConnectionStringBuilder();
            csBuilder.DataSource = @"79-RKING2\RKING";
            csBuilder.InitialCatalog = "test_one";
            csBuilder.UserID = "RKING";
            csBuilder.Password = "rking5GGH@";
            
            DataSet devicesDS = new DataSet("Devices");
            SqlDataAdapter devicesAdapter = 
                new SqlDataAdapter("select * from Devices",csBuilder.ConnectionString);
            SqlDataAdapter ConfigurationsAdapter =
                new SqlDataAdapter("select * from Configurations",csBuilder.ConnectionString);
            devicesAdapter.Fill(devicesDS,"Devices");
            ConfigurationsAdapter.Fill(devicesDS,"Configurations");
            PrintDataSet(devicesDS);
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
