using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        double m_aspect = 0;
        Image m_myImg = null;
        public Form1()
        {

            InitializeComponent();
            m_myImg = Image.FromFile(@"F:\graphix\em\janine\01014\53400016.jpg");
            
            //figure the aspect ratio so that we can just apply it to a
            // given Height to get a new Width!

            m_aspect = (double) m_myImg.Width / (double) m_myImg.Height;
            
            
            pictureBox1.Width = (int) ((double) pictureBox1.Height * m_aspect);
            
            //locate the control in the center of our container (in this case the main
            // window)
            Adjust_X_Location();
            
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = m_myImg;
        }

        private void pictureBox1_SizeChanged(object sender, EventArgs e)
        {
            pictureBox1.Width = (int)((double)pictureBox1.Height * m_aspect);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            
            Adjust_X_Location();
        }

        private void Adjust_X_Location()
        {
            int locX = (this.Width / 2) - (pictureBox1.Width / 2);
            if (locX < 0)
            {
                locX = 10;
            }
            Point pbPt = pictureBox1.Location;
            pbPt.X = locX;
            pictureBox1.Location = pbPt;
        }
    }
}
