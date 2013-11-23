using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ConfigurationsDSWithVSTools
{
    public partial class Form1:Form
    {
        const int LIST_BOX_LINES_MAX = 200;
        private Queue<string> m_msgs = new Queue<string>();
        
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender,EventArgs e)
        {

        }
        
        private void AddListBoxMessage(string str)
        {
            m_msgs.Enqueue(str);
            // keep list contained.
            if(m_msgs.Count > LIST_BOX_LINES_MAX)
            {
                m_msgs.Dequeue();
            }
            ListBoxMessageUpdate();
        }
        private void ListBoxMessageUpdate()
        {
            lstbox_main.BeginUpdate();
            lstbox_main.Items.Clear();
            lstbox_main.Items.AddRange(m_msgs.ToArray());
            lstbox_main.EndUpdate();
        }

        private void btn_DoTest_Click(object sender,EventArgs e)
        {
            NewConfigRow(RemoteConfigurationsDS,
                         1,
                         1,
                         "Dvc 1 of Config 1");
            NewConfigRow(RemoteConfigurationsDS,
                         1,
                         2,
                         "Dvc 2 of Config 1");

            NewDeviceRow(RemoteConfigurationsDS,
                         1,1,1,"Device 1 for User 1 Config 1");
            NewDeviceRow(RemoteConfigurationsDS,
                         1,1,2,"Device 2 for User 1 Config 1");
            NewDeviceRow(RemoteConfigurationsDS,
                         2,2,2,"Device 2 for User 2 Config 2");
                         
            NewDeviceKeyRow(RemoteConfigurationsDS,
                            1,1,1,23,"key #23");
            NewDeviceKeyRow(RemoteConfigurationsDS,
                            1,1,1,24,"key #24");
            NewDeviceKeyRow(RemoteConfigurationsDS,
                            1,1,1,37,"key #37");
            NewDeviceKeyRow(RemoteConfigurationsDS,
                            4,4,4,37,"key #37");
                            
            PrintDataSet(RemoteConfigurationsDS);  
            RemoteConfigurationsDS.WriteXmlSchema("ADOBuiltConfigurationsSchema.xsd");
            RemoteConfigurationsDS.WriteXml("ADOBuiltConfigurations.xml");
        }
        bool NewConfigRow(DataSet ds,
                          ulong UserID,
                          ushort ConfigID, 
                          string ConfigName)
        {
            bool retVal = true;
            try
            {
                
                DataRow newRow = ds.Tables["Configurations"].NewRow();
                newRow["UserID"] = UserID;
                newRow["ConfigID"] = ConfigID;
                newRow["ConfigName"] = ConfigName;
                ds.Tables["Configurations"].Rows.Add(newRow);
                ds.Tables["Configurations"].AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            return retVal;
        }
        bool NewDeviceRow(DataSet ds,
                          ulong UserID,
                          ushort ConfigID, 
                          ushort DeviceID,
                          string DeviceName)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ds.Tables["Devices"];
                DataRow newRow = dt.NewRow();
                newRow["UserID"] = UserID;
                newRow["ConfigID"] = ConfigID;
                newRow["DeviceID"] = DeviceID;
                newRow["DeviceName"] = DeviceName;
                
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            return retVal;
        }
        
        bool NewDeviceKeyRow(DataSet ds,
                             ulong   UserID,
                             ushort  ConfigID, 
                             ushort  DeviceID,
                             ushort  KeyID,
                             string  KeyName)
        {
            bool retVal = true;
            try
            {
                DataTable dt = ds.Tables["DeviceKeys"];
                DataRow newRow = dt.NewRow();
                newRow["UserID"] = UserID;
                newRow["ConfigID"] = ConfigID;
                newRow["DeviceID"] = DeviceID;
                newRow["KeyID"] = KeyID;
                newRow["KeyName"] = KeyName;
                
                dt.Rows.Add(newRow);
                dt.AcceptChanges();
            }
            catch(System.Data.InvalidConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            catch(System.Data.ConstraintException e)
            {
                retVal = false;
                AddListBoxMessage(e.Message);
            }
            return retVal;
        }
        
        void PrintDataSet(DataSet ds)
        {
            StringBuilder sb = null;
            AddListBoxMessage(String.Format("Tables in '{0}' DataSet.",ds.DataSetName));
            foreach(DataTable dt in ds.Tables)
            {
                AddListBoxMessage("");
                AddListBoxMessage(String.Format("{0} Table.",dt.TableName));
                sb = new StringBuilder();
                for(int curCol = 0; curCol < dt.Columns.Count; curCol++)
                {
                    sb.Append(
                        String.Format("{0,25}",dt.Columns[curCol].ColumnName.Trim()));
                }
                AddListBoxMessage(sb.ToString());
                AddListBoxMessage("---------------------------------------------------------------------------------------");
                
                
                for(int curRow = 0; curRow < dt.Rows.Count; curRow++)
                {
                    sb = new StringBuilder();
                    for(int curCol = 0; curCol < dt.Columns.Count; curCol++)
                    {
                        sb.Append(
                            String.Format("{0,25}",dt.Rows[curRow][curCol].ToString().Trim()));
                    }
                    AddListBoxMessage(sb.ToString());
                }
            }
        }
        
    }
}