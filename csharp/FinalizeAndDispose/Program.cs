using System;
using System.Collections.Generic;
using System.Text;

namespace FinalizeAndDispose
{
    class MyContainedClass : IDisposable
    {
        private static int nxt_obj_val = 0;
        private int obj_id = 0;
        private int m_parentID = 0;
        
        private bool disposed = false;
        
        public MyContainedClass(int parentID)
        {
            obj_id = nxt_obj_val++;
            m_parentID = parentID;
        }

        // MS Dispose pattern        
        ~MyContainedClass()
        {
            Cleanup(false);
            GC.SuppressFinalize(this);
        }
        public void Dispose()
        {
            Cleanup(true);
        }
        private void Cleanup(bool disposing)
        {
            if(!this.disposed)
            {
                if(disposing)
                {
                    // call dispose on all contained objects, since we are manually 
                    // disposing
                    Console.WriteLine("Via disposal");
                }
                else
                {
                    Console.WriteLine("Via finalizer");
                }
                // cleanup unmanaged resources
                Console.WriteLine("MyContainedClass[" + m_parentID + ":" + obj_id + "]");
            }
            disposed = true;
        }
    }
    class MyClass : IDisposable
    {
        private static int nxt_obj_val = 0;
        private int obj_id = 0;
        
        private MyContainedClass m_mcc = null;
        private MyContainedClass m_mcc2 = null;
        
        private bool disposed = false;
        
        public MyClass()
        {
            obj_id = nxt_obj_val++;
            m_mcc = new MyContainedClass(obj_id);
            m_mcc2 = new MyContainedClass(obj_id);
        }

        // MS Dispose pattern        
        ~MyClass()
        {
            Cleanup(false);
            GC.SuppressFinalize(this);
        }
        public void Dispose()
        {
            Cleanup(true);
        }
        private void Cleanup(bool disposing)
        {
            if(!this.disposed)
            {
                if(disposing)
                {
                    // call dispose on all contained objects, since we are manually 
                    // disposing
                    Console.WriteLine("Via disposal");
                    m_mcc.Dispose();
                    m_mcc2.Dispose();
                }
                else
                {
                    Console.WriteLine("Via finalizer");
                }
                // cleanup unmanaged resources
                Console.WriteLine("MyClass[" + obj_id + "]");
            }
            disposed = true;
        }
        
        
    }
    class Program
    {
        static void Main(string[] args)
        {
            for(int x = 0; x < 30; x++)
            {
                using(MyClass mc = new MyClass())
                {
                }
            }
        }
    }
}
