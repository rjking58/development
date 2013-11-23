using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinqTest1
{
    class Program
    {
        public delegate int ChangeInt(int a);
        public delegate int TwoIntFunction(int a,int b);
        
        static public int DoubleIt(int x)
        {
            return x * 2;
        }


        static void Main(string[] args)
        {
            // LINQ on a simple array..
            string [] names = {"cat", "dog", "mouse", "rat"};
            
            IEnumerable<string> expr = from s in names
                                       where s.Length == 3
                                       orderby s
                                       select s.ToUpper();
                                       
            foreach(string item in expr)
            {
                Console.WriteLine(item);
            }
            
            // lambda expression syntax
            //    first.. basic delegate..
            ChangeInt myDoubler = new ChangeInt(Program.DoubleIt);
            Console.WriteLine(myDoubler(4));
            
            // now the same, using a lambda expression..
            ChangeInt myTripler = x => x*3;
            Console.WriteLine(myTripler(4));
            // lambda syntax:
            //  <argname> => <some function that permutes <argname>>
            
            // typed lambda..
            ChangeInt myQuadrupler = (int x) => x*4;
            Console.WriteLine(myQuadrupler(4));
            
            // two parameter type lambda expression
            TwoIntFunction MultNums = (int x,int y) => x*y;
            Console.WriteLine(String.Format(" 4*5 = {0}",MultNums(4,5)));
            
            // now the same examples, using Functional Generics provided by LINQ..
            // use of:
            //   public delegate TR Func<T0,TR>(T0 a0);
            //
            Func<int,int> myTripler2 = x => x*3;
            Console.WriteLine(myTripler(6));
            // lambda syntax:
            //  <argname> => <some function that permutes <argname>>
            
            // typed lambda..
            // use of:
            //   public delegate TR Func<T0,TR>(T0 a0);
            //
            Func<int,int> myQuadrupler2 = (int x) => x*4;
            Console.WriteLine(myQuadrupler(6));
            
            // two parameter type lambda expression
            // use of:
            //   public delegate TR Func<T0,T1,TR>(T0 a0,T1 a1);
            //
            Func<int,int,int> MultNums2 = (int x,int y) => x*y;
            Console.WriteLine(String.Format(" 7*8 = {0}",MultNums(7,8)));
            
            
        }
    }
}
