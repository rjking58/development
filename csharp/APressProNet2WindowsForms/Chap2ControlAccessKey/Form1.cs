using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Chap2ControlAccessKey
{
    public partial class Form1 : Form
    {
        bool m_toggle_state = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_toggle_Click(object sender, EventArgs e)
        {
            if (m_toggle_state)
            {
                m_toggle_state = false;
                lbl_toggleResult.Text = "false";
                btn_Controlled.Enabled = false;
            }
            else
            {
                m_toggle_state = true;
                lbl_toggleResult.Text = "true";
                btn_Controlled.Enabled = true;                
            }
        }
    }
}