using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace FormsProperties
{
    class myForm : Form
    {
        public myForm()
        {
            Text = "My First Windows Forms program";
            Width *= 2;

            // register event handlers..
        }

        protected override void OnClick(EventArgs ea)
        {
            base.OnClick(ea);

            MessageBox.Show("woohoo!  you clicked dude!");
        }

        protected override void OnPaint(PaintEventArgs ea)
        {
            base.OnPaint(ea);

            Graphics grfx = ea.Graphics;
            grfx.DrawString("Hello, windows forms", 
                            this.Font,
                            SystemBrushes.ControlText,
                            0,
                            0);
        }
    }

    class FormsProperties
    {
        // single threaded apartment mode..
        [STAThread]
        static void Main()
        {
            myForm frm = new myForm();


            Application.Run(frm);
        }
    }
}