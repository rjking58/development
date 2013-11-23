using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LoopingAndBreaking
{
    class Program
    {
        static void Main(string[] args)
        {

            List<int> listOfInts = new List<int>();
            List<int> anotherListOfInts = new List<int>();
            listOfInts.Add(1);
            listOfInts.Add(2);
            listOfInts.Add(3);
            listOfInts.Add(4);
            listOfInts.Add(5);
            anotherListOfInts.Add(10);
            anotherListOfInts.Add(11);
            anotherListOfInts.Add(12);
            anotherListOfInts.Add(13);
            anotherListOfInts.Add(14);

            bool found = false;            
            foreach (int i in listOfInts)
            {
                foreach (int j in anotherListOfInts)
                {
                    Console.WriteLine(i + " " + j);
                    if (j == 11)
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }
        }
    }
}
