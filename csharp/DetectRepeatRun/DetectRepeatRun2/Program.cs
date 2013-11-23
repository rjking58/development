using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace DetectRepeatRun2
{
    class Program
    {
        static void Main(string[] args)
        {
            //create a mutex with a unique name   
            CSingleInstanceOfProgram si = new CSingleInstanceOfProgram("{88D4E01E-CB8F-45af-9073-766C11050369}");
            
            if(!si.IsRunning())
            {
                // we be cool.  Continue on
                Console.WriteLine("First Copy");
                Console.ReadLine();
                // and release at the end.
                si.Release();
            }
            else
            {
                // did not gain the mutex, so this must be another copy of this program running.
                Console.WriteLine("Already running...!");
                Console.ReadLine();
                // note.. no need to release here.. since we never owned the Mutex to begin with..
            }
        }
    }
    
    class CSingleInstanceOfProgram
    {
        //our Mutex member variable
        private Mutex m_mutex;	
        public CSingleInstanceOfProgram(string mutexname)
        {
            m_mutex=new Mutex(false,mutexname);
        }
        
        public void Release()
        {
            //we must release it when the CSingleInstance object is destroyed
            m_mutex.ReleaseMutex();
        }
        public bool IsRunning()
        {
            //you can replace 10 with 1 if you want to save 9 ms
            return !m_mutex.WaitOne(10,true);           
        }
    }
}



