using System;
using System.Collections.Generic;
using System.Text;

namespace ArrayManip1
{
    class ArrayManip1
    {
        static void Main(string[] args)
        {
            byte [] x = new byte[10] {1,2,3,4,5,6,7,8,9,10};
            byte [] y = new byte[1] {33};


            Console.WriteLine(x.Length);
            Console.Write(@"x {");
            for(int i = 0;
                 i < x.Length;
                 i++ )
            {
                if(i > 0)
                {
                    Console.Write(",");
                }
                Console.Write(x[i]);
            }
            Console.WriteLine(@"}");

            Console.WriteLine(y.Length);
            Console.Write(@"y {");
            for(int i = 0;
                 i < y.Length;
                 i++ )
            {
                if(i > 0)
                {
                    Console.Write(",");
                }
                Console.Write(y[i]);
            }
            Console.WriteLine(@"}");

            // //////////////////////////////////////////////////
            // //////////////////////////////////////////////////
            // assign x->y
            // //////////////////////////////////////////////////
            // //////////////////////////////////////////////////
            Console.WriteLine("assigning x -> y");
            y = x;
            // //////////////////////////////////////////////////
            // //////////////////////////////////////////////////

            Console.WriteLine(x.Length);
            Console.Write(@"x {");
            for(int i = 0;
                 i < x.Length;
                 i++ )
            {
                if(i > 0)
                {
                    Console.Write(",");
                }
                Console.Write(x[i]);
            }
            Console.WriteLine(@"}");

            Console.WriteLine(y.Length);
            Console.Write(@"y {");
            for(int i = 0;
                 i < y.Length;
                 i++ )
            {
                if(i > 0)
                {
                    Console.Write(",");
                }
                Console.Write(y[i]);
            }
            Console.WriteLine(@"}");


        }
    }
}
