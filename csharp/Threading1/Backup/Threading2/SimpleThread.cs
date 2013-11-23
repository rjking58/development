using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Threading2
{

    class SimpleThread
    {
        private SharedData  m_sd_instance;
        private String      m_name = "default";
        private Thread      m_thread;
        private int         m_loopcnt = 0;
        private int         m_waittime = 10;
        private bool     m_thread_complete = false;
        private bool     m_threadenabled = false;


        public SimpleThread(String name)
        {
            m_name = name;
        }

        public void run()
        {
            m_threadenabled = true;
            m_sd_instance = SharedData.GetInstance();
            Thread.Sleep(200);

            while(m_threadenabled)
            {
                m_loopcnt++;
                Console.WriteLine("thread " + m_name + " executing loop#" + m_loopcnt);            
                //bad!
    //            int x = SharedData.GetInstance().GetNum();
    //            x++;
    //            SharedData.GetInstance().SetNum(x);
    //            SharedData.GetInstance().incNum();
                m_sd_instance.incNum();            
                //end bad!!
            }
            Console.WriteLine(m_name + "exiting..");
            m_thread_complete = true;
        }

        public void Stopthread()
        {
            m_threadenabled = false;
            //m_thread = null;
        }
        public int GetLoopCnt()
        {
            return m_loopcnt;
        }
        public bool isComplete()
        {
            return m_thread_complete;
        }
    }
}
