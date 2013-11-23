using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Threading;

namespace ThreadingTest
{
    abstract class ControllableThread
    {

        private Thread mythread = null;


        private void MainThreadLoop()
        {
            DoWork();
        }

        public void Start()
        {
            mythread = new Thread(new ThreadStart(MainThreadLoop));
            mythread.Start();
        }

        
        public abstract void DoWork();
    }

    class MyControllableThread : ControllableThread
    {
        private static int g_masterId = 0;
        private EventWaitHandle m_workDone = null;
        private int m_id = 0;
        private int m_execs = 0;

        // stop semantics
        private bool m_GoAway = false;
        private EventWaitHandle m_workerWakeup = new EventWaitHandle(false, EventResetMode.AutoReset);

        public MyControllableThread(EventWaitHandle workDone)
        {
            m_id = g_masterId++;
            m_workDone = workDone;
        }

        public void Stop()
        {
            m_GoAway = true;
            m_workerWakeup.Set();
        }

        public void DoSomething()
        {
            m_workerWakeup.Set();
        }

        public override void DoWork()
        {
            while(! m_GoAway)
            {
                m_workerWakeup.WaitOne();
                m_execs++;
                Console.WriteLine("[" + m_id + "]" + "woof(" + m_execs + ")");
                Console.WriteLine("[" + m_id + "]" + "woof(" + m_execs + ")");
                m_workDone.Set();
            }
            Console.WriteLine("[" + m_id + "]" + "finis");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            EventWaitHandle t1WorkDone = new EventWaitHandle(false,EventResetMode.AutoReset);
            EventWaitHandle t2WorkDone = new EventWaitHandle(false, EventResetMode.AutoReset);
            EventWaitHandle t3WorkDone = new EventWaitHandle(false, EventResetMode.AutoReset);
            EventWaitHandle t4WorkDone = new EventWaitHandle(false, EventResetMode.AutoReset);

            MyControllableThread t1 = new MyControllableThread(t1WorkDone);
            MyControllableThread t2 = new MyControllableThread(t2WorkDone);
            MyControllableThread t3 = new MyControllableThread(t3WorkDone);
            MyControllableThread t4 = new MyControllableThread(t4WorkDone);
            t1.Start();
            t2.Start();
            t3.Start();
            t4.Start();

            for(int x = 0; x < 10; x++)
            {
                t1.DoSomething();
                t2.DoSomething();
                t3.DoSomething();
                t4.DoSomething();

                t1WorkDone.WaitOne();
                t2WorkDone.WaitOne();
                t3WorkDone.WaitOne();
                t4WorkDone.WaitOne();

            }

            t1.Stop();
            t2.Stop();
            t3.Stop();
            t4.Stop();
        }
    }
}
