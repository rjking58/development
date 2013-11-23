using System;
using System.Collections.Generic;
using System.Text;
using System.Data;

namespace HandBuiltConstraints
{
    class Program
    {
        static DataSet ConfigurationsDS = new DataSet("RemoteConfiguration");
        static void Main(string[] args)
        {
            BuildSchema();

            // add two rows.
            Console.WriteLine("Add First Config:" + NewConfigRow(1,
                                                                 "Config 1"));
            Console.WriteLine("Add Second Config:" + NewConfigRow(2,
                                                                  "Config 2"));
            Console.WriteLine("Add Third Config:" + NewConfigRow(2,
                                                                 "Config 2(again)"));
            Console.WriteLine("Add First Device:" + NewDevicesRow(2,
                                                                  1,
                                                                  "Config 2/Dev 1"));
            Console.WriteLine("Add Second Device:" + NewDevicesRow(1,
                                                                   1,
                                                                   "Config 1/Dev 1"));
            Console.WriteLine("Add Third Device:" + NewDevicesRow(3,
                                                                  1,
                                                                  "Config 3/Dev 1 (FK Error)"));
            Console.WriteLine("Add Key1:" + NewDeviceKeysRow(1,
                                                             1,
                                                             33,
                                                             0,
                                                             false,
                                                             "Config 1/Dev 1/Key33/no learned"));
            Console.WriteLine("Add Key1:" + NewDeviceKeysRow(1,
                                                             4,
                                                             33,
                                                             0,
                                                             false,
                                                             "Config 1/Dev 4/Key33/no learned (FK Error)"));
            
            Console.WriteLine("Add Key1:" + NewLearnedKeysRow(1,
                                                              1,
                                                              2,
                                                              new byte[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
                                                                         11,12,13,14,15,16,17,18,19,20}));
            
            ConfigurationsDS.Tables["Configurations"].AcceptChanges();
            
            ConfigurationsDS.WriteXmlSchema("configurations.xsd");
            ConfigurationsDS.WriteXml("configurations.xml");
        
            PrintDataSet(ConfigurationsDS);
            
            DataRow [] rows = ConfigurationsDS.Tables["LearnedKeys"].Select();
            foreach(DataRow dr in rows)
            {
                Console.Write("ConfigID[" + dr["ConfigID"].ToString() + "]");
                Console.Write("  DeviceID[" + dr["DeviceID"].ToString() + "]");
                Console.WriteLine("  LearnedID[" + dr["LearnedKey"].ToString() + "]");
                byte [] fetchedArray = (byte []) dr["LearnedData"];
                for(int currByte = 0;
                    currByte < fetchedArray.Length;
                    currByte++)
                {
                    if((currByte != 0) && ((currByte % 16) == 0))
                    {
                        Console.WriteLine();
                    }
                    Console.Write(String.Format("{0:X2} ",fetchedArray[currByte]));
                }
                Console.WriteLine();
                Console.WriteLine();
            }
        }
        
