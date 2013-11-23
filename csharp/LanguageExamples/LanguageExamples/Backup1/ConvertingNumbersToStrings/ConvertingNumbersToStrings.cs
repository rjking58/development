using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;

namespace ConvertingNumbersToStrings
{
    class ConvertingNumbersToStrings
    {
        static void Main(string[] args)
        {
            // simple decimal number
            string num = "1234";
            int i; 
            try
            {
                i = Int32.Parse(num); 
            }
            catch(System.FormatException ex)
            {   
                i = 0;
                Console.WriteLine("oops.. bad number");
            }
            Console.WriteLine("1234=" + i);
            // invalid number
            num = "1234.$"; 
            try
            {
                i = Int32.Parse(num);            
            }
            catch (System.FormatException ex)
            {
                i = 0;
                Console.WriteLine("oops.. bad number");
            }
            Console.WriteLine("1234.$=" + i);
            
            num = "ab";
            try
            {
                i = Int32.Parse(num,NumberStyles.AllowHexSpecifier);
            }
            catch (System.FormatException ex)
            {
                i = 0;
                Console.WriteLine("oops.. bad number");
            }
            Console.WriteLine("ab=" + i);
            Console.WriteLine("ab=" + String.Format("{0:X2}",i));

            num = "abx";
            try
            {
                i = Int32.Parse(num,NumberStyles.AllowHexSpecifier);
            }
            catch (System.FormatException ex)
            {
                i = 0;
                Console.WriteLine("oops.. bad number");
            }
            Console.WriteLine("abx=" + i);
            Console.WriteLine("abx=" + String.Format("{0:X2}",i));
            
            
            // hexadecimal number
            // invalid hexadecimal number
        }
    }
}
