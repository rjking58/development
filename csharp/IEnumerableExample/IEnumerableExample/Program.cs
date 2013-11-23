using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IEnumerableExample
{
    class Program
    {
        class Myclass
        {
            List<int> m_l = new List<int>() {1,2,3,4,5,6,7,8,9};

            public IEnumerable<int> GetAll()
            {
                foreach(int i in m_l)
                {
                    yield return i;
                }
            }

            public IEnumerable<int> GetOdd()
            {
                foreach(int i in m_l)
                {
                    if( (i % 2) != 0)
                    {
                        yield return i;
                    }
                }
            }
        }
        static void Main(string[] args)
        {
            Myclass mc = new Myclass();

            foreach (int i in mc.GetAll())
            {
                Console.WriteLine(i);
            }


            foreach (int i in mc.GetOdd())
            {
                Console.WriteLine(i);
            }

        }
    }
}
