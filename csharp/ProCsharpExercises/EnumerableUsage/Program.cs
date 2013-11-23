using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EnumerableUsage
{
    // hand coded enumerator
    // (old) school
    class MyIntCollection2 : IEnumerable<int>
    {
        private int[] m_intArray = { 9,8,7,6,5,4,3 };

        public IEnumerator<int> GetEnumerator()
        {
            return new MyIntEnumerator(m_intArray);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        class MyIntEnumerator : IEnumerator<int>
        {
            private int currOfst = -1;
            private int[] m_IntArray = null;

            public MyIntEnumerator(int[] IntArray)
            {
                m_IntArray = IntArray;
            }
            public int Current
            {
                get
                {
                    return m_IntArray[currOfst];
                }
            }
            Object IEnumerator.Current
            {
                get
                {
                    return Current;
                }
            }
            public void Reset()
            {
                currOfst = -1;
            }

            public bool MoveNext()
            {
                currOfst++;
                return (currOfst < m_IntArray.Length);
            }

            public void Dispose()
            {
            }

        }
    }

    // new school
    class IntCollection : IEnumerable
    {
        private int[] intArray = {4,7,11,33,42};

        public IntCollection()
        {

        }

        #region IEnumerable Members

        public IEnumerator GetEnumerator()
        {
            foreach(int i in intArray)
            {
                if((i % 2 ) == 0)
                {
                    yield return i;
                }
            }
        }

        #endregion
    }
    class Program
    {
        static void Main(string[] args)
        {
            IntCollection ic = new IntCollection();

            foreach( int i in ic)
            {
                Console.WriteLine(i);
            }

            MyIntCollection2 ic2 = new MyIntCollection2();
            foreach( int i in ic2)
            {
                Console.WriteLine(i);
            }
        }
    }
}
