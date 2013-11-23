using System;
using System.Collections.Generic;
using System.Text;

namespace InputAndOutput
{
    class KbIn
    {
        static void Main()
        {
            //char ch;

            //Console.Write("Press a key followed by ENTER: ");
            //ch = (char)Console.Read();
            //Console.WriteLine("Your key is: " + ch);
            // **or**

            //string str;
            //Console.Write("Type characters followed by ENTER: ");
            //str = Console.ReadLine();
            //Console.WriteLine("You typed: " + str);

            // using specific standard output streams..

            Console.Out.WriteLine("create an error");
            int a = 10;
            int b = 0;
            int result;
            try
            {
                result = a / b;
            }
            catch (DivideByZeroException exc)
            {
                Console.Error.WriteLine(exc);
            }

        }
    }
}
