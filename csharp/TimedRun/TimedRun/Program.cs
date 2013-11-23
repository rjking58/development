using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;

namespace TimedRun
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime dt = DateTime.Now;
            dt = dt.AddMinutes(1.0);
            while (dt.CompareTo(DateTime.Now) > 0)
            {
                Thread.Sleep(1000);
                Console.WriteLine(dt.Hour + ":" + dt.Minute + ":" + dt.Second);
                Console.WriteLine(DateTime.Now.Hour + ":" + DateTime.Now.Minute + ":" + DateTime.Now.Second);                
            }

        }
    }
}
