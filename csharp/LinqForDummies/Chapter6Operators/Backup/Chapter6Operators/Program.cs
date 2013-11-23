using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Chapter6Operators
{
    class Program
    {
        private enum NumToWord
        {
            Zero,
            One,
            Two,
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten
        }
        static void Main(string[] args)
        {

            Console.WriteLine("===========================================");
            Console.WriteLine("Concat");
            Console.WriteLine("===========================================");
            String[] First = { "One", "Two", "Three" };
            String[] Second = { "Four", "Five", "Six" };
            var ConCatQ = First.Concat<String>(Second);

            foreach (String val in ConCatQ)
            {
                Console.WriteLine(val);
            }

            Console.WriteLine("===========================================");
            Console.WriteLine("Concat");
            Console.WriteLine("===========================================");

            List<String> valList = new List<string>() { "1", "2", "3" , "4","5","6"};

            // take a list of strings containing numbers... 
            //   convert those to ints and apply a where clause to it to only get values greater than 3..
            //   then reconvert those values and cast them to the enum type...
            //   and finally (during output) call ToString to get them back to string for display.
            // the REAL tricking going on here is this little piece of magic:  NumToWord.One.ToString()
            // SNEAKY.
            var ConvertQ =
                (valList.AsEnumerable<String>()).Where(ThisElement => Convert.ToInt32(ThisElement) > 3).Select(ThisElement => (NumToWord)Convert.ToInt32(ThisElement));

            Console.WriteLine(" ");
            foreach (var ThisElement in ConvertQ)
            {
                Console.WriteLine(ThisElement.ToString());
            }

            Console.WriteLine("===========================================");
            Console.WriteLine("OfType");
            Console.WriteLine("===========================================");
            // Define a test object.    
            Dictionary<String, Object> TestData =       new Dictionary<string, object>();    
            // Fill the test object with data.    
            TestData.Add("One", 1);
            TestData.Add("Two", "Two");    
            TestData.Add("Three", 3);    
            TestData.Add("Four", "Four");    
            TestData.Add("Five", 5);    
            TestData.Add("Six", "Six");    
            // Create the query.    
            var ThisQuery = TestData.Values.OfType<String>();    
            // Display the output.    
            foreach (String ThisElement in ThisQuery)       
            {
                Console.WriteLine(ThisElement);
            }
            //note that you can't reuse a query here.. the typing
            // is retained on the var 'ThisQuery' after it is assigned from the above
            var ThisQuery2 = TestData.Values.OfType<int>();
            // Display the output.    
            foreach (int ThisElement in ThisQuery2)
            {
                Console.WriteLine(ThisElement);
            }

        }
    }
}
