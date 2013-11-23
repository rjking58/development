using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using Manifest.Lib;

namespace MutexGrabber
{
    public partial class Form1:Form
    {
        private MutexHandler mh = new MutexHandler(false,"abcd");
        bool held = false;                
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_Acquire_Click(object sender,EventArgs e)
        {
            if(mh.Check())
            {
                lbl_MutexState.Text = "Acquire:  we got it";
                held = true;
            }
            else
            {
                lbl_MutexState.Text = "Acquire:  we couldn't get it";            
                held = false;
            }
        }

        private void btn_Release_Click(object sender,EventArgs e)
        {
            lbl_MutexState.Text = "released...";
            mh.Release();
        }
    }
}