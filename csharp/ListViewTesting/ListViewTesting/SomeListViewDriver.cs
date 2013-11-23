using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace ListViewTesting
{
    public class SomeListViewDriver
    {
        private string m_name1 = "";
        private string m_name2 = "";
        private string m_name3 = "";
        
        public SomeListViewDriver(string name)
        {
            m_name1 = name;
            m_name2 = name + "1";
            m_name3 = name + "2";
        }
        
        public string Name1
        {
            get
            {
                return m_name1;
            }
            set
            {
                m_name1 = value;
            }
        }
        public string Name2
        {
            get
            {
                return m_name2;
            }
            set
            {
                m_name2 = value;
            }
        }
        public string Name3
        {
            get
            {
                return m_name3;
            }
            set
            {
                m_name3 = value;
            }
        }
        
        public void AddToListViewItem(ListView lv)
        {
            ListViewItem lvi = new ListViewItem(m_name1);
            lvi.SubItems.Add(m_name2);
            lvi.SubItems.Add(m_name3);            
            
            lvi.Tag = this;
            
            lv.Items.Add(lvi);
            
        }
        public void ChangeListViewItem(ListViewItem lvi)
        {
            lvi.Text = m_name1;
            lvi.SubItems[1].Text = m_name2;
            lvi.SubItems[2].Text = m_name3;            
        }
    }
}
