using System;
using System.Collections.Generic;
using System.Text;
using System.Data;

namespace DataWiz2
{
    class Program
    {
        static void Main(string[] args)
        {
            test_oneDataSet tst1DS = 
                new test_oneDataSet();
                
            
            test_oneDataSetTableAdapters.ConfigurationsTableAdapter configsTA = 
                new DataWiz2.test_oneDataSetTableAdapters.ConfigurationsTableAdapter();
                
            configsTA.Fill(tst1DS.Configurations);
            
            test_oneDataSetTableAdapters.deviceKeysTableAdapter deviceKeysTA = 
                new DataWiz2.test_oneDataSetTableAdapters.deviceKeysTableAdapter();
            deviceKeysTA.Fill(tst1DS.deviceKeys);
            
            test_oneDataSetTableAdapters.DevicesTableAdapter DevicesTA = 
                new DataWiz2.test_oneDataSetTableAdapters.DevicesTableAdapter();
            DevicesTA.Fill(tst1DS.Devices);
            
            test_oneDataSetTableAdapters.LearnedKeysTableAdapter LearnedKeysTA = 
                new DataWiz2.test_oneDataSetTableAdapters.LearnedKeysTableAdapter();
            LearnedKeysTA.Fill(tst1DS.LearnedKeys);
            
            test_oneDataSetTableAdapters.UsersTableAdapter UsersTA = 
                new DataWiz2.test_oneDataSetTableAdapters.UsersTableAdapter();
            UsersTA.Fill(tst1DS.Users);

            tst1DS.WriteXmlSchema("configs.xsd");
            tst1DS.WriteXml("configs.xml");
            
            Console.WriteLine("EnforceConstraints[" + tst1DS.EnforceConstraints + "]");
            // test constraints by trying to add non existant user configuration..
            DataRow newRow = tst1DS.Configurations.NewRow();
            newRow["UserID"] = 4;
            newRow["ConfigID"] = 4;
            tst1DS.Configurations.Rows.Add(newRow);
            tst1DS.AcceptChanges();
            PrintDataSet(tst1DS);
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
