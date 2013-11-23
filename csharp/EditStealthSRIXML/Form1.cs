using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;

namespace EditStealthSRIXML
{
    public partial class Form1:Form
    {
        private bool        m_open = false;
        private string      m_filename = "";
        private ConfigInfo  m_cfg = null;


        /// <summary>
        /// class for managing a list of previously opened files..
        /// </summary>
        [Serializable]
        class ConfigInfo 
        {
            List<FileInfo> m_fileList = new List<FileInfo>();
            /// <summary>
            /// add an entry.  This algorithm:
            /// 1. checks to make sure the file hasn't been added before.
            /// 2. updates the GUI with the new list.
            /// 3. if the number of entries exceeds 10, removes the last entry
            ///    in the list
            /// possible improvements:
            ///   currently, the list is not reordered based on usage.. this could
            ///   be done so that a 'most recently used' paradigm is applied to the
            ///   previously opened files.
            ///
            ///   currently an assumption is made that menu item #5 is the start for our saved
            ///   file list.  If the number of menu items changes on the file menu, this algorithm
            ///   must change too.. this could be made meta-data driven.
            /// </summary>
            /// <param name="new_fi">file name to add</param>
            /// <param name="f">form containing the menu to adjust.</param>
            /// <param name="tsmi">tool strip item that must be adjusted.</param>
            public void AddEntry(FileInfo new_fi,
                                 Form1 f,
                                 ToolStripMenuItem tsmi)
            {
                bool filenameFound = false;
                foreach(FileInfo fi in m_fileList)
                {
                    if(fi.FullName == new_fi.FullName)
                    {
                        filenameFound = true;
                        break;
                    }
                }
                if(!filenameFound)
                {
                    if(m_fileList.Count >= 10)
                    {
                        m_fileList.RemoveAt(0);
                    }
                    m_fileList.Add(new_fi);
                }
                
                AddMenuStripItems(f,
                                  tsmi);
                f.SaveConfigInfo();
            }
            
            private void ClearMenuItems(ToolStripMenuItem tsmi)
            {
                if(tsmi.DropDownItems.Count > 4)
                {
                    int last_index = tsmi.DropDownItems.Count - 1;
                    int items_to_delete = tsmi.DropDownItems.Count - 4;
                    for(int currItem = 0;
                        currItem < items_to_delete;
                        currItem++)
                    {
                        tsmi.DropDownItems.RemoveAt(last_index);
                        last_index--;
                    }
                }
            }
            
            public void AddMenuStripItems(Form1 f,
                                          ToolStripMenuItem tsmi)
            {
                ClearMenuItems(tsmi);
                
                for(int currItem = (m_fileList.Count - 1);
                    currItem >=0;
                    currItem --)
                {
                    int len = m_fileList[currItem].FullName.Length;
                    string finalName = "";
                    if(len > 20)
                    {
                        finalName = "..." + m_fileList[currItem].FullName.Substring(len - 40,40);
                    }
                    else
                    {
                        finalName = m_fileList[currItem].FullName;
                    }
                    ToolStripMenuItem tsi = new ToolStripMenuItem(finalName);
                    tsi.Click += new EventHandler(f.OpenOldFile_Click);
                    tsi.Tag = m_fileList[currItem].FullName;
                    tsmi.DropDownItems.Add(tsi);
                }
            }
        }
    
        private string ConfigFileName = "EditStealthSRI.cfg";
        
        public void GetConfigInfo()
        {
            string FullPathConfigFileName = 
                Application.StartupPath + @"\" + ConfigFileName;
            Stream file;
            IFormatter formatter;
            if (!File.Exists(FullPathConfigFileName))
            {
                m_cfg = new ConfigInfo();
            }
            else
            {
                file = File.Open(FullPathConfigFileName, FileMode.Open);

                // Create a formatter object based on command line arguments
                formatter = (IFormatter)new BinaryFormatter();

                // Deserialize the object graph from stream
                try
                {
                    m_cfg = formatter.Deserialize(file) as ConfigInfo;

                    // Tests like this are relevant in projects which 
                    // serialize multiple object types
                    if (m_cfg == null)
                    {
                        MessageBox.Show("The deserialized object graph is not a ConfigInfo.");
                    }
                }
                // Handler for BinaryFormatter exception
                catch (SerializationException)
                {
                    MessageBox.Show("Could not deserialize file.  Check that the input file is valid and the requested serialization format is correct.");
                }
                // Handler for SoapException
                catch (ArgumentException)
                {
                    MessageBox.Show("Could not deserialize file.  Check that the input file is valid and the requested serialization format is correct.");
                }
                // All done
                file.Close();
            }
        }
        public void SaveConfigInfo()
        {
            string FullPathConfigFileName = 
                Application.StartupPath + @"\" + ConfigFileName;
            Stream file;
            IFormatter formatter;
            
            file = File.Open(FullPathConfigFileName, FileMode.Create);
            // Create a formatter object based on command line arguments
            formatter = (IFormatter)new BinaryFormatter();
            // Serialize the object graph to stream
            formatter.Serialize(file, m_cfg);
            // All done
            file.Close();
        }
            
