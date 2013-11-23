using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Chapter1SimpleQuery
{
    class Program
    {
        static void Main(string[] args)
        {
            String[] QueryString = { "One", "Two", "Three", "Four", "Five", "Six", "Seven" };
            Console.WriteLine("Length>3");
            Console.WriteLine("===============================");
            var ThisQuery =
                from StringValue
                in QueryString
                where StringValue.Length > 3
                select StringValue;

            foreach (var str in ThisQuery)
            {
                Console.WriteLine("{0}[{1}]",str,str.Length);
            }

            Console.WriteLine(" ");
            Console.WriteLine("orderby StringValue orderby StringValue.Length");
            Console.WriteLine("===============================");
            var ThisQueryOrderBy =
                from StringValue
                in QueryString
                orderby StringValue
                orderby StringValue.Length
                select StringValue;

            foreach (var str in ThisQueryOrderBy)
            {
                Console.WriteLine("{0}[{1}]", str, str.Length);
            }


            Console.WriteLine(" ");
            Console.WriteLine("Two Froms");
            Console.WriteLine("===============================");
            Int32[] ArrayA = { 1, 2, 3, 4, 8 }; 
            Int32[] ArrayB = { 1, 3, 5, 7, 8 };

            var TwoFroms = from QueryA in ArrayA
                           from QueryB in ArrayB
                           where QueryA == QueryB
                           select new { QueryA, QueryB };

            foreach (var result in TwoFroms)
            {
                Console.WriteLine("QueryA[{0}] QueryB[{1}]", result.QueryA, result.QueryB);
            }
            
            Console.WriteLine(" ");
            Console.WriteLine("Two arrays.. join style");
            Console.WriteLine("===============================");

            var Joined = from QueryA in ArrayA
                         join QueryB in ArrayB
                         on QueryA equals QueryB
                         select new { QueryA, QueryB };
            foreach (var result in Joined)
            {
                Console.WriteLine("QueryA[{0}] QueryB[{1}]", result.QueryA, result.QueryB);
            }
            
            Console.WriteLine(" ");
            Console.WriteLine("Cartesian product, calculated values");
            Console.WriteLine("===============================");
            Int32[] NumAry1 = { 1, 2, 3, 4 };
            Int32[] NumAry2 = { 1, 2, 3, 4 };

            var Multiplicands = from Q1 in NumAry1
                                from Q2 in NumAry2
                                let multiplicand = Q1 * Q2
                                where multiplicand > 4
                                select new { Q1, Q2, multiplicand };

            foreach (var result in Multiplicands)
            {
                Console.WriteLine("{0} * {1} = {2}", result.Q1, result.Q2 , result.multiplicand);
            }
                 
            
            
        }
    }
}
