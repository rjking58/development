using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ControlEventHandlingUsingDelegates
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void numeric_TextBox_KeyPress(object sender,
                                    KeyPressEventArgs ea)
        {
            if (!char.IsControl(ea.KeyChar) && !char.IsDigit(ea.KeyChar))
            {
                ea.Handled = true;
            }
        }
    }
}