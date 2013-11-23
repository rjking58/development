using System;
using System.Collections.Generic;
using System.Text;
using System.Data;


namespace ReadXMLSchemaAndDataTest
{
    class Program
    {
        static void Main(string[] args)
        {
            DataSet ConfigsDS = new DataSet("Configurations");
            
            ConfigsDS.ReadXmlSchema("ADOBuiltConfigurationsSchema.xsd");
            ConfigsDS.ReadXml("ADOBuiltConfigurations.xml");
            //ConfigsDS.ReadXmlSchema("test_one_Schema.xsd");
            //ConfigsDS.ReadXml("test_one.xml");
            Console.WriteLine("Constraints enabled:" + ConfigsDS.EnforceConstraints);
            PrintDataSet(ConfigsDS);
            
            // now traverse our relations to make sure its all there..
            
            foreach(DataTable dt in ConfigsDS.Tables)
            {
                Console.WriteLine("Table:" + dt.TableName);
                for(int currConstraint = 0;
                    currConstraint < dt.Constraints.Count;
                    currConstraint++)
                {
                    Console.WriteLine("ConstraintName:" + dt.Constraints[currConstraint].ConstraintName);
                    Console.WriteLine("PropertyCount:" + dt.Constraints[currConstraint].ExtendedProperties.Count);
                    foreach (string s in  dt.Constraints[currConstraint].ExtendedProperties)
                    {   
                        Console.WriteLine(s);
                    }
                }
            }

            Console.WriteLine("Relations.Count:" + ConfigsDS.Relations.Count);
            for(int currRelation = 0;
                currRelation < ConfigsDS.Relations.Count;
                currRelation++)
            {
                Console.WriteLine("Relation[" + ConfigsDS.Relations[currRelation].RelationName + "]");
                for(int currCol = 0;
                    currCol < ConfigsDS.Relations[currRelation].ParentColumns.Length;
                    currCol++)
                {
                    Console.WriteLine(ConfigsDS.Relations[currRelation].ParentTable
                                      + "."
                                      + ConfigsDS.Relations[currRelation].ParentColumns[currCol].ColumnName
                                      + " -> "
                                      + ConfigsDS.Relations[currRelation].ChildTable
                                      + "."                                      
                                      + ConfigsDS.Relations[currRelation].ChildColumns[currCol].ColumnName
                                      );
//ConfigsDS.Relations[currRelation].ParentColumns[currCol].
                }
                
                Console.WriteLine();
            }

            // test constraints by trying to add non existant user configuration..
            DataRow newRow = ConfigsDS.Tables["Devices"].NewRow();
            newRow["UserID"] = 4;
            newRow["ConfigID"] = 4;
            newRow["DeviceID"] = 4;
            newRow["DeviceName"] = "Device 4 of Config 4 of User 4";
            ConfigsDS.Tables["Devices"].Rows.Add(newRow);
            ConfigsDS.AcceptChanges();
            
            PrintDataSet(ConfigsDS);
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
