using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Runtime.InteropServices; 



namespace myAlarm
{
    /// <summary>
    /// Summary description for Form1.
    /// </summary>



    public class AlarmTime
    {
    
        private int m_hour;
        private int m_minute;

        public AlarmTime(int hour, int minute)
        {
            m_hour = hour;
            m_minute = minute;
        }
        
        public override String ToString()
        {
            return "Alarm @" + String.Format("{0:d2}",m_hour) + ":" + String.Format("{0:d2}",m_minute);
        }

        public int GetHour()
        {
            return m_hour;
        }
        public int GetMinute()
        {
            return m_minute;
        }


    }


    public class Form1 : System.Windows.Forms.Form
    {
        [DllImport("winmm.dll")]
        public static extern long PlaySound(string lpszName, long hModule, long dwFlags);

        private System.Windows.Forms.Label A;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown HoursUpDown;
        private System.Windows.Forms.Button NewAlarmBtn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button ClearAlarmBtn;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox AlarmTimes;
        private System.Windows.Forms.NumericUpDown MinutesUpDown;
        private System.ComponentModel.IContainer components;
        private System.Windows.Forms.Label CurrentTimeLbl;
        private String ALARMS_FILE = "alarms.dat";

        private int mHour;
        private System.Windows.Forms.Timer timer2;
        private int mMinute;
        public Form1()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            UpdateTime();
            //
            // TODO: Add any constructor code after InitializeComponent call
            //
            // try to read in "alarms.dat"..
            try
            {
                FileStream f = new FileStream(ALARMS_FILE,FileMode.Open);
                
                // read and load up the list box..
                try
                {
                    while(f.Length != f.Position)
                    {
                        int hour = (int) f.ReadByte();
                        int minute = (int) f.ReadByte();
                        AlarmTime m = new AlarmTime(hour,minute);
                        // add to list box..
                        AlarmTimes.Items.Add(m);
                        
                    }

                }
                catch(IOException exc)
                {
                    MessageBox.Show(exc.Message,
                        "File Reading...",
                        MessageBoxButtons.OK, 
                        MessageBoxIcon.Exclamation);

                }

            }
            catch (System.IO.FileNotFoundException e)
            {
            }


        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
            {
                if (components != null) 
                {
                    components.Dispose();
                }
            }
            base.Dispose( disposing );
        }

