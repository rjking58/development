using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Chapter1UIArchitecture
{
    public partial class Form1 : Form
    {
#if false
        private GroupBox gb_GroupBox1 = new GroupBox();
        private RadioButton rb_RadioButton1 = new RadioButton();
        private RadioButton rb_RadioButton2 = new RadioButton();
        private Button btn_Button1 = new Button();
#endif
        public Form1()
        {
#if false
            gb_GroupBox1.Text = "GroupBox1";
            rb_RadioButton1.Text = "RadioButton1";
            rb_RadioButton2.Text = "RadioButton2";
            btn_Button1.Text = "Button1";

            gb_GroupBox1.Controls.Add(rb_RadioButton1);
            gb_GroupBox1.Controls.Add(rb_RadioButton2);

            this.Controls.Add(gb_GroupBox1);
            this.Controls.Add(btn_Button1);
#endif

            InitializeComponent();
        }
    }
}