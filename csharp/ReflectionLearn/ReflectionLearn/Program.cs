using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ReflectionLearn
{
    class ClassToTest
    {
        private int j = 10;
        public int method1(int i)
        {
            return i + j;

        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int i = 42;

            System.Type i_typ = i.GetType();

            System.Console.WriteLine(i_typ);

            ClassToTest ctt = new ClassToTest();
            System.Type ctt_typ = ctt.GetType();
            System.Console.WriteLine(ctt_typ);



        }
    }
}
