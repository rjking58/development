using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;


namespace Threading_dotNet
{
    class SharedResource
    {
        static public Object lockit = new Object();
        static public int m_value = 0;
        static public void IncValue()
        {
            Monitor.Enter(lockit);

            m_value++;

            Monitor.Exit(lockit);
        }
        static public int GetVal()
        {
            return m_value;
        }
    }

    class UltraSimpleThread
    {
        public void ThreadProc()
        {
            //for (int x = 0; x < 3; x++)
            //{
            //    Console.WriteLine(x);
            //}
            for (int x = 0; x < 4000; x++)
            {
                SharedResource.IncValue();
            }

        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("threadID[" + Thread.CurrentThread.ManagedThreadId + "] threadState[" + Thread.CurrentThread.ThreadState + "]");

            UltraSimpleThread ust = new UltraSimpleThread();
            UltraSimpleThread ust2 = new UltraSimpleThread();
            UltraSimpleThread ust3 = new UltraSimpleThread();

            Thread simple = new Thread(new ThreadStart(ust.ThreadProc));
            Thread simple2 = new Thread(new ThreadStart(ust2.ThreadProc));
            Thread simple3 = new Thread(new ThreadStart(ust3.ThreadProc));

            simple.Start();
            simple2.Start();
            simple3.Start();

            simple.Join();
            simple2.Join();
            simple3.Join();
            Console.WriteLine(SharedResource.GetVal());
        }
    }
}
