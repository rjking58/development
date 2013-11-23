using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace sieveOfEratosthenes
{
    class Program
    {
        static void Main(string[] args)
        {
            int         maxNum = 100000;
            List<bool>   isPrime = new List<bool>();
            for (int currNum = 0; currNum < maxNum; currNum++ )
            {
                isPrime.Add(true);
            }
            for (int currCheck = 4;
                currCheck < maxNum;
                currCheck += 2)
            {
                isPrime[currCheck] = false;
            }
            // we already know that all even numbers not 2 are not prime, so cut them out
            // of algorithm.
            for (int currCheck = 3;
                currCheck < maxNum;
                currCheck += 2)
            {
                if (isPrime[currCheck])
                {
                    int multiplier = 2;
                    int nextNotPrime = currCheck * multiplier;
                    while (nextNotPrime < maxNum)
                    {
                        isPrime[nextNotPrime] = false;
                        multiplier++;
                        nextNotPrime = currCheck * multiplier;
                    }
                }
            }

#if true
            // double check..
            // make sure each prime is not divisable by all numbers between 2 and
            // currentNumber - 1
            for(int x = 0;
                x < maxNum;
                x ++)
            {
                if(x > 3)
                {
                    if(isPrime[x])
                    {
                        for(int currDivisor = 2;
                            currDivisor < x;
                            currDivisor ++)
                        {
                            if( (x % currDivisor) == 0)
                            {
                                Console.WriteLine("failed at " + x);
                            }
                        }
                    }
                }
            }
#endif
            int lineBreakCount = 0;
            for(int x = 0;
                x < maxNum;
                x++)
            {
                if(isPrime[x])
                {
                    Console.Write(x + ",");

                    lineBreakCount++;
                    if(lineBreakCount > 10)
                    {
                        Console.WriteLine();
                        lineBreakCount = 0;
                    }
                }
            }
        }
    }
}
