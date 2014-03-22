using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DictionaryOneLookupExperiment
{
    class X
    {
        public int m_int;
        public X(int pInt)
        {
            m_int = pInt;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<int, X> Xlookup = new Dictionary<int, X>();

            for(int currX = 1;
                currX <= 10;
                currX++)
            {
                X myX = new X(currX);

                Xlookup.Add(currX,myX);
            }

            // this mimics the find/check for end semantics of STL and results in only 
            // one search per interesting key in the Dictionary.
            for(int currX = 1;
                currX <= 12;
                currX++)
            {
                X foundX = null;
                if (Xlookup.TryGetValue(currX, out foundX))
                {
                    Console.WriteLine("foundX[" + foundX.m_int + "]");
                }
                else
                {
                    Console.WriteLine("no entry for key[" + currX + "]");
                }
            }

        }
    }
}
