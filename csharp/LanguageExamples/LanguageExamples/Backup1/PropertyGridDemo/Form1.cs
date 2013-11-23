using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace PropertyGridDemo
{
    public partial class Form1 : Form
    {
        private SimpleClass m_sc = new SimpleClass();
        public Form1()
        {
            InitializeComponent();
            
            m_sc.Name = "werble";
            m_sc.SimpleNumber = 44;
            propertyGrid1.SelectedObject = m_sc;
        }
    }
}