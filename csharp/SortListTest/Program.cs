using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SortListTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SortedDictionary<int,int> sortedInts = new SortedDictionary<int,int>();

            AddVal(10,sortedInts);
            AddVal(9,sortedInts);
            AddVal(7,sortedInts);
            AddVal(5,sortedInts);
            AddVal(3,sortedInts);
            AddVal(1,sortedInts);

            foreach(KeyValuePair<int,int> kvp in sortedInts)
            {
                Console.WriteLine(kvp.Value);
            }
            Console.WriteLine();
            Console.WriteLine();

            AddVal(8,sortedInts);
            AddVal(6,sortedInts);
            AddVal(4,sortedInts);
            AddVal(2,sortedInts);
            AddVal(0,sortedInts);
            foreach(KeyValuePair<int,int> kvp in sortedInts)
            {
                Console.WriteLine(kvp.Value);
            }
        }

        private static void AddVal(int val,
                                   SortedDictionary<int,int> list)
        {
            if(! list.ContainsKey(val))
            {
                list.Add(val,val);
            }
        }
    }
}
