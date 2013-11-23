using System;
using System.Collections.Generic;
using System.Text;

namespace exceptions
{
    class ExcTest
    {
        // intentional exception generation in a method..
        public static void genException()
        {
            int[] ge_nums = new int[6];

            Console.WriteLine("ENTER: ExcTest::genException()");
            Console.WriteLine("before exception is generated");
            // causes exception...
            for (int i = 0; i < 10; i++)
            // runs ok....
            //for (int i = 0; i < nums.Length; i++)
            {
                ge_nums[i] = i;
                Console.WriteLine("ge_nums[{0}]: {1}", i, ge_nums[i]);
            }
            // should never execute...
            Console.WriteLine("EXIT: ExcTest::genException()");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int[] nums = new int[6];
            try
            {
                Console.WriteLine("before exception is generated");
                // causes exception...
                for (int i = 0; i < 10; i++)
                // runs ok....
                //for (int i = 0; i < nums.Length; i++)
                {
                    nums[i] = i;
                    Console.WriteLine("nums[{0}]: {1}", i, nums[i]);
                }
                Console.WriteLine("never displayed!");
            }
            catch (IndexOutOfRangeException)
            {
                Console.WriteLine("index out of bounds!");
            }
            Console.WriteLine("after catch..");
            try
            {
                ExcTest.genException();
            }
            catch (IndexOutOfRangeException exc)
            {
                Console.WriteLine("standard message is:");
                Console.WriteLine(exc);
                Console.WriteLine("Stack Trace: " + exc.StackTrace);
                Console.WriteLine("Message: " + exc.Message);
                Console.WriteLine("TargetSite: " + exc.TargetSite);

            }
            Console.WriteLine("after ExcTest.genException catch..");
        }
    }
}
