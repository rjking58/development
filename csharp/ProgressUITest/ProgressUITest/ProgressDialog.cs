using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProgressUITest
{
    public partial class ProgressDialog : Form
    {

        public ProgressDialog()
        {
            InitializeComponent();
        }

        private void ProgressDialog_Load(object sender, EventArgs e)
        {

        }

        public void SetProgress(short pct)
        {
            progressBar1.Value = pct;
        }
    }
}