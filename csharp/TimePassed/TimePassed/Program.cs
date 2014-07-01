using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TimePassed
{
    class TimePassed
    {
        int TIME_UNTIL_OK = 5;

        DateTime m_lastTime = DateTime.Now;

        public TimePassed(int timePeriod)
        {
            TIME_UNTIL_OK = timePeriod;
        }
        public bool TimeHasPassed()
        {
            bool result = false;
            DateTime checkTime = DateTime.Now;

            TimeSpan diff = checkTime.Subtract(m_lastTime);

            if(diff.Seconds >= TIME_UNTIL_OK)
            {
                m_lastTime = DateTime.Now;
                result = true;
            }

            return result;
        }


    }
    class Program
    {
        static void Main(string[] args)
        {
            TimePassed tp = new TimePassed(5);
            for(int x = 1;
                x < 50;
                x++)
            {
                System.Threading.Thread.Sleep(1000);
                if(tp.TimeHasPassed())
                {
                    Console.WriteLine("yup");
                }
                else
                {
                    Console.WriteLine("nope");
                }
            }
        }
    }
}
