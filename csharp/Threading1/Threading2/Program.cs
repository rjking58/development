// statements_lock2.cs
using System;
using System.Threading;

namespace Threading2
{
    class Threading2
    {
        public static void Main()
        {
            SimpleThread st1  = new SimpleThread("st1");
            SimpleThread st2 = new SimpleThread("st2");
            SimpleThread st3 = new SimpleThread("st3");        

            Thread t1 = new Thread(new ThreadStart(st1.run));
            Thread t2 = new Thread(new ThreadStart(st2.run));
            Thread t3 = new Thread(new ThreadStart(st3.run));

            t1.Start();
            t2.Start();
            t3.Start();

            Thread.Sleep(6000);

            st1.Stopthread();
            st2.Stopthread();
            st3.Stopthread();

            while (!(    st1.isComplete()
                      && st2.isComplete()
                      && st3.isComplete()
                    )
                  )
            {
                Console.WriteLine("waiting on children..");
            }
            int agg_loopcnt =   st1.GetLoopCnt()
                                + st2.GetLoopCnt()
                                + st3.GetLoopCnt()
                                ;

            Console.WriteLine("aggregated loopcnt:" + agg_loopcnt);
    //        Console.WriteLine("shared data int:" + SharedData.GetInstance().GetNum());
            Console.WriteLine("shared data int:" + SharedData.GetInstance().GetNum());        
        }
    }
}
        
   


