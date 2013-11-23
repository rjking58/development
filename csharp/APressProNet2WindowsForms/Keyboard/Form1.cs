using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Keyboard
{
    public partial class Form1 : Form
    {
        Queue<string> m_msgs = new Queue<string>();
        
        public Form1()
        {
            InitializeComponent();
        }

        // buffered input.. 'a shift-d' ends up as 'D'...
        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            
        }


        private void AddMessageToListBox(string str)
        {
            m_msgs.Enqueue(str);
            if (m_msgs.Count > 34)
            {
                m_msgs.Dequeue();
            }
            lstbox_formmessages.Items.Clear();
            lstbox_formmessages.Items.AddRange(m_msgs.ToArray());
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
        }

        private void lstboxFrmMsgs_KeyPress(object sender, KeyPressEventArgs e)
        {
            //AddMessageToListBox("KeyPress :" + e.KeyChar.ToString());
        }

        private void lstboxFrmMsgs_KeyDown(object sender, KeyEventArgs e)
        {
            AddMessageToListBox("KeyDown1 :" + e.KeyCode.ToString() + " Value :" + e.KeyValue.ToString());
            AddMessageToListBox("KeyDown2 All Keys depressed :" + e.KeyData.ToString());            
        }
    }
}