        static bool NewConfigRow(ushort ConfigID, 
                                 string ConfigName)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ConfigurationsDS.Tables["Configurations"];
                DataRow newRow = dt.NewRow();
                newRow["ConfigID"] = ConfigID;
                newRow["ConfigName"] = ConfigName;
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            return retVal;
        }
        static bool NewDevicesRow(ushort ConfigID, 
                                 ushort DeviceID,
                                  string DeviceName)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ConfigurationsDS.Tables["Devices"];
                DataRow newRow = dt.NewRow();
                newRow["ConfigID"] = ConfigID;
                newRow["DeviceID"] = DeviceID;
                newRow["DeviceName"] = DeviceName;
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            return retVal;
        }
        static bool NewDeviceKeysRow(ushort ConfigID, 
                                     ushort DeviceID,
                                     ushort KeyID,
                                     ushort LearnedKey,
                                     bool   LearnedValid,
                                     string KeyName)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ConfigurationsDS.Tables["DeviceKeys"];
                DataRow newRow = dt.NewRow();
                newRow["ConfigID"] = ConfigID;
                newRow["DeviceID"] = DeviceID;
                newRow["KeyID"] = KeyID;
                newRow["KeyName"] = KeyName;
                if(LearnedValid)
                {
                    newRow["LearnedKey"] = LearnedKey;
                }
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            return retVal;
        }

        static bool NewLearnedKeysRow(ushort    ConfigID, 
                                      ushort    DeviceID,
                                      ushort    LearnedKey,
                                      byte []   LearnedData)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ConfigurationsDS.Tables["LearnedKeys"];
                DataRow newRow = dt.NewRow();
                newRow["ConfigID"] = ConfigID;
                newRow["DeviceID"] = DeviceID;
                newRow["LearnedKey"] = LearnedKey;
                newRow["LearnedData"] = LearnedData;
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                Console.WriteLine(e.Message);
            }
            return retVal;
        }
        
        static DataColumn MakeLearnedDataCol()
        {
            DataColumn dc = new DataColumn("LearnedData",typeof(byte[]));
            dc.Caption = "LearnedData";
            dc.ReadOnly = false;
            dc.AllowDBNull = false;
            dc.Unique = false;
            dc.ColumnMapping = MappingType.Element;
            return dc;
        }
        
        static DataColumn MakeIDCol(string name)
        {
            DataColumn dc = new DataColumn(name,typeof(ushort));
            dc.Caption = name;
            dc.ReadOnly = false;
            dc.AllowDBNull = false;
            dc.Unique = false;
            dc.ColumnMapping = MappingType.Attribute;
            return dc;
        }
        static DataColumn MakeNameCol(string name)
        {
            DataColumn dc = new DataColumn(name,typeof(string));
            dc.Caption = name;
            dc.ReadOnly = false;
            dc.AllowDBNull = false;
            dc.Unique = false;
            dc.ColumnMapping = MappingType.Attribute;
            return dc;
        }
        
        static void BuildSchema()
        {
            ConfigurationsDS.ExtendedProperties["TimeStamp"] = DateTime.Now;
            ConfigurationsDS.ExtendedProperties["Company"] = "UEI training";
            // configurations
            DataColumn ConfigIDCol = MakeIDCol("ConfigID");
            DataColumn ConfigNameCol = MakeNameCol("ConfigName");
            
            DataTable ConfigurationsTbl = new DataTable("Configurations");
            ConfigurationsTbl.Columns.AddRange(new DataColumn[] {ConfigIDCol,
                                                                 ConfigNameCol}
                                              );
            ConfigurationsTbl.PrimaryKey = new DataColumn[] {ConfigIDCol};
            ConfigurationsDS.Tables.Add(ConfigurationsTbl);
            
            // Devices
            ConfigIDCol = MakeIDCol("ConfigID");
            DataColumn DeviceIDCol = MakeIDCol("DeviceID");
            DataColumn DeviceNameCol = MakeNameCol("DeviceName");
            
            DataTable DevicesTbl = new DataTable("Devices");
            DevicesTbl.Columns.AddRange(new DataColumn[] {ConfigIDCol,
                                                          DeviceIDCol,
                                                          DeviceNameCol}
                                              );
            DevicesTbl.PrimaryKey = new DataColumn[] {ConfigIDCol,
                                                      DeviceIDCol};
            ConfigurationsDS.Tables.Add(DevicesTbl);

            //DeviceKeys
            ConfigIDCol = MakeIDCol("ConfigID");
            DeviceIDCol = MakeIDCol("DeviceID");
            DataColumn KeyIDCol = MakeIDCol("KeyID");
            DataColumn KeyNameCol = MakeNameCol("KeyName");
            DataColumn LearnedKeyCol = MakeIDCol("LearnedKey");
            LearnedKeyCol.AllowDBNull = true;
            
            DataTable DeviceKeysTbl = new DataTable("DeviceKeys");
            DeviceKeysTbl.Columns.AddRange(new DataColumn[] {ConfigIDCol,
                                                             DeviceIDCol,
                                                             KeyIDCol,
                                                             KeyNameCol,
                                                             LearnedKeyCol}
                                              );
            DeviceKeysTbl.PrimaryKey = new DataColumn[] {ConfigIDCol,
                                                         DeviceIDCol,
                                                         KeyIDCol};
            ConfigurationsDS.Tables.Add(DeviceKeysTbl);
            
            //LearnedKeys
            ConfigIDCol = MakeIDCol("ConfigID");
            DeviceIDCol = MakeIDCol("DeviceID");
            LearnedKeyCol = MakeIDCol("LearnedKey");
            LearnedKeyCol.AllowDBNull = false;
            DataColumn LearnedDataCol = MakeLearnedDataCol();
            
            DataTable LearnedKeysTbl = new DataTable("LearnedKeys");
            LearnedKeysTbl.Columns.AddRange(new DataColumn[] {ConfigIDCol,
                                                              DeviceIDCol,
                                                              LearnedKeyCol,
                                                              LearnedDataCol}
                                              );
            LearnedKeysTbl.PrimaryKey = new DataColumn[] {ConfigIDCol,
                                                          DeviceIDCol,
                                                          LearnedKeyCol};
            ConfigurationsDS.Tables.Add(LearnedKeysTbl);
            
            //data relations...
            //DevicesToConfigurations
            DataColumn[] ConfigurationsPKCols = new DataColumn[] {ConfigurationsDS.Tables["Configurations"].Columns["ConfigID"] };
            DataColumn[] DevicesFKCols = new DataColumn[] {ConfigurationsDS.Tables["Devices"].Columns["ConfigID"] };
            DataRelation dr = new DataRelation("DevicesToConfigurations",
                                               ConfigurationsPKCols,
                                               DevicesFKCols);
            ConfigurationsDS.Relations.Add(dr);
            
            DataColumn[] DevicesPKCols = new DataColumn[] {ConfigurationsDS.Tables["Devices"].Columns["ConfigID"],
                                                           ConfigurationsDS.Tables["Devices"].Columns["DeviceID"] };
            DataColumn[] DeviceKeysFKCols = new DataColumn[] {ConfigurationsDS.Tables["DeviceKeys"].Columns["ConfigID"],
                                                              ConfigurationsDS.Tables["DeviceKeys"].Columns["DeviceID"]  };
            dr = new DataRelation("DevicesKeysToDevices",
                                  DevicesPKCols,
                                  DeviceKeysFKCols);
            ConfigurationsDS.Relations.Add(dr);

            DevicesPKCols = new DataColumn[] {ConfigurationsDS.Tables["Devices"].Columns["ConfigID"],
                                              ConfigurationsDS.Tables["Devices"].Columns["DeviceID"] };
            DataColumn[] LearnedKeysFKCols = new DataColumn[] {ConfigurationsDS.Tables["LearnedKeys"].Columns["ConfigID"],
                                                               ConfigurationsDS.Tables["LearnedKeys"].Columns["DeviceID"]  };
            dr = new DataRelation("LearnedKeysToDevices",
                                  DevicesPKCols,
                                  LearnedKeysFKCols);
            ConfigurationsDS.Relations.Add(dr);
            
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
//            carIDColumn.AutoIncrement = true;
//            carIDColumn.AutoIncrementSeed = 0;
//            carIDColumn.AutoIncrementStep = 1;
//            carIDColumn.ColumnMapping = MappingType.Attribute;
    
}
