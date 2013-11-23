using System;
using System.Collections.Generic;
using System.Text;
using System.Timers;

namespace Clock1
{
    class simpleClock
    {
        private Timer m_clockTimer;
        private const int oneSecond = 1000;     //milliseconds
        private const int oneMinute = 60000;    //milliseconds
        public delegate void ClockEventDelegate(DateTime current_time);
        public event ClockEventDelegate clock_event = null;
        private class alarmTime : System.IComparable<alarmTime>
        {
            int alarm_hour;
            int alarm_minute;


            #region IComparable<alarmTime> Members

            public int CompareTo(alarmTime other)
            {
                // if < 0, this object < other
                // if == 0, this object == other
                // if > 0, this object > other
                int retVal;

                if (alarm_hour < other.alarm_hour)
                {
                    retVal = -1;
                }
                else
                {
                    if (alarm_hour > other.alarm_hour)
                    {
                        retVal = 1;
                    }
                    else
                    {
                        if (alarm_minute < other.alarm_minute)
                        {
                            retVal = -1;
                        }
                        else
                        {
                            if (alarm_minute > other.alarm_minute)
                            {
                                retVal = 1;
                            }
                            else
                            {
                                retVal = 0;
                            }
                        }
                    }
                }
                return retVal;
            }

            #endregion
        }
        private List<alarmTime> m_alarms = new List<alarmTime>();
        
        public simpleClock(bool useSeconds)
        {
            if (useSeconds)
            {
                m_clockTimer = new Timer(oneSecond);
            }
            else
            {
                m_clockTimer = new Timer(oneMinute);
            }
            m_clockTimer.Elapsed +=new ElapsedEventHandler(m_clockTimer_Elapsed);
            m_clockTimer.Enabled = false;
        }
        public void StartClock()
        {
            m_clockTimer.Enabled = true;
        }
        
        public void StopClock()
        {
            m_clockTimer.Enabled = false;
        }
        private void m_clockTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Console.WriteLine("Elapsed called...");
            DateTime currtime = DateTime.Now;
            checkForAlarm();
            if (clock_event != null)
            {
                clock_event(currtime);
            }
        }
        
        private void checkForAlarm()
        {
        }

        public void setAlarm(int hour, int minute)
        {
        }
        
    }
}
