using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MultiControlEventHandler
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        private void mceh_OnClick(Object sender, EventArgs ea)
        {
            if(sender is Control)
            {
                
                Control ctrl = (Control) sender;
                MessageBox.Show("you LEFT clicked: " + ctrl.Name);
            }
        }

        
    }
    
}