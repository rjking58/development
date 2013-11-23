using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ThreadComm1
{
    class CommThreadTest
    {

        private Queue<ctt_message> ctt_msg_input_queue  = new Queue<ctt_message>();
        private Queue<ctt_message> ctt_msg_output_queue = new Queue<ctt_message>();
        private Object ctt_msg_input_queue_lock         = new Object();
        private Object ctt_msg_output_queue_lock        = new Object();

        public abstract class ctt_message
        {
            public abstract void doCommand(CommThreadTest ctt);
        }
        public class ctt_message1 : ctt_message
        {
            public override void doCommand(CommThreadTest ctt)
            {
                ctt.message1();
            }
        }
        public class ctt_message2 : ctt_message
        {
            public override void doCommand(CommThreadTest ctt)
            {
                ctt.message2();
            }
        }
        public class ctt_message3 : ctt_message
        {
            public override void doCommand(CommThreadTest ctt)
            {
                ctt.message3();
            }
        }


        private bool    m_stopThread = false;
        
        public CommThreadTest()
        {
        }

        ///<summary>
        /// Pulse the communications lock to wake up the sub process. 
        ///</summary>
        public void SendMessage(ctt_message msg)
        {
            Monitor.Enter(ctt_msg_input_queue_lock);
            Console.WriteLine ("set_NewMessageWaiting thread({0})...",Thread.CurrentThread.GetHashCode ());
            ctt_msg_input_queue.Enqueue(msg);
            Monitor.Pulse(ctt_msg_input_queue_lock);
            Monitor.Exit(ctt_msg_input_queue_lock);
        }
        ///<summary>
        /// set stop boolean to true.  This should be called by the owning thread, not the sub-thread.
        ///</summary>
        ///<returns>
        /// this is a setter only.. boolean value. 
        ///</returns>
        public bool StopThread
        {
            set
            {
                Monitor.Enter(ctt_msg_input_queue_lock);
                Console.WriteLine ("set_StopThread thread({0})...",Thread.CurrentThread.GetHashCode ());
                m_stopThread = value;
                Monitor.Pulse(ctt_msg_input_queue_lock);
                Monitor.Exit(ctt_msg_input_queue_lock);
            }
        }
        ///<summary>
        /// the main run loop for the sub thread.  This is the method name that should be passed to the
        /// ThreadStart object on construction.
        ///</summary>
        public void Run()
        {
            ctt_message curr_msg;
            while(!m_stopThread)
            {
                Console.WriteLine("CommThreadTest thread({0}) working...",Thread.CurrentThread.GetHashCode ());
                Monitor.Enter(ctt_msg_input_queue_lock);

                while(ctt_msg_input_queue.Count > 0)
                {
                    curr_msg = ctt_msg_input_queue.Dequeue();
                    curr_msg.doCommand(this);
                }

                Monitor.Wait(ctt_msg_input_queue_lock,10000);

                
            }
            Console.WriteLine("thread({0}) ENDING...",Thread.CurrentThread.GetHashCode ());
        }    
        private void message1()
        {
            Console.WriteLine("message1({0}) ...",Thread.CurrentThread.GetHashCode ());
        }
        private void message2()
        {
            Console.WriteLine("message2({0}) ...",Thread.CurrentThread.GetHashCode ());
        }
        private void message3()
        {
            Console.WriteLine("message3({0}) ...",Thread.CurrentThread.GetHashCode ());
        }
    }

    class tstClass
    {
        public static void Main()
        {
            bool endThread = false;
            CommThreadTest ctt = new CommThreadTest();
            Thread ctt_thread = new Thread(new ThreadStart(ctt.Run));
            ctt_thread.Start();
            string inp;

            // start the sub thread..
            while (!endThread)
            {

                Console.WriteLine("MAIN thread({0}) working...",Thread.CurrentThread.GetHashCode());
                Console.Write("input:");
                inp = Console.ReadLine();
                if (inp[0] == '1')
                {
                    ctt.SendMessage(new CommThreadTest.ctt_message1());
                }
                if (inp[0] == '2')
                {
                    ctt.SendMessage(new CommThreadTest.ctt_message2());
                }
                if (inp[0] == '3')
                {
                    ctt.SendMessage(new CommThreadTest.ctt_message3());
                }
                if (inp[0] == '4')
                {
                    ctt.SendMessage(new CommThreadTest.ctt_message1());
                    ctt.SendMessage(new CommThreadTest.ctt_message2());
                    ctt.SendMessage(new CommThreadTest.ctt_message3()); 
                }
                // 'stop'/'exit'/'quit'
                if (inp[0] == 's' || inp[0] == 'x' || inp[0] == 'q')
                {
                    ctt.StopThread = true;
                    endThread = true;
                }

            }
            while (ctt_thread.IsAlive)
            {
                Console.WriteLine("MAIN thread({0}) waiting on sub-thread...",Thread.CurrentThread.GetHashCode());
            }

        }
    }    
    
}
