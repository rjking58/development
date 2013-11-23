using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;

namespace TimeMeasurements
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime startTime = DateTime.Now;

            Thread.Sleep(1000);

            DateTime endTime = DateTime.Now;

            TimeSpan ts = new TimeSpan((long)(endTime.Ticks - startTime.Ticks));

            Console.WriteLine(ts.TotalMilliseconds);
        }
    }
}
