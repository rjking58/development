using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using System.IO;
using UEI.HidIf;
using UEI.Diagnostics;

namespace BackgroundWorkerQueueHandling
{
    /// <summary>
    /// Multithreaded wrapper for <seealso cref="CrystalisHIDDevice" />
    /// </summary>
    public class CrystalisHIDQueueHandler
    {

        ///<summary>
        /// form of event fired when we have gotten a good ping acknowledge from the remote. 
        /// or a reasonable response for other commands
        ///</summary>
        public delegate void RemoteCommEstablished_delegate();
        ///<summary>
        /// event fired when we have gotten a good ping acknowledge from the remote. 
        /// or a reasonable response for other commands
        ///</summary>
        public event RemoteCommEstablished_delegate RemoteCommEstablished_event= null;
        ///<summary>
        /// form of event fired when we have gotten a bad ping acknowledge from the remote. 
        ///</summary>
        public delegate void RemoteCommLost_delegate();
        ///<summary>
        /// event fired when we have gotten a bad ping acknowledge from the remote. 
        ///</summary>
        public event RemoteCommLost_delegate RemoteCommLost_event = null;

        ///<summary>
        /// error code returned by <seealso cref="Start" />
        ///</summary>
        public enum StartErr
        {
            /// <summary>
            /// start successful
            /// </summary>
            SUCCESS,
            /// <summary>
            /// already started.. quit first then try again.
            /// </summary>
            ALREADY_STARTED
        }

        ///<summary>
        /// enumeration of all multi-threading states of CrystalisHIDQueueHandler
        ///</summary>
        public enum QH_ThreadState
        {
            /// <summary>
            /// threading not started.. use 'Start()' to get things going.
            /// </summary>
            NOT_STARTED,
            /// <summary>
            /// threading still coming up.
            /// </summary>
            STARTING,
            /// <summary>
            /// thread is now waiting for queued msgs.
            /// </summary>
            RUNNING_IDLE,
            /// <summary>
            /// thread is now servicing a msg.
            /// </summary>
            RUNNING_BUSY,
            /// <summary>
            /// we are finished.
            /// </summary>
            ENDED
        }

        /// <summary>
        /// current multi-threading state.
        /// </summary>
        QH_ThreadState m_state = QH_ThreadState.NOT_STARTED;

        /// <summary>
        /// accessor for state of queue..
        /// </summary>
        public QH_ThreadState State
        {
            get
            {
                return m_state;
            }
        }

        /// <summary>
        /// queue of abstract messages of type <seealso cref="CrystalisHIDAsynchCommand" />
        /// </summary>
        private Queue<CrystalisHIDAsynchCommand>    m_messages  = new Queue<CrystalisHIDAsynchCommand>();
        /// <summary>
        /// instance of the CrystalisHIDDevice we use to communicate with the Remote.
        /// </summary>
        private CrystalisHIDDevice                  m_crys_comm = new CrystalisHIDDevice();
        /// <summary>
        /// single worker we allow.  There should NEVER be one of these, since the remote can 
        /// deal with serial messages ONLY (i.e. we can't expect it will react well if we send
        /// two requests then expect two responses asynchronously)
        /// </summary>
        private Thread                              m_runningThread = null;
        private EventWaitHandle                     m_pingWait      = new EventWaitHandle(false,EventResetMode.AutoReset);
        private const int                           QUEUE_SLEEP = 1000; // milliseconds
        /// <summary>
        /// quit message.. this control main while loop in the <seealso cref="MainQueueHandling" /> routine
        /// </summary>
        private bool                                m_quitNow = false;
        /// <summary>
        /// whether remote seems connected or not.
        /// </summary>
        private bool                                m_remoteConnected = false;
        /// <summary>
        /// previous state for whether remote was connected or not.
        /// </summary>
        private bool                                m_remoteConnectedPrev = false;
        
        /// <summary>
        /// singleton implementation.
        /// </summary>
        private static CrystalisHIDQueueHandler m_instance = null;
        /// <summary>
        /// Singleton get instance method.
        /// </summary>
        /// <returns>CrystalisHIDQueueHandler</returns>
        public static CrystalisHIDQueueHandler GetInstance()
        {
            if (m_instance == null)
            {
                m_instance = new CrystalisHIDQueueHandler();
            }
            return m_instance;
        }


