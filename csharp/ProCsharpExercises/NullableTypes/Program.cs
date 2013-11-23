using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NullableTypes
{
    class Program
    {
        static void Main(string[] args)
        {

            int? nullable_int = null;
            int? a_null = null;

            if(nullable_int == null)
            {
                nullable_int = 44;
            }
            Console.WriteLine(nullable_int);

            // assign a value if the previous expression is NULL..
            nullable_int = a_null ?? 33;
            Console.WriteLine(nullable_int);

        }
    }
}