        public void OpenOldFile_Click(object sender,EventArgs e)
        {
            if(sender is ToolStripMenuItem)
            {
                ToolStripMenuItem tsmi = (ToolStripMenuItem) sender;
                stealthUSB_SRI.Clear();
                stealthUSB_SRI.ReadXml((string) tsmi.Tag);
                setOpenFileInformation((string) tsmi.Tag);
                //MessageBox.Show((string) tsmi.Tag);
            }
        }
 
        void setOpenFileInformation(string filename)
        {
                m_open = true;
                m_filename = filename;
                
                this.Text = "Edit Stealth SRI XML - [" + filename + "]";
        }
   
        public Form1()
        {
            InitializeComponent();
            GetConfigInfo();
            
            // init the menus..
            m_cfg.AddMenuStripItems(this,fileToolStripMenuItem);
        }

        private void Form1_Load(object sender,EventArgs e)
        {

        }

        private void openToolStripMenuItem_Click(object sender,EventArgs e)
        {
            // show file explorer.. read xml if file exists..
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "c:\\" ;
            openFileDialog1.Filter = "xml files (*.xml)|*.xml" ;
            openFileDialog1.FilterIndex = 2 ;
            openFileDialog1.RestoreDirectory = false ;

            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                stealthUSB_SRI.Clear();
                stealthUSB_SRI.ReadXml(openFileDialog1.FileName);
                setOpenFileInformation(openFileDialog1.FileName);
                
                m_cfg.AddEntry(new FileInfo(m_filename),this,fileToolStripMenuItem);
            }
            dataGridView1.Refresh();
            dataGridView2.Refresh();
            dataGridView3.Refresh();
            dataGridView4.Refresh();
            dataGridView5.Refresh();
            dataGridView6.Refresh();
            dataGridView7.Refresh();
            dataGridView8.Refresh();
            dataGridView10.Refresh();
            
        }
        public void SaveXML()
        {
            updateFormTextIfChanges();
            if(m_open)
            {
                stealthUSB_SRI.WriteXml(m_filename);
            }
        }

        private void saveToolStripMenuItem_Click(object sender,EventArgs e)
        {
            dataGridView1.EndEdit();
            dataGridView2.EndEdit();
            dataGridView3.EndEdit();
            dataGridView4.EndEdit();
            dataGridView5.EndEdit();
            dataGridView6.EndEdit();
            dataGridView7.EndEdit();
            dataGridView8.EndEdit();
            dataGridView10.EndEdit();
            
            SaveXML();
            this.Text = "Edit Stealth SRI XML - [" + m_filename + "]";
        }
        private void updateFormTextIfChanges()
        {
            // guarantee that data in the binding source is flushed to the dataset.
            ValidKeyNamesBindingSrc.EndEdit();
            KeyMapBindingSrc.EndEdit();
            ModeGroupingBindingSrc.EndEdit();
            StealthPickMapBindingSrc.EndEdit();
            DeviceGroupingBindingSrc.EndEdit();
            GeneralInfoBindingSrc.EndEdit();
            KeyGroupingActivityBindingSrc.EndEdit();
            KeyGroupingChannelBindingSrc.EndEdit();
            KeyGroupingDigitBindingSrc.EndEdit();
            KeyGroupingModeBindingSrc.EndEdit();
            KeyGroupingSNSBindingSrc.EndEdit();
            KeyGroupingSoftkeyBindingSrc.EndEdit();
            KeyGroupingTransportBindingSrc.EndEdit();
            KeyGroupingVolumeBindingSrc.EndEdit();
            FeatureSettingsNumericBindingSrc.EndEdit();
            RecordTypesSupportedBindingSrc.EndEdit();
            
            //// check dataset for changes.
            
            if(stealthUSB_SRI.HasChanges())
            {
                this.Text = "Edit Stealth SRI XML - [" + m_filename + "*]";
            }
        }

        private void dataGridView6_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView5_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView4_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView3_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView2_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView1_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void saveAsToolStripMenuItem_Click(object sender,EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "xml files (*.xml)|*.xml" ;
            sfd.FilterIndex = 2 ;
            sfd.RestoreDirectory = false ;

            if(sfd.ShowDialog() == DialogResult.OK)
            {
                
                stealthUSB_SRI.WriteXml(sfd.FileName);
                m_open = true;
                m_filename = sfd.FileName;
                this.Text = "Edit Stealth SRI XML - [" + sfd.FileName + "]";
            }

            this.dataGridView1.Refresh();
            this.dataGridView2.Refresh();
            this.dataGridView3.Refresh();
            this.dataGridView4.Refresh();
            this.dataGridView5.Refresh();
            this.dataGridView6.Refresh();
            this.dataGridView10.Refresh();
        }

        private void dataGridView2_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void tabPage8_Click(object sender,EventArgs e)
        {

        }

        private void dataGridView7_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void label5_Click(object sender,EventArgs e)
        {

        }

        private void dataGridView11_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void label7_Click(object sender,EventArgs e)
        {

        }

        private void dataGridView13_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void label8_Click(object sender,EventArgs e)
        {

        }

        private void dataGridView3_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void KeyGroupingDigitBindingSrc_CurrentChanged(object sender,EventArgs e)
        {

        }

        private void KeyGroupingVolumeBindingSrc_CurrentChanged(object sender,EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void fileToolStripMenuItem_Click(object sender,EventArgs e)
        {

        }
    }
}