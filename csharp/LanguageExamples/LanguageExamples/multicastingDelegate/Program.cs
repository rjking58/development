using System;
using System.Collections.Generic;
using System.Text;

delegate void strMod(ref string a);

delegate void myEventHandler();

namespace multicastingDelegate
{
    class MyEvent
    {
        public event myEventHandler SomeEventHandler;

        public void OnSomeEvent()
        {
            if (SomeEventHandler != null)
            {
                SomeEventHandler();
            }
        }
    }
    class StringOps
    {
        public void replacesSpaces(ref string a)
        {
            Console.WriteLine("replace spaces with hyphens");
            a = a.Replace(' ', '-');
        }

        public void removeSpaces(ref string a)
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
            a = temp;
        }
    }

    class Program
    {
        static void handler()
        {
            Console.WriteLine("SomeEvent occurred");
        }

        static void reverse(ref string a)
        {
            string temp = "";
            int i;
            int j;

            Console.WriteLine("reversing string");
            for (j = 0, i = a.Length - 1; i >= 0; i--, j++)
            {
                temp += a[i];
            }
            a = temp;
        }

        static void Main(string[] args)
        {
            StringOps so = new StringOps();
            // delegate is a 'type'.
            // this acts a lot like a C++ functor.

            // delegate assigned an instance method
            strMod strOp;
            strMod replaceMod = new strMod(so.replacesSpaces);
            strMod removeMod = new strMod(so.removeSpaces);
            strMod reverseMod = new strMod(reverse);
            string my_str = "this is a test";
            strOp = replaceMod;
            strOp += reverseMod;

            strOp(ref my_str);
            Console.WriteLine("result:" + my_str);
            Console.WriteLine();

            my_str = "this is a test";
            strOp -= replaceMod;
            strOp += removeMod;
            strOp(ref my_str);
            Console.WriteLine("result:" + my_str);
            Console.WriteLine();

            MyEvent evt = new MyEvent();
            evt.SomeEventHandler += new myEventHandler(handler);
            evt.OnSomeEvent();
        }
    }
}
