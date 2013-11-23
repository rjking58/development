using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CallObjectMethodFromThreadTest_CSharp
{

    class ThreadControlClass
    {
    
        // boo.
        private string          m_str = "woof woof";
        private bool            m_EndWorkerThread = false;
        private Thread          m_workerThread = null;
        private EventWaitHandle workerEndThread_evt = new EventWaitHandle(false,EventResetMode.ManualReset);
        private int             m_workerThreadID = 0;

        private void    SetEndWorkerThread()
        {
            m_EndWorkerThread = true;
        }

        public ThreadControlClass() 
        {
        }

        public void StartWorkerThread()
        {
            m_workerThread = new Thread(new ThreadStart(WorkerThread1));
            m_workerThread.Start();
        }
        public void EndWorkerThread()
        {
            SetEndWorkerThread();
            workerEndThread_evt.WaitOne(5000);
            m_workerThread = null;
            workerEndThread_evt = null;
        }
        public bool IsEndWorkerThread()
        {
            return m_EndWorkerThread;
        }

        private void WorkerThread1()
        {
            while( ! IsEndWorkerThread() )
            {
                output();
                Thread.Sleep(100);
            }
            workerEndThread_evt.Set();
        }


        public void output()
        {
            Console.WriteLine("from the thread..");
        }
    }



    class Program
    {
        static void Main(string[] args)
        {
            ThreadControlClass tcc = new ThreadControlClass();

            tcc.StartWorkerThread();

    
            Thread.Sleep(4000);

            tcc.EndWorkerThread();


            Console.WriteLine("closed and complete");

        }
    }
}
