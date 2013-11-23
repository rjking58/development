using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DeviceImagesEditTest
{
    public partial class Form1:Form
    {
        private bool    m_open = false;
        private string  m_filename = "";
        private DeviceImagesDS deviceImagesDS;
                
        public Form1()
        {
            InitializeComponent();
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
                deviceImagesDS.ReadXml(openFileDialog1.FileName);
                m_open = true;
                m_filename = openFileDialog1.FileName;
                this.Text = "Edit Devices and Keys XML - [" + openFileDialog1.FileName + "]";
            }
            this.dataGridView1.Refresh();
            this.dataGridView2.Refresh();
            this.dataGridView3.Refresh();
            this.dataGridView4.Refresh();
        }

        public void SaveXML()
        {
            if(m_open)
            {
                deviceImagesDS.WriteXml(m_filename);
            }
        }

        private void saveToolStripMenuItem_Click(object sender,EventArgs e)
        {
            SaveXML();
            this.Text = "Edit Devices and Keys XML - [" + m_filename + "]";
        }

        private void dataGridView4_CellContentClick(object sender,DataGridViewCellEventArgs e)
        {

        }

        private void DevicesBindingSrc_ListChanged(object sender,ListChangedEventArgs e)
        {
            this.dataGridView1.EndEdit();
            this.dataGridView2.EndEdit();
            this.dataGridView3.EndEdit();
            this.dataGridView4.EndEdit();
            
            if(deviceImagesDS.HasChanges())
            {
                this.Text = "Edit Devices and Keys XML - [" + m_filename + "*]";
            }
        }

        private void updateFormTextIfChanges()
        {
            if(deviceImagesDS.HasChanges())
            {
                this.Text = "Edit Devices and Keys XML - [" + m_filename + "*]";
            }
        }

        private void dataGridView1_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView2_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView3_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView4_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void dataGridView5_CellEndEdit(object sender,DataGridViewCellEventArgs e)
        {
            updateFormTextIfChanges();
        }

        private void Form1_Load(object sender,EventArgs e)
        {

        }

        private void saveAsToolStripMenuItem_Click(object sender,EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "xml files (*.xml)|*.xml" ;
            sfd.FilterIndex = 2 ;
            sfd.RestoreDirectory = false ;

            if(sfd.ShowDialog() == DialogResult.OK)
            {
                deviceImagesDS.WriteXml(sfd.FileName);
                m_open = true;
                m_filename = sfd.FileName;
                this.Text = "Edit Devices and Keys XML - [" + sfd.FileName + "]";
            }
            this.dataGridView1.Refresh();
            this.dataGridView2.Refresh();
            this.dataGridView3.Refresh();
            this.dataGridView4.Refresh();
           
        }
    }
}