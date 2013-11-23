using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Clock1
{
    public partial class Form1 : Form
    {
        private simpleClock m_clock;
        private bool m_displayGrey = true;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_clock.StopClock();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            m_clock = new simpleClock(true);
            m_clock.clock_event += new simpleClock.ClockEventDelegate(m_clock_clock_event);
            m_clock.StartClock();
           
        }

        void m_clock_clock_event(DateTime current_time)
        {

            lbl_currTime.Text = string.Format(  "{0:D2}:{1:D2}:{2:D2}", 
                                                current_time.Hour, 
                                                current_time.Minute,
                                                current_time.Second);
            if(m_displayGrey)
            {
//                pictureBox1.Image = new Bitmap(Application.);
                m_displayGrey = false;
            }
            else
            {
                m_displayGrey = true;
            }
                                                            
                                                
        }
    }
}