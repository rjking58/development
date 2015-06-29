using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// https://msdn.microsoft.com/en-us/library/bb397687.aspx

namespace lambdasCSharp
{
    class Program
    {
        // declare the delegate...
        delegate int simpleLambdaDel(int x);
        delegate void printingLambdaDel(int x);

        delegate bool D();
        delegate bool D2(int i);

        D del;
        D2 del2;

        public void TestMethod(int input)
        {
            int j = 0;
            // Initialize the delegates with lambda expressions.
            // Note access to 2 outer variables.
            // del will be invoked within this method.
            del = () => { j = 10; return j > input; };

            // del2 will be invoked after TestMethod goes out of scope.
            del2 = (x) => { return x == j; };

            // Demonstrate value of j:
            // Output: j = 0 
            // The delegate has not been invoked yet.
            Console.WriteLine("j = {0}", j);        // Invoke the delegate.
            bool boolResult = del();

            // Output: j = 10 b = True
            Console.WriteLine("j = {0}. b = {1}", j, boolResult);
        }



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
            //    Where<string>( Func<string, bool> predicate)
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

            // example of outer variable capture for lambda..   
            Program prgrm = new Program();
            prgrm.TestMethod(5);

            // Prove that del2 still has a copy of
            // local variable j from TestMethod.
            bool bool_result = prgrm.del2(10);

            // Output: True
            Console.WriteLine(bool_result);

            Console.ReadKey();


        }
    }
}
