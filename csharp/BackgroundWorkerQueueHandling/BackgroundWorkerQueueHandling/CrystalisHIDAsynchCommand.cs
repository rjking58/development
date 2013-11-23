using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using UEI.HidIf;
using UEI.Diagnostics;

namespace BackgroundWorkerQueueHandling
{
    /// <summary>
    /// abstract form of an asynchonous command.  
    /// 
    /// Usage Notes:
    ///   each subclass will typically set up a delegate and an event used to
    ///   notify the caller when the command is complete, and to receive any return
    ///   values from the call.  A working example of a command class with these events included
    ///   looks like:
    /// 
    /// <pre><code>
    ///
    ///class GetFirmwareVersion : CrystalisHIDAsynchCommand
    ///{
    ///    public delegate void GetFirmwareVersionResult_delegate(UEI.HidIf.CommandType    retVal,
    ///                                                           string                   version);
    ///    public event GetFirmwareVersionResult_delegate GetFirmwareVersionResult_Event = null;
    ///
    ///
    ///    public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
    ///    {
    ///
    ///        string version = "";
    ///        UEI.HidIf.CommandType retVal = UEI.HidIf.CommandType.ResponseSuccess;
    ///        if(crys_comm.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
    ///        {
    ///            UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFirmwareVersion.. executing",
    ///                                                          Thread.CurrentThread.GetHashCode()));
    ///        }
    ///
    ///
    ///        retVal = crys_comm.GetFirmwareVersion(ref version);
    ///
    ///        if (GetFirmwareVersionResult_Event != null)
    ///        {
    ///            GetFirmwareVersionResult_Event(retVal,version);
    ///        }
    ///
    ///        return retVal;
    ///    }
    ///}
    ///
    /// </code></pre>
    /// 
    /// A typical message submission from the UI assembly would look like:
    /// 
    /// <pre><code>
    ///       private CrystalisHIDQueueHandler background_q = null;
    ///             ...
    ///             ...
    ///       background_q = CrystalisHIDQueueHandler.GetInstance();
    ///       // hook up the events for detecting when the remote id connected/disconnected..
    ///       background_q.RemoteCommEstablished_event += GainedRemoteCommsEventHandler;
    ///       background_q.RemoteCommLost_event += LostRemoteCommsEventHandler;
    ///             ...
    ///             ...
    ///       // send our FirmwareVersion request..
    ///       GetFirmwareVersion my_msg = new GetFirmwareVersion();
    ///       my_msg.GetFirmwareVersionResult_Event += this.FirmwareVersionResult;
    ///       background_q.SubmitMessage(my_msg);
    /// </code></pre>
    /// With FirmwareVersionResult looking like:
    /// <pre><code>
    ///private void FirmwareVersionResult(UEI.HidIf.CommandType retVal,
    ///                                   string                version)
    ///{
    ///    if(this.InvokeRequired)
    ///    {
    ///        this.Invoke(new GetFirmwareVersion.GetFirmwareVersionResult_delegate(FirmwareVersionResult),
    ///                    new object[] {retVal,version});
    ///    }
    ///    else
    ///    {
    ///        lbl_FirmwareVersion.Text = version;
    ///        lbl_RetVal.Text = String.Format("{0}", retVal);
    ///    }
    ///}
    /// </code></pre>
    /// the method 'DoCommand' is actually run on the worker thread.. when finished, it calls back the Event
    /// handler, which then tries to determine if the thread that called it is a UI thread.. if not, it
    /// performs an Invoke to make sure that the UI thread is the only thread which can change UI components.
    /// 
    /// Which brings us to the final assumption.. the above event handler assumes that the object which contains
    /// it derives from System.Windows.Forms.Control (notice the call to:  this.InvokeRequired)  This is because of 
    /// .NET restrictions on which threads can actually change control states (only the thread that owns 
    /// the UI components can change them).  Stated more directly, .NET windows controls are not thread safe, 
    /// which requires these types of mechanism to make sure non-UI threads do not modify UI state.
    /// </summary>
    public abstract class CrystalisHIDAsynchCommand
    {

        UEI.HidIf.CommandType   m_retVal;
        private EventWaitHandle m_ewh = new EventWaitHandle(false,System.Threading.EventResetMode.AutoReset);
            
        public EventWaitHandle ewh
        {
            get
            {
                return m_ewh;
            }
        }

        /// <summary>
        /// Do a command asynchronously
        /// </summary>
        /// <param name="dev">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public abstract UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm);
        public abstract void SendCompleteEvent();

        public UEI.HidIf.CommandType DoCommandProcess(CrystalisHIDDevice crys_comm)
        {
            m_retVal = DoCommand(crys_comm);
            m_ewh.Set();
            SendCompleteEvent();
            return m_retVal;
        }

        public UEI.HidIf.CommandType retVal 
        {
            get
            {
                return m_retVal;
            }
            set
            {
                m_retVal = value;
            }
        }

    }


