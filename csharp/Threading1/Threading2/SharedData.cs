using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Threading2
{
    class SharedData
    {
        private static Object SharedDataLock = new Object();
        private static SharedData m_instance = null;
        private int m_num = 0;

        private SharedData()
        {
        }
        public static SharedData GetInstance()
        {
            lock(SharedDataLock)
            {
                Console.WriteLine("ENTER SharedData.GetInstance() is executing in thread(" + Thread.CurrentThread.GetHashCode() + ")" );
                if (m_instance == null)
                {
                    Console.WriteLine("m_instance created!");
                    m_instance = new SharedData();
                }
                Console.WriteLine("Exit SharedData.GetInstance() is executing in thread(" + Thread.CurrentThread.GetHashCode() + ")" );
            }
            return m_instance;
        }
        public int GetNum()
        {
            return m_num;
        }

        //private void SetNum(int num)
        //{
        //    m_num = num;
        //}
        public void incNum()
        {
            lock(SharedDataLock)
            {
                m_num++;
            }
        }

    }
}
