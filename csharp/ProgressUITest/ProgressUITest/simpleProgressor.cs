using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ProgressUITest
{
    class simpleProgressor
    {
        public delegate void PercentCompleteDelegate(short percent);
        public event PercentCompleteDelegate PercentCompleteEvent = null;

        public void go()
        {
            for (int i = 0;
                 i < 100;
                 i++)
            {
                Thread.Sleep(50);
                if (PercentCompleteEvent != null)
                {
                    PercentCompleteEvent((short)((((double)i) / 100.0) * 100.0)); 
                }
            }
        
        }

    }
}