        /// <summary>
        /// are we quitting?  Used by CrystalisHIDDevice to detect situations where we
        /// are going away.
        /// </summary>
        public bool IsQuitting
        {
            get
            {
                return m_quitNow;
            }
        }

        /// <summary>
        /// private constructor.. required by singleton pattern
        /// </summary>
        private CrystalisHIDQueueHandler()
        {
        }

        /// <summary>
        /// quit signal.  All the caller can do is tell us to go away.. 
        /// </summary>
        public void QuitNow()
        {
            const int WAIT_FOR_STOP = 15;
            const int WAIT_DURATION = 50; // milliseconds.
            int m_retry_count = 0;
            
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::QuitNow ENTER",
                                                              Thread.CurrentThread.GetHashCode()));
            }
            if(m_runningThread != null)
            {
                m_quitNow = true;
                m_pingWait.Set();
                
                if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                {
                    UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::QuitNow  signal sent..",
                                                                  Thread.CurrentThread.GetHashCode()));
                }
                
                while(      (m_retry_count < WAIT_FOR_STOP                          )
                      &&    (m_runningThread.ThreadState != ThreadState.Stopped)   )
                {
                    if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                    {
                        UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::QuitNow  waiting to complete",
                                                                      Thread.CurrentThread.GetHashCode()));
                    }
                    Thread.Sleep(WAIT_DURATION);
                    m_retry_count++;
                }
                if(m_runningThread.ThreadState != ThreadState.Stopped)
                {
                    if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                    {
                        UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::QuitNow  abort required",
                                                                      Thread.CurrentThread.GetHashCode()));
                    }
                    m_runningThread.Abort();
                }
            }
            m_runningThread = null;
            m_state = QH_ThreadState.NOT_STARTED;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::QuitNow  EXIT",
                                                              Thread.CurrentThread.GetHashCode()));
            }
            
        }

        /// <summary>
        /// deal with all the potential thread states (performed during message submission).
        /// if this thread is in any funny state at all, try to abort then restart
        /// </summary>
        private void ThreadingStateHandler()
        {
            if(m_runningThread != null)
            {
                if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                {
                    UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::SubmitMessage threadstate:{1}",
                                                                  Thread.CurrentThread.GetHashCode(),
                                                                  m_runningThread.ThreadState)); 
                }
                switch(m_runningThread.ThreadState)
                {
                    case ThreadState.Aborted:
                    case ThreadState.AbortRequested:
                    case ThreadState.Stopped:
                    case ThreadState.StopRequested:
                        // we are in a 'bad state'.. try to abort then restart.
                        if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                        {

                            UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::SubmitMessage end state detected.. aborting",
                                                                          Thread.CurrentThread.GetHashCode()));
                        }

                        // abort this thread.
                        m_runningThread.Abort();
                        if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                        {
                            UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::SubmitMessage end state detected.. awaiting full stop",
                                                                          Thread.CurrentThread.GetHashCode()));
                        }
                        // wait until we are done.
                        while(m_runningThread.ThreadState != ThreadState.Stopped);
                        m_runningThread = null;
                        m_state = QH_ThreadState.NOT_STARTED;
                        if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                        {
                            UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::SubmitMessage end state detected.. restarting",
                                                                          Thread.CurrentThread.GetHashCode()));
                        }

                        // now restart..
                        Start();
                        break;
                    default:
                        // all other states we don't care about.
                        break;
                }
            }
            else
            {
                m_state = QH_ThreadState.NOT_STARTED;
                if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                {
                    UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::SubmitMessage ... starting",
                                                                  Thread.CurrentThread.GetHashCode()));
                }

                Start();
            }
        }

        /// <summary>
        /// submit a message for processing.  Will autostart queue or autorestart if necessary.
        /// it is NOT RECOMMENDED to depend on this behavior for first start, since the remote connected/disconnected
        /// events are only fired when we are multiprocessing.  Use <seealso cref="Start" /> to initially start the queue.
        /// </summary>
        /// <param name="qe">the command to be executed</param>
        public void SubmitMessage(CrystalisHIDAsynchCommand qe)
        {
            ThreadingStateHandler();
            lock(this)
            {
                m_messages.Enqueue(qe);
            }
            // process the message..
            m_pingWait.Set();
        }

        /// <summary>
        /// start message processing (and our one worker thread)
        /// </summary>
        /// <returns> StartErr </returns>
        public StartErr Start()
        {
            StartErr retVal = StartErr.SUCCESS;
            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
            {
                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::Start",
                                                Thread.CurrentThread.GetHashCode()));
            }

            m_quitNow = false;
            if(m_state == QH_ThreadState.NOT_STARTED)
            {
                m_state = QH_ThreadState.STARTING;
                
                if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                {
                    UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::Start  starting..",
                                                    Thread.CurrentThread.GetHashCode()));
                }
                
                m_runningThread = new Thread(MainQueueHandling);
                m_runningThread.IsBackground = true;
                m_runningThread.Start();
            }
            else
            {
                if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                {
                    UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::Start  already started!",
                                                    Thread.CurrentThread.GetHashCode()));
                }
                retVal = StartErr.ALREADY_STARTED;
            }
            return retVal;
        }

        /// <summary>
        /// main processing loop.  This is where all messages get processed.
        /// </summary>
        private void MainQueueHandling()
        {
            m_state = QH_ThreadState.RUNNING_IDLE;
            CrystalisHIDAsynchCommand qe = null;
            UEI.HidIf.CommandType retVal = UEI.HidIf.CommandType.ResponseSuccess;
            while(! m_quitNow)
            {
                // make sure we are clear before next loop.
                qe = null;

                // the normal.. 
                // check if it looks like we have anything..
                if (m_messages.Count > 0)
                {
                    if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                    {
                        UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::MainQueueHandling  msg rcvd",
                                                        Thread.CurrentThread.GetHashCode()));
                    }

                    // lock if it looks like we do..
                    lock(this)
                    {
                        // check again just in case.
                        // note that this detail prob. isn't required 
                        // if it is just ONE task servicing messages.. 
                        // but just in case we ever go to multiple workers
                        // this design will work.
                        if (m_messages.Count > 0)
                        {
                            if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                            {
                                UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::MainQueueHandling  msg dequeued",
                                                                Thread.CurrentThread.GetHashCode()));
                            }   
                        
                            qe = m_messages.Dequeue();
                        }
                    }
                    if(qe != null)
                    {
                        if(UEI.HidIf.HidIFTraceSwitch.trace_switch.Level >= System.Diagnostics.TraceLevel.Info)
                        {
                            UEI.Diagnostics.Debug.WriteLine(String.Format("({0})HIDQueueHander::MainQueueHandling  processing msg",
                                                            Thread.CurrentThread.GetHashCode()));
                        }

                        // do the command.
                        m_state = QH_ThreadState.RUNNING_BUSY;
                        retVal = qe.DoCommandProcess(m_crys_comm);                    
                        m_state = QH_ThreadState.RUNNING_IDLE;

                        if(retVal == UEI.HidIf.CommandType.PCErrorDeviceNotOpen)
                        {
                            // this message is unequivocal.. 
                            m_remoteConnected = false;
                        }
                    }
                    // done with message.
                    qe = null;
                }
                else
                {
                    // default behavior.. when not servicing a queue request, ping the remote then sleep for 1 second.
                    retVal = m_crys_comm.PingRemote();
                    if(retVal != UEI.HidIf.CommandType.ResponseSuccess)
                    {
                        m_remoteConnected = false;
                    }
                    else
                    {
                        m_remoteConnected = true;
                    }
                    // wait for one second, or until this event is 'Set'
                    m_pingWait.WaitOne(QUEUE_SLEEP,false);
                }
                // fire our remote connected/disconnected events if needed
                HandleRemoteConnected();
            }
            // we are done.
            m_state = QH_ThreadState.ENDED;
        }

        /// <summary>
        /// fire the remote connected/disconnected events if needed.
        /// </summary>
        private void HandleRemoteConnected()
        {
            if(m_remoteConnected != m_remoteConnectedPrev)
            {
                if(m_remoteConnected)
                {
                    if(RemoteCommEstablished_event != null)
                    {
                        RemoteCommEstablished_event();
                    }
                }
                else
                {
                    if(RemoteCommLost_event != null)
                    {
                        RemoteCommLost_event();
                    }
                }
                m_remoteConnectedPrev = m_remoteConnected;
            }
        }
    }
    
}
