using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ControlEventHandlingUsingDelegates
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
            Form1 frm = new Form1();

            frm.ShowDialog();
        }
    }
}