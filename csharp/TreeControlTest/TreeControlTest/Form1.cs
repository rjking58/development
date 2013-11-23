using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TreeControlTest
{
    public partial class Form1 : Form
    {
        private TreeNode m_selectedNode = null;

        public Form1()
        {
            InitializeComponent();
            TreeNode insertnode = null;

            insertnode = tree_View1.Nodes.Add("firstAlevel-1");
            insertnode.Nodes.Add("secondAlevel-1");
            insertnode.Nodes.Add("secondAlevel-2");
            insertnode = insertnode.Nodes.Add("secondAlevel-3");
            insertnode.Nodes.Add("thirdAlevel-1");

            insertnode = tree_View1.Nodes.Add("firstBlevel-1");
            insertnode.Nodes.Add("secondBlevel-1");
            insertnode = insertnode.Nodes.Add("secondBlevel-2");
            insertnode.Nodes.Add("thirdBlevel-1");
        }

        private void tree_View1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }

        private void tree_View1_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {
                Point ClickPoint = new Point(e.X,e.Y);
                TreeNode ClickNode = tree_View1.GetNodeAt(ClickPoint);
                
                if(ClickNode != null) 
                {
                    m_selectedNode = ClickNode;
    
                    // Convert from Tree coordinates to Screen coordinates
                    Point ScreenPoint = tree_View1.PointToScreen(ClickPoint);
                    // Convert from Screen coordinates to Form coordinates
                    Point FormPoint = this.PointToClient(ScreenPoint);
                    // Show context menu
                    
                    contextMenu_Tree1.Show(this,FormPoint);
                }
            }
        }

        private void validateSubtreeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            StringBuilder report = new StringBuilder();

            WalkTheTree(m_selectedNode,report);

            tb_result.Text = report.ToString();
        }

        private void WalkTheTree(TreeNode currnode,StringBuilder report)
        {
            report.Append("\n\r");
            report.Append("\n\r");
            report.Append(currnode.Text);
            if(currnode.Nodes.Count > 0)
            {
                foreach( TreeNode subnode in currnode.Nodes)
                {
                    // weeeeeee
                    WalkTheTree(subnode,report);
                }
            }
        }
    }
}
