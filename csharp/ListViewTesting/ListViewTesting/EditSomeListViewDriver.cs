using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ListViewTesting
{
    public partial class EditSomeListViewDriver:Form
    {
        private SomeListViewDriver m_somelvd;
        public EditSomeListViewDriver(SomeListViewDriver somelvd)
        {
            m_somelvd = somelvd;
            InitializeComponent();
        }

        private void txt_Name1_TextChanged(object sender,EventArgs e)
        {
            m_somelvd.Name1 = txt_Name1.Text;
        }

        private void txt_Name2_TextChanged(object sender,EventArgs e)
        {
            m_somelvd.Name2 = txt_Name2.Text;           
        }

        private void txt_Name3_TextChanged(object sender,EventArgs e)
        {
            m_somelvd.Name3 = txt_Name3.Text;
        }

        private void btn_OK_Click(object sender,EventArgs e)
        {
            this.Close();
        }

        private void EditSomeListViewDriver_Load(object sender,EventArgs e)
        {
            txt_Name1.Text = m_somelvd.Name1;
            txt_Name2.Text = m_somelvd.Name2;
            txt_Name3.Text = m_somelvd.Name3;            
        }
    }
}