using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEnumerableTestProg
{
    class MyClass
    {
        private List<int> m_vals = new List<int>();

        public MyClass()
        {
            m_vals.Add(1);
            m_vals.Add(2);
            m_vals.Add(3);
            m_vals.Add(4);
            m_vals.Add(5);
            m_vals.Add(6);
            m_vals.Add(7);
            m_vals.Add(8);
            m_vals.Add(9);
            m_vals.Add(10);
            m_vals.Add(11);
        }

        public IEnumerable<int> GetAllVals()
        {
            foreach (int currInt in m_vals)
            {
                yield return currInt;
            }
        }
        public IEnumerable<int> GetEvenVals()
        {
            foreach (int currInt in m_vals)
            {
                if ((currInt % 2) == 0)
                {
                    yield return currInt;
                }
            }
        }
        public IEnumerable<int> GetOddVals()
        {
            foreach (int currInt in m_vals)
            {
                if ((currInt % 2) != 0)
                {
                    yield return currInt;
                }
            }
        }
        
    }
    class Program
    {
        
        static void Main(string[] args)
        {
            MyClass mc = new MyClass();

            foreach (int currInt in mc.GetAllVals())
            {
                Console.WriteLine(currInt);
            }
            Console.WriteLine(" ");
            foreach (int currInt in mc.GetEvenVals())
            {
                Console.WriteLine(currInt);
            }
            Console.WriteLine(" ");
            foreach (int currInt in mc.GetOddVals())
            {
                Console.WriteLine(currInt);
            }
            Console.WriteLine(" ");
            
        }
    }
}
