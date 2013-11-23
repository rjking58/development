using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace FileInfoPropertiesTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            FileInfo fi = new FileInfo(@"c:\temp\DeviceFile.cs");

            InitializeComponent();

            propertyGrid1.SelectedObject = fi;
            propertyGrid2.SelectedObject = fi.GetType();
        }
    }
}
