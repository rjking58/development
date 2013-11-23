using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ClipboardDemo
{
    public partial class Form1 : Form
    {
        private const string TAB_CSHARP = "tab_csharp";
        private const string TAB_CPP = "tab_cpp";
        private const string TAB_PYTHON = "tab_python";
        private const string TAB_RUBY = "tab_ruby";
        private const string TAB_JAVA = "tab_java";

        private Dictionary<string, Dictionary<string,string>> m_CodeSnippetsByType =
            new Dictionary<string, Dictionary<string,string>>();

        public Form1()
        {
            InitializeComponent();

            InitializeSnippets();

            SetInitialSelection();

            LoadTabs();
        }

        private void btn_FromClipboard_Click(object sender, EventArgs e)
        {
            // <<---- the name of the tab in the format we are using internally
            //tb_selectedTab.Text = tabControl1.SelectedTab.Name;


            // Declares an IDataObject to hold the data returned from the clipboard.
            // Retrieves the data from the clipboard.
            IDataObject iData = Clipboard.GetDataObject();

            // Determines whether the data is in a format you can use.
            if (iData.GetDataPresent(DataFormats.Text))
            {
                // Yes it is, so display it in a text box.
                textBox1.Text = (String)iData.GetData(DataFormats.Text);
            }
            else
            {
                // No it is not.
                textBox1.Text = "Could not retrieve data off the clipboard.";
            }

        }

        private void btn_ToClipboard_Click(object sender, EventArgs e)
        {
            // <<---- the name of the tab in the format we are using internally
            //tb_selectedTab.Text = tabControl1.SelectedTab.Name;

            if (textBox1.Text.Length != 0)
            {
                Clipboard.SetDataObject(textBox1.Text);
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            LoadTabs();
        }

        private void tabControl1_DrawItem(object sender, DrawItemEventArgs e)
        {
            TabPage currentab=tabControl1.TabPages[e.Index];
			SolidBrush textbrush=new SolidBrush(Color.Black);
			Rectangle itemrect=tabControl1.GetTabRect(e.Index);
			StringFormat sf=new StringFormat();
			sf.Alignment=StringAlignment.Center;
			sf.LineAlignment=StringAlignment.Center;

            if (Convert.ToBoolean(e.State & DrawItemState.Selected))
            {
                Font f = new Font(tabControl1.Font.Name, tabControl1.Font.Size, FontStyle.Bold);
                e.Graphics.DrawString(currentab.Text, f, textbrush, itemrect, sf);
            }
            else
            {
                e.Graphics.DrawString(currentab.Text, e.Font, textbrush, itemrect, sf);
            }
			textbrush.Dispose();		
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }
        private void InitializeSnippets()
        {
            for(int x = 0;
                x < 4;
                x++)
            {
                Dictionary<string,string> SnippetsByLang = new Dictionary<string,string>();
                switch(x)
                {
                    case 0:
                        m_CodeSnippetsByType.Add("sample1",SnippetsByLang);
                        listBox1.Items.Add("sample1");
                        SnippetsByLang.Add(TAB_CSHARP,"sample1 c#");
                        SnippetsByLang.Add(TAB_CPP,"sample1 c++");
                        SnippetsByLang.Add(TAB_PYTHON,"sample1 python");
                        SnippetsByLang.Add(TAB_RUBY,"sample1 ruby");
                        SnippetsByLang.Add(TAB_JAVA,"sample1 java");
                        break;
                    case 1:
                        m_CodeSnippetsByType.Add("sample2",SnippetsByLang);
                        listBox1.Items.Add("sample2");
                        SnippetsByLang.Add(TAB_CSHARP,"sample2 c#");
                        SnippetsByLang.Add(TAB_CPP,"sample2 c++");
                        SnippetsByLang.Add(TAB_PYTHON,"sample2 python");
                        SnippetsByLang.Add(TAB_RUBY,"sample2 ruby");
                        SnippetsByLang.Add(TAB_JAVA,"sample2 java");
                        break;
                    case 2:
                        m_CodeSnippetsByType.Add("sample3",SnippetsByLang);
                        listBox1.Items.Add("sample3");
                        SnippetsByLang.Add(TAB_CSHARP,"sample3 c#");
                        SnippetsByLang.Add(TAB_CPP,"sample3 c++");
                        SnippetsByLang.Add(TAB_PYTHON,"sample3 python");
                        SnippetsByLang.Add(TAB_RUBY,"sample3 ruby");
                        SnippetsByLang.Add(TAB_JAVA,"sample3 java");
                        break;
                    case 3:
                        m_CodeSnippetsByType.Add("sample4",SnippetsByLang);
                        listBox1.Items.Add("sample4");
                        SnippetsByLang.Add(TAB_CSHARP,"sample4 c#");
                        SnippetsByLang.Add(TAB_CPP,"sample4 c++");
                        SnippetsByLang.Add(TAB_PYTHON,"sample4 python");
                        SnippetsByLang.Add(TAB_RUBY,"sample4 ruby");
                        SnippetsByLang.Add(TAB_JAVA,"sample4 java");
                        break;
                }
            }
        }
        void SetInitialSelection()
        {
            listBox1.SelectedItem = "sample1";
        }

        void LoadTabs()
        {
            string selection = listBox1.SelectedItem.ToString();

            foreach(Control ctrl in tabControl1.Controls)
            {
                string tab_name = ctrl.Name;

                ctrl.Controls[0].Text = m_CodeSnippetsByType[selection][tab_name];
            }
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
