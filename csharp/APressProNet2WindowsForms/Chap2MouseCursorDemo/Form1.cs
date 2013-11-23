using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Chap2MouseCursorDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_WaitCursor_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
        }

        private void btn_DefaultCursor_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;
        }
    }
}