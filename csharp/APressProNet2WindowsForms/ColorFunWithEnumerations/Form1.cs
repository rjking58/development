using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ColorFunWithEnumerations
{
    public partial class ColorChooser : Form
    {
        public ColorChooser()
        {
            InitializeComponent();
        }

        private void ColorChooser_Load(object sender, EventArgs e)
        {
            string[] colorNames;
            colorNames = System.Enum.GetNames(typeof(KnownColor));
            lstColors.Items.AddRange(colorNames);
        }

        private void lstColors_SelectedIndexChanged(object sender, EventArgs e)
        {
            KnownColor selectedColor;
            selectedColor = (KnownColor)System.Enum.Parse(typeof(KnownColor), lstColors.Text);
            this.BackColor = System.Drawing.Color.FromKnownColor(selectedColor);
            
            this.txtbox_brightness.Text = this.BackColor.GetBrightness().ToString();
            this.txtbox_saturation.Text = this.BackColor.GetSaturation().ToString();
            this.txtbox_hue.Text = this.BackColor.GetSaturation().ToString();


            this.txtbox_red.Text = this.BackColor.R.ToString();
            this.txtbox_green.Text = this.BackColor.G.ToString();
            this.txtbox_blue.Text = this.BackColor.B.ToString();
        }

    }
}