		#region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.A = new System.Windows.Forms.Label();
            this.MinutesUpDown = new System.Windows.Forms.NumericUpDown();
            this.HoursUpDown = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.NewAlarmBtn = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.AlarmTimes = new System.Windows.Forms.ListBox();
            this.ClearAlarmBtn = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.CurrentTimeLbl = new System.Windows.Forms.Label();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.MinutesUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HoursUpDown)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // A
            // 
            this.A.Location = new System.Drawing.Point(8, 32);
            this.A.Name = "A";
            this.A.Size = new System.Drawing.Size(48, 16);
            this.A.TabIndex = 1;
            this.A.Text = "Hours";
            this.A.Click += new System.EventHandler(this.A_Click);
            // 
            // MinutesUpDown
            // 
            this.MinutesUpDown.Location = new System.Drawing.Point(160, 32);
            this.MinutesUpDown.Maximum = new System.Decimal(new int[] {
                                                                          59,
                                                                          0,
                                                                          0,
                                                                          0});
            this.MinutesUpDown.Name = "MinutesUpDown";
            this.MinutesUpDown.Size = new System.Drawing.Size(40, 20);
            this.MinutesUpDown.TabIndex = 2;
            // 
            // HoursUpDown
            // 
            this.HoursUpDown.Location = new System.Drawing.Point(64, 32);
            this.HoursUpDown.Maximum = new System.Decimal(new int[] {
                                                                        23,
                                                                        0,
                                                                        0,
                                                                        0});
            this.HoursUpDown.Name = "HoursUpDown";
            this.HoursUpDown.Size = new System.Drawing.Size(40, 20);
            this.HoursUpDown.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(112, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 16);
            this.label1.TabIndex = 4;
            this.label1.Text = "Minutes";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // NewAlarmBtn
            // 
            this.NewAlarmBtn.Location = new System.Drawing.Point(16, 64);
            this.NewAlarmBtn.Name = "NewAlarmBtn";
            this.NewAlarmBtn.Size = new System.Drawing.Size(88, 16);
            this.NewAlarmBtn.TabIndex = 5;
            this.NewAlarmBtn.Text = "New Alarm";
            this.NewAlarmBtn.Click += new System.EventHandler(this.NewAlarmBtn_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.NewAlarmBtn,
                                                                                    this.A,
                                                                                    this.HoursUpDown,
                                                                                    this.label1,
                                                                                    this.MinutesUpDown});
            this.groupBox1.Location = new System.Drawing.Point(8, 16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(248, 104);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Set An Alarm";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.AlarmTimes,
                                                                                    this.ClearAlarmBtn});
            this.groupBox2.Location = new System.Drawing.Point(8, 136);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(248, 200);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Current Alarms";
            // 
            // AlarmTimes
            // 
            this.AlarmTimes.Location = new System.Drawing.Point(24, 24);
            this.AlarmTimes.Name = "AlarmTimes";
            this.AlarmTimes.Size = new System.Drawing.Size(136, 160);
            this.AlarmTimes.TabIndex = 0;
            this.AlarmTimes.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // ClearAlarmBtn
            // 
            this.ClearAlarmBtn.Location = new System.Drawing.Point(176, 24);
            this.ClearAlarmBtn.Name = "ClearAlarmBtn";
            this.ClearAlarmBtn.Size = new System.Drawing.Size(48, 32);
            this.ClearAlarmBtn.TabIndex = 6;
            this.ClearAlarmBtn.Text = "Clear Alarm";
            this.ClearAlarmBtn.Click += new System.EventHandler(this.ClearAlarmBtn_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 60000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // CurrentTimeLbl
            // 
            this.CurrentTimeLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.CurrentTimeLbl.Location = new System.Drawing.Point(264, 40);
            this.CurrentTimeLbl.Name = "CurrentTimeLbl";
            this.CurrentTimeLbl.Size = new System.Drawing.Size(80, 24);
            this.CurrentTimeLbl.TabIndex = 8;
            this.CurrentTimeLbl.Text = "label2";
            // 
            // timer2
            // 
            this.timer2.Interval = 2000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(352, 358);
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.CurrentTimeLbl,
                                                                          this.groupBox2,
                                                                          this.groupBox1});
            this.Name = "Form1";
            this.Text = "Alarmist!";
            ((System.ComponentModel.ISupportInitialize)(this.MinutesUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HoursUpDown)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }
		#endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() 
        {
            Application.Run(new Form1());
        }

        private void A_Click(object sender, System.EventArgs e)
        {
        
        }

        private void label1_Click(object sender, System.EventArgs e)
        {
        
        }

        private void timer1_Tick(object sender, System.EventArgs e)
        {
            UpdateTime();

            timer2.Stop();

            IEnumerator currAlarm = AlarmTimes.Items.GetEnumerator();
            int CurrTimeABS = mHour*60;
            CurrTimeABS += mMinute;
            while(currAlarm.MoveNext())
            {
                int AlarmMinutesABS;
                // get current time and convert into raw minutes
                AlarmMinutesABS = (((AlarmTime)currAlarm.Current).GetHour()) * 60;
                AlarmMinutesABS += ((AlarmTime)currAlarm.Current).GetMinute();
                
                if (        (AlarmMinutesABS >= (CurrTimeABS -2))
                    &&     (AlarmMinutesABS <= (CurrTimeABS + 2)) )
                {
                    timer2.Start();
                }
            }

        }

        private void listBox1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
        
        }

        private void NewAlarmBtn_Click(object sender, System.EventArgs e)
        {
            // Get the hour/minute combination from the correct fields..

            int hour = (int) HoursUpDown.Value;
            int minute = (int) MinutesUpDown.Value;
            // do something..
            AlarmTime m = new AlarmTime(hour,minute);
            // add to list box..
            AlarmTimes.Items.Add(m);
            writeAlarms();            
            // write the new alarm file..
        }

        private void ClearAlarmBtn_Click(object sender, System.EventArgs e)
        {
            int selection_idx = AlarmTimes.SelectedIndex;
            if ( selection_idx >= 0)
            {
                AlarmTimes.Items.RemoveAt(selection_idx);
            }   
            writeAlarms();
        }

        private void writeAlarms()
        {
            FileStream f;
            try 
            {
                f = new FileStream(ALARMS_FILE, FileMode.Create);
            }
            catch(IOException exc)
            {
                MessageBox.Show(exc.Message,
                    "File Creation Problem",
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Exclamation);
                return;
            }
                
            //write the file out..
            IEnumerator currAlarm = AlarmTimes.Items.GetEnumerator();
            while(currAlarm.MoveNext())
            {
                f.WriteByte((byte) ((AlarmTime)currAlarm.Current).GetHour());
                f.WriteByte((byte) ((AlarmTime)currAlarm.Current).GetMinute());
            }
            
            f.Close();
        }

        private void UpdateTime()
        {
            DateTime d1 = DateTime.Now;
            // update on screen clock..
            mHour = d1.Hour;
            mMinute = d1.Minute;
            CurrentTimeLbl.Text = String.Format("{0:x4}",d1.Hour) + ":" + String.Format("{0:d2}",d1.Minute);
        }

        private void timer2_Tick(object sender, System.EventArgs e)
        {

            PlaySound("c:\\windows\\media\\LOUDchimes.wav",0,1);
        }
    }
}
