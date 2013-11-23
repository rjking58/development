using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Text;
using System.Windows.Forms;

namespace FontViewer
{
    public partial class FontViewer : Form
    {
        InstalledFontCollection fonts = new InstalledFontCollection();
        
        public FontViewer()
        {
            InitializeComponent();

            foreach (FontFamily family in fonts.Families)
            {
                lstInstalledfonts.Items.Add(family.Name);

            }
            
        }

        private void lstInstalledfonts_SelectedIndexChanged(object sender, EventArgs e)
        {
            // find the family name
            lblFontdisplay.Text = lstInstalledfonts.Text;
            lblFontdisplay.Font = new Font(lstInstalledfonts.Text, (float)14.0);
        }

        private void displaySystemFonts()
        {

        }
    }
}