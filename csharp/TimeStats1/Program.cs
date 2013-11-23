using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace TimeStats1
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime LastMark = DateTime.Now;
            Console.WriteLine(LastMark.ToLongTimeString());
            TimeSpan s1 = new TimeSpan();
            TimeSpan s2 = new TimeSpan();
            for(int x = 0;x < 10; x++)
            {
                LastMark = DateTime.Now;
                Thread.Sleep(1000);
                // MOST important to assign a new one.. since Add doesn't do it in place.. 
                // the result of the add is RETURNED from the method.
                s1 = s1.Add(DateTime.Now.Subtract(LastMark));
                LastMark = DateTime.Now;
                Thread.Sleep(10);
                s2 = s2.Add(DateTime.Now.Subtract(LastMark));
                LastMark = DateTime.Now;
            }
            Console.WriteLine(s1.TotalSeconds);
            Console.WriteLine(s2.TotalSeconds);
        }
    }
}