using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lambdasCSharp
{
    class Program
    {
        // declare the delegate...
        delegate int simpleLambdaDel(int x);
        delegate void printingLambdaDel(int x);

        struct s1
        {
            public string s1_str;
            public int s1_int;
        }

        static void Main(string[] args)
        {
            // simple lambda used with a delegate..
            simpleLambdaDel simpleLambda = (int x) => { return x* x; };
            int result = simpleLambda(5);
            Console.WriteLine(result);

            // lambda which returns nothing.
            printingLambdaDel printingLambda = (int x) => { Console.WriteLine(x); };

            printingLambda(10);


            // query syntax used in Where on collections..

            List<string> fruits =
               new List<string> { 
                                    "apple", 
                                    "passionfruit", 
                                    "banana", 
                                    "mango", 
                                    "orange", 
                                    "blueberry", 
                                    "grape", 
                                    "strawberry" };

            // Where in this case is declared as:
            //    WHere<string>( Func<string, bool> predicate)
            //                        ^param  ^retval
            IEnumerable<string> query = fruits.Where(fruit => fruit.Length < 6);

            foreach (string fruit in query)
            {
                Console.WriteLine(fruit);
            }


            // more complex where using a structure in a container


            List<s1> s1_list = new List<s1> {
                                            new s1 {s1_str = "one", s1_int = 1},
                                            new s1 {s1_str = "two", s1_int = 2},
                                            new s1 {s1_str = "three", s1_int = 3},
                                            new s1 {s1_str = "four", s1_int = 4},
                                            new s1 {s1_str = "five", s1_int = 5},
                                            new s1 {s1_str = "six", s1_int = 6}
                                        };
            IEnumerable<s1> s1query = s1_list.Where(s1Inst => s1Inst.s1_int > 3);

            foreach (s1 s1Inst in s1query)
            {
                Console.WriteLine(s1Inst.s1_str);
            }
        }
    }
}
