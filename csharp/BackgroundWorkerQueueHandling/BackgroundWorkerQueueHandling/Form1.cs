using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Threading;
using System.IO;

using UEI.HidIf;
using UEI.Diagnostics;

namespace BackgroundWorkerQueueHandling
{
    public partial class Form1:Form
    {
        private CrystalisHIDQueueHandler background_q = null;
        private StreamWriter m_tw = null;
        public Form1()
        {
            InitializeComponent();
            background_q = CrystalisHIDQueueHandler.GetInstance();
            background_q.RemoteCommEstablished_event += GainedRemoteCommsEventHandler;
            background_q.RemoteCommLost_event += LostRemoteCommsEventHandler;
            Debug.SetLogFilePath("BackgroundQueue.log");
            UEI.HidIf.HidIFTraceSwitch.trace_switch.Level = System.Diagnostics.TraceLevel.Info;
            
            background_q.Start();
            
            lbl_FirmwareVersion.Text = "";
            lbl_SerialNumber.Text = "";
            
        }

        void GainedRemoteCommsEventHandler()
        {
            if(this.InvokeRequired)
            {
                this.Invoke(new CrystalisHIDQueueHandler.RemoteCommEstablished_delegate(GainedRemoteCommsEventHandler));
            }
            else
            {
                lbl_Connected.Text = "remote connected";
            }
        }
        void LostRemoteCommsEventHandler()
        {
            if(this.InvokeRequired)
            {
                this.Invoke(new CrystalisHIDQueueHandler.RemoteCommLost_delegate(LostRemoteCommsEventHandler));
            }
            else
            {
                lbl_Connected.Text = "remote NOT connected";
            }
        }
        private void Form1_FormClosing(object sender,FormClosingEventArgs e)
        {
            background_q.QuitNow();
            UEI.Diagnostics.Debug.Close();
        }

        private void btn_FirmwareVersion_Click(object sender,EventArgs e)
        {
           GetFirmwareVersion my_msg = new GetFirmwareVersion();
           my_msg.GetFirmwareVersionResult_Event += this.FirmwareVersionResult;
           background_q.SubmitMessage(my_msg);
        }

        private void FirmwareVersionResult(UEI.HidIf.CommandType retVal,
                                           string                version)
        {
            if(this.InvokeRequired)
            {
                this.Invoke(new GetFirmwareVersion.GetFirmwareVersionResult_delegate(FirmwareVersionResult),
                            new object[] {retVal,version});
            }
            else
            {
                lbl_FirmwareVersion.Text = version;
                lbl_RetVal.Text = String.Format("{0}", retVal);
            }
        }

        private void btn_SerialNumber_Click(object sender,EventArgs e)
        {
            GetSerialNumber my_msg = new GetSerialNumber();
            my_msg.GetSerialNumberResult_Event += this.SerialNumberResult;
            background_q.SubmitMessage(my_msg);
        }

        private void SerialNumberResult(UEI.HidIf.CommandType retVal,
                                        string                serialnumber)
        {
            if(this.InvokeRequired)
            {
                this.Invoke(new GetSerialNumber.GetSerialNumberResult_delegate(SerialNumberResult),
                            new object[] {retVal,serialnumber});
            }
            else
            {
                lbl_SerialNumber.Text = serialnumber;
                lbl_RetVal.Text = String.Format("{0}", retVal);
            }
        }

        private void btn_CrashTest_Click(object sender,EventArgs e)
        {
            background_q.QuitNow();
            //background_q.DoAbort();
        }

        private void btn_StartThread_Click(object sender,EventArgs e)
        {
            CrystalisHIDQueueHandler.StartErr err = background_q.Start();
            lbl_RetVal.Text = String.Format("{0}",err);
        }

        private void btn_ClearManifest_Click(object sender,EventArgs e)
        {
            lst_FileManifest.Items.Clear();
            lbl_FirmwareVersion.Text = "";
            lbl_SerialNumber.Text = "";
        }

        private void btn_GetManifest_Click(object sender,EventArgs e)
        {
            List<string> FileManifest = new List<string>();
            bool signaled = false;
            GetFileManifest my_msg = new GetFileManifest(FileManifest);

            background_q.SubmitMessage(my_msg);
            signaled = my_msg.ewh.WaitOne(15000,false);
            lbl_RetVal.Text = my_msg.retVal.ToString();            
            if(!signaled)
            {
                lst_FileManifest.Items.Add("failed manifest call!");
            }
            else
            {
                foreach(string fname in FileManifest)
                {
                    lst_FileManifest.Items.Add(fname);
                }
            }
        }

        private void btn_RemoveFile_Click(object sender,EventArgs e)
        {
            bool signaled = false;
            RemoveFile my_msg = new RemoveFile(txt_filename.Text);

            background_q.SubmitMessage(my_msg);
            signaled = my_msg.ewh.WaitOne(15000,false);
            lbl_RetVal.Text = my_msg.retVal.ToString();                        
            if(!signaled)
            {
                lst_FileManifest.Items.Add("failed RemoveFile call!");            
            }
        }

        private void btn_SendFile_Click(object sender,EventArgs e)
        {
            bool signaled = false;  
            SendFile my_msg = new SendFile(txt_SendFile.Text);

            background_q.SubmitMessage(my_msg);
            signaled = my_msg.ewh.WaitOne(15000,false);
            lbl_RetVal.Text = my_msg.retVal.ToString();                        
            if(!signaled)
            {
                lst_FileManifest.Items.Add("failed Send call!");            
            }
        }

        private void btn_GetFile_Click(object sender,EventArgs e)
        {
            bool signaled = false;  
            GetFile my_msg = new GetFile(txt_GetFile.Text);

            background_q.SubmitMessage(my_msg);
            signaled = my_msg.ewh.WaitOne(15000,false);
            lbl_RetVal.Text = my_msg.retVal.ToString();                        
            if(!signaled)
            {
                lst_FileManifest.Items.Add("failed Get call!");            
            }

        }
    }
}