    /// <summary>
    /// get firmware version from the remote.
    /// </summary>
    class GetFirmwareVersion : CrystalisHIDAsynchCommand
    {
        /// <summary>
        /// form of an event fired by this object when the command has returned and is 
        /// ready to return data to the caller.
        /// </summary>
        public delegate void GetFirmwareVersionResult_delegate(UEI.HidIf.CommandType    retVal,
                                                               string                   version);
        /// <summary>
        /// event fired by this object when the command has returned and is 
        /// ready to return data to the caller.
        /// </summary>
        public event GetFirmwareVersionResult_delegate GetFirmwareVersionResult_Event = null;
        
        private string m_version = "";
        
        /// <summary>
        /// get firmware version from the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {


            retVal = UEI.HidIf.CommandType.ResponseSuccess;

            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFirmwareVersion.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.GetFirmwareVersion(ref m_version);

            
            return retVal;
        }
        public override void SendCompleteEvent()
        {
            if (GetFirmwareVersionResult_Event != null)
            {
                GetFirmwareVersionResult_Event(retVal,m_version);
            }
        }

    }
    
    /// <summary>
    /// get serial number from the remote.
    /// </summary>
    class GetSerialNumber : CrystalisHIDAsynchCommand
    {
        /// <summary>
        /// form of an event fired by this object when the command has returned and is 
        /// ready to return data to the caller.
        /// </summary>
        public delegate void GetSerialNumberResult_delegate(UEI.HidIf.CommandType    retVal,
                                                            string                   serialNumber);
        /// <summary>
        /// event fired by this object when the command has returned and is 
        /// ready to return data to the caller.
        /// </summary>
        public event GetSerialNumberResult_delegate GetSerialNumberResult_Event = null;

        private string m_serialnumber = "";
        
        /// <summary>
        /// get serial number from the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {
            retVal = UEI.HidIf.CommandType.ResponseSuccess;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetSerialNumber.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.GetSerialNumber(ref m_serialnumber);


            return retVal;
        }
        public override void SendCompleteEvent()
        {
            if (GetSerialNumberResult_Event != null)
            {
                GetSerialNumberResult_Event(retVal,m_serialnumber);
            }
        }
    }

    /// <summary>
    /// get file manifest from the remote.
    /// </summary>
    class GetFileManifest : CrystalisHIDAsynchCommand
    {
        private List<string>        m_FileManifest = null;
        
        public GetFileManifest(List<string> FileManifest)
        {
            m_FileManifest = FileManifest;
            if(m_FileManifest == null)
            {
                throw new System.NullReferenceException("FileManifest must not be null");
            }
        }
        /// <summary>
        /// get file manifest from the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {

            retVal = UEI.HidIf.CommandType.ResponseSuccess;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFileManifest.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.GetFileManifest(m_FileManifest);
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFileManifest.. complete",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            return retVal;
        }
        public override void SendCompleteEvent()
        {
        }
    }

    /// <summary>
    /// remove file on the remote.
    /// </summary>
    class RemoveFile : CrystalisHIDAsynchCommand
    {
        private string              m_filename = "";
        public RemoveFile(string filename)
        {
            m_filename = filename;
        }
        
        /// <summary>
        /// remove file on the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {

            retVal = UEI.HidIf.CommandType.ResponseSuccess;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})RemoveFile.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.RemoveFile(m_filename);

            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})RemoveFile.. complete",
                                                              Thread.CurrentThread.GetHashCode()));
            }
            return retVal;
        }
        public override void SendCompleteEvent()
        {
        }
    }

    /// <summary>
    /// send file to the remote.
    /// </summary>
    class SendFile : CrystalisHIDAsynchCommand
    {
        private string              m_filename = "";
        public SendFile(string filename)
        {
            m_filename = filename;
        }
        
        /// <summary>
        /// send file to the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {

            retVal = UEI.HidIf.CommandType.ResponseSuccess;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})SendFile.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.SendFile(m_filename);

            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})SendFile.. complete",
                                                              Thread.CurrentThread.GetHashCode()));
            }
            return retVal;
        }
        public override void SendCompleteEvent()
        {
        }
    }

    /// <summary>
    /// GetFile to the remote.
    /// </summary>
    class GetFile : CrystalisHIDAsynchCommand
    {
        private string              m_filename = "";
        public GetFile(string filename)
        {
            m_filename = filename;
        }

        /// <summary>
        /// GetFile to the remote.
        /// </summary>
        /// <param name="crys_comm">Crystalis device used to communicate with a remote</param>
        /// <returns>UEI.HidIf.CommandType</returns>
        public override UEI.HidIf.CommandType DoCommand(CrystalisHIDDevice crys_comm)
        {

            retVal = UEI.HidIf.CommandType.ResponseSuccess;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFile.. executing",
                                                              Thread.CurrentThread.GetHashCode()));
            }

            retVal = crys_comm.GetFile(m_filename);

            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})GetFile.. complete",
                                                              Thread.CurrentThread.GetHashCode()));
            }
            return retVal;
        }
        public override void SendCompleteEvent()
        {
        }
    }

}


