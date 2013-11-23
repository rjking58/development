using System;
using System.Collections.Generic;
using System.Text;

namespace InterfaceOrientedSingleton
{
    public interface ISingleton
    {
        void method1();
    }
    
    public class Singleton
    {
        public enum SingletonType
        {
            A,
            B,
            UNDEFINED
        }
        private static ISingleton m_instance = null;
        
        public static ISingleton GetInstance(SingletonType typ)
        {
            bool make_new = false;
            SingletonType is_type = SingletonType.UNDEFINED;
            if(m_instance != null)
            {
                if(m_instance is SingletonA)
                {
                    is_type = SingletonType.A;
                }
                else if (m_instance is SingletonB)
                {
                    is_type = SingletonType.B;
                }
                if(is_type != typ)
                {
                    make_new = true;
                }
            }
            else
            {
                make_new = true;
            }
                
            if(make_new)
            {
                switch (typ)
                {
                    case SingletonType.A:
                        Console.WriteLine("Creating A");
                        m_instance = new SingletonA();
                        break;
                    case SingletonType.B:
                        Console.WriteLine("Creating B");
                        m_instance = new SingletonB();
                        break;
                    default:
                        throw new System.ArgumentException("invalid type passed!");
                }
                
            }
            return m_instance;
        }
        class SingletonA : ISingleton
        {
            #region ISingleton Members
            public void method1()
            {
                Console.WriteLine("SingletonA");
            }
            #endregion
        }
        class SingletonB: ISingleton
        {
            #region ISingleton Members

            public void method1()
            {
                Console.WriteLine("SingletonB");
            }
            #endregion
        }
    }
    
    class Program
    {
        static void Main(string[] args)
        {

            Singleton.GetInstance(Singleton.SingletonType.A).method1();
            Singleton.GetInstance(Singleton.SingletonType.A).method1();
            Singleton.GetInstance(Singleton.SingletonType.A).method1();
            Singleton.GetInstance(Singleton.SingletonType.A).method1();
            Singleton.GetInstance(Singleton.SingletonType.B).method1();
            Singleton.GetInstance(Singleton.SingletonType.B).method1();
            Singleton.GetInstance(Singleton.SingletonType.B).method1();
            Singleton.GetInstance(Singleton.SingletonType.B).method1();
        }
    }
}
