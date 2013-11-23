using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EnumTypes
{
    class Program
    {
        enum myEnum : int
        {
            first = 1,
            second = 2,
            third = 3
        }
        static void Main(string[] args)
        {
            myEnum myE = myEnum.first;

            // prints string value of enum "first", not "1"
            Console.Write(myE.ToString());
            Console.WriteLine(" is " + (int) myE);
            myE.GetType();

            try
            {
                myEnum myParsedE = (myEnum)Enum.Parse(typeof(myEnum), "second");
                Console.Write(myParsedE.ToString());
                Console.WriteLine(" is " + (int)myParsedE);

                myEnum myParsedE2 = (myEnum)Enum.Parse(typeof(myEnum), "bazurble");
                Console.Write(myParsedE2.ToString());
                Console.WriteLine(" is " + (int)myParsedE2);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
        }
    }
}
