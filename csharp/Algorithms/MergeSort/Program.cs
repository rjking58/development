using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MergeSort
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> unsortedList = new List<int>() { 4,5,2,3,9,1,11,6};

            List<int> sortedList = mrgSort(unsortedList);

            foreach(int x in sortedList)
            {
                Console.WriteLine(x);
            }

            unsortedList = new List<int>() { 4,5,2,3,9,1,11,6,12};

            sortedList = mrgSort(unsortedList);

            foreach(int x in sortedList)
            {
                Console.WriteLine(x);
            }

            unsortedList = new List<int>();
            Random rng = new Random();
            for(int x = 0; x < 1000000; x++)
            {
               unsortedList.Add(rng.Next(10000000));
            }
            Console.WriteLine("START");
            sortedList = mrgSort(unsortedList);
            Console.WriteLine("STOP");
#if false
            foreach(int x in sortedList)
            {
                Console.WriteLine(x);
            }
#endif

        }

        static List<int> mrgSort(List<int> unsortedList)
        {
            if(unsortedList.Count <= 1)
            {
                return unsortedList;
            }
            List <int> left = new List<int>();
            List <int> right = new List<int>();
            List <int> result = new List<int>();
            int middle = unsortedList.Count / 2;
            bool isOdd = (unsortedList.Count % 2) == 1;

            left.AddRange(unsortedList.GetRange(0,middle));
            right.AddRange(unsortedList.GetRange(middle,isOdd ? middle + 1 : middle));
            left = mrgSort(left);
            right = mrgSort(right);
            result = domrg(left,right);
            return result;
        }

        static List<int> domrg(List<int> left, List<int> right)
        {
            List<int>   result = new List<int>();
            int         leftOfst = 0;
            int         rightOfst = 0;

            while(leftOfst < left.Count || rightOfst < right.Count)
            {
                if(leftOfst < left.Count && rightOfst < right.Count)
                {
                    if(left[leftOfst] <= right[rightOfst])
                    {
                        result.Add(left[leftOfst]);
                        leftOfst++;
                    }
                    else
                    {
                        result.Add(right[rightOfst]);
                        rightOfst++;
                    }
                }
                else if(leftOfst < left.Count)
                {
                    result.Add(left[leftOfst]);
                    leftOfst++;
                }
                else if(rightOfst < right.Count)
                {
                    result.Add(right[rightOfst]);
                    rightOfst++;
                }
            }
            return result;
        }
    }
}
