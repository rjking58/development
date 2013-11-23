using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ListViewTesting
{
    public partial class Form1:Form
    {
        private List<SomeListViewDriver> m_list = 
            new List<SomeListViewDriver>();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender,EventArgs e)
        {
            m_list.Add(new SomeListViewDriver("a"));
            m_list.Add(new SomeListViewDriver("b"));
            m_list.Add(new SomeListViewDriver("c"));
            m_list.Add(new SomeListViewDriver("d"));
            m_list.Add(new SomeListViewDriver("e"));
            m_list.Add(new SomeListViewDriver("f"));
            m_list.Add(new SomeListViewDriver("g"));
            m_list.Add(new SomeListViewDriver("h"));
            m_list.Add(new SomeListViewDriver("j"));
            m_list.Add(new SomeListViewDriver("k"));            
            
            //ImageList ilSmall = new ImageList();
            //ilSmall.Images.Add();
            
            //ImageList ilLarge = new ImageList();
            //ilLarge.Images.Add();
                        
            listView1.Items.Clear();
            listView1.Columns.Add("Name");
            listView1.Columns.Add("derivedCol1");
            listView1.Columns.Add("derivedCol2");                        
            
            foreach(SomeListViewDriver slvd in m_list)
            {
                slvd.AddToListViewItem(listView1);
            }
            listView1.View = View.Details;
            
            optLargeIcon.Tag = View.Details;
            optSmallIcon.Tag = View.SmallIcon;
            optDetails.Tag = View.Details;
            optList.Tag = View.List;
            optTile.Tag = View.Tile;
        }
       
        private void NewView(object sender, System.EventArgs a)
        {
            
            listView1.View = (View) (((Control) sender).Tag);
            this.Text = "Using View:" + listView1.View.ToString();
        }

        private void listView1_MouseDoubleClick(object sender,MouseEventArgs e)
        {

            ListViewItem lvi = listView1.GetItemAt(e.X,e.Y);
            if(lvi.Tag is SomeListViewDriver)
            {
                SomeListViewDriver slvd = (SomeListViewDriver) lvi.Tag;
                
                EditSomeListViewDriver edit_form = new EditSomeListViewDriver(slvd);
                edit_form.ShowDialog();
                
                slvd.ChangeListViewItem(lvi);
            }
            
        }
    }
}