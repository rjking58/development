using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace YieldReturnExample
{
    class TestClass: IEnumerable<int>
    {
            #region IEnumerable<int> Members

            public IEnumerator<int> GetEnumerator()
            {
                for (int i = 0; i < 5; i++)
                    yield return i;
            }

            #endregion

            #region IEnumerable Members

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }

            #endregion

    }
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
