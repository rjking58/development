using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace DataSetWizardTest
{
    class Program
    {
        static void Main(string[] args)
        {
            test_oneWZDataSet test_oneDS = 
                new test_oneWZDataSet();
            test_oneWZDataSetTableAdapters.ConfigurationsTableAdapter configsTA = 
                new test_oneWZDataSetTableAdapters.ConfigurationsTableAdapter();
            test_oneWZDataSetTableAdapters.DevicesTableAdapter devsTA = 
                new test_oneWZDataSetTableAdapters.DevicesTableAdapter();
            test_oneWZDataSetTableAdapters.deviceKeysTableAdapter devkeysTA = 
                new test_oneWZDataSetTableAdapters.deviceKeysTableAdapter();
            test_oneWZDataSetTableAdapters.UsersTableAdapter usersTA = 
                new test_oneWZDataSetTableAdapters.UsersTableAdapter();

            configsTA.Fill(test_oneDS.Configurations);
            devsTA.Fill(test_oneDS.Devices);
            devkeysTA.Fill(test_oneDS.deviceKeys);
            usersTA.Fill(test_oneDS.Users);
            
            PrintDataSet(test_oneDS);            
            
            test_oneDS.WriteXml("test_one.xml");
            test_oneDS.WriteXmlSchema("test_one_Schema.xsd");

            
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
