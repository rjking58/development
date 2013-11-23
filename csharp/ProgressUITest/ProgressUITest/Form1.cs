using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProgressUITest
{
    public partial class Form1 : Form
    {
        ProgressDialog pd;
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_ProgressTest_Click(object sender, EventArgs e)
        {
            simpleProgressor sp = new simpleProgressor();
            sp.PercentCompleteEvent += PctProgress;

            pd = new ProgressDialog();
            pd.Show();
            sp.go();
            pd.Close();
            pd = null;
            
        }

        private void PctProgress(short pct)
        {
            pd.SetProgress(pct);
        }
    }
}