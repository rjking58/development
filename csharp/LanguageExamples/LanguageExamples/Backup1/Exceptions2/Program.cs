using System;
using System.Collections.Generic;
using System.Text;

namespace Exceptions2
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] numer = { 4, 8, 16, 32, 64, 128, 256, 512 };
            int[] denom = { 2, 0, 4, 4, 0, 8 };

            for (int i = 0;
                i < numer.Length;
                i++)
            {
                try
                {
                    Console.WriteLine(numer[i] + "/" +
                                      denom[i] + " is " +
                                      numer[i] / denom[i]);
                }
                catch (DivideByZeroException)
                {
                    Console.WriteLine(numer[i] + "/" +
                                      denom[i] + " is UNDEFINED");

                    Console.WriteLine("since division by zero is UNDEFINED!!");
                }
                catch (IndexOutOfRangeException)
                {
                    Console.WriteLine("oops.. either numer[{0}] or denom[{0}] doesn't exist", i);
                }
            }

            try
            {
                Console.WriteLine("before manual throw of DivideByZeroException");
                throw new DivideByZeroException();
            }
            catch (DivideByZeroException)
            {
                Console.WriteLine("DivideByZeroException exception caught");
            }
            finally
            {
                Console.WriteLine("'finally' clean up code for DivideByZeroException manual throw block");
            }
            Console.WriteLine("after throw demo block");
        }
    }
}
