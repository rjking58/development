using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Singleton
{
    class Singleton
    {
        /// <summary>
        /// a PRIVATE constructor to prevent willy-nilly construction
        /// of this object without going through the GetInstance method
        /// </summary>
        private Singleton()
        {
            m_instance_ID = ++m_instance_counter;
        }
        /// <summary>
        /// print this classes ID.
        /// </summary>
        public void PrintID()
        {
            Console.WriteLine (m_instance_ID);
        }
        /// <summary>
        /// get an instance of the singleton
        /// </summary>
        /// <returns>the instance reference</returns>
        public static Singleton GetInstance()
        {
            // single threaded ONLY.. multi-threaded needs
            // lock protection for this activity..
            if(m_instance == null)
            {
                m_instance = new Singleton();
            }
            return m_instance;
        }
        /// <summary>
        /// where we store the single instance
        /// </summary>
        private static Singleton    m_instance = null;
        /// <summary>
        /// identification semantics
        /// </summary>
        private static int          m_instance_counter = 0;
        private int                 m_instance_ID = 0;
    }
    class Program
    {
        static void Main(string[] args)
        {
            Singleton inst = Singleton.GetInstance ();
            inst.PrintID();
            inst = Singleton.GetInstance ();
            inst.PrintID();
        }
    }
}
