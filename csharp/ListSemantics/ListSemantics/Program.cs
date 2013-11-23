using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ListSemantics
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> myInts = new List<int>();

            for(int x = 0; x < 5; x++)
            {
                myInts.Add(x);
            }

            Console.WriteLine(myInts.Count);

            myInts.RemoveAt(3);

            Console.WriteLine(myInts.Count);

            myInts.RemoveAt(0);

            Console.WriteLine(myInts.Count);

            foreach(int currInt in myInts)
            {
                Console.WriteLine("curr:" + currInt);
            }
        }
    }
}
