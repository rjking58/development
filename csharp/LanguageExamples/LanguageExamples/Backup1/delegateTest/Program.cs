using System;
using System.Collections.Generic;
using System.Text;

delegate string strMod(string str);

namespace delegateTest
{
    class StringOps
    {
        public string replacesSpaces(string a)
        {
            Console.WriteLine("replace spaces with hyphens");
            return a.Replace(' ', '-');
        }

        public string removeSpaces(string a)
        {
            Console.WriteLine("removes spaces");
            string temp = "";
            int i;
            for (i = 0;
                i < a.Length;
                i++)
            {
                if (a[i] != ' ')
                {
                    temp += a[i];
                }
            }
            return temp;
        }
    }
    class Program
    {

        static string reverse(string a)
        {
            string temp = "";
            int i;
            int j;

            Console.WriteLine("reversing string");
            for(j = 0, i = a.Length-1; i>=0; i--, j++)
            {
                temp += a[i];
            }
            return temp;
        }

        static void Main(string[] args)
        {
            StringOps so = new StringOps();
            // delegate is a 'type'.
            // this acts a lot like a C++ functor.
            
            // delegate assigned an instance method
            strMod strOp = new strMod(so.replacesSpaces);
            string str;

            str = strOp("this is a test");
            Console.WriteLine("result:" + str);
            Console.WriteLine();

            // delegate assigned an instance method
            strOp = new strMod(so.removeSpaces);
            str = strOp("this is a test");
            Console.WriteLine("result:" + str);
            Console.WriteLine();

            // delegate assigned an static class method
            strOp = new strMod(reverse);
            str = strOp("this is a test");
            Console.WriteLine("result:" + str);
            Console.WriteLine();



        }
    }
}
