using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using UEI.HidIf;
using System.IO;

namespace BackgroundWorkerQueueHandling
{

    class Message1 : CrystalisHIDAsynchCommand
    {
        public delegate void Message1Result_delegate();
        public event Message1Result_delegate Message1Result_Event = null;
        
        StreamWriter m_tw = null;

        public Message1(StreamWriter tw)
        {
            m_tw = tw;
        }
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice dev)
        {
            Thread.Sleep(2000);
            m_tw.Write("(" + Thread.CurrentThread.GetHashCode() + ")");
            m_tw.WriteLine("Message1 wrote this:");
            m_tw.Flush();
            Thread.Sleep(2000);
            return UEI.HidIf.CommandType.ResponseSuccess;
        }
        public override void SendCompleteEvent()
        {
            if (Message1Result_Event != null)
            {
                Message1Result_Event();
            }
        }
    }
}
