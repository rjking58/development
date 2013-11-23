using System;
using System.Collections.Generic;
using System.Text;

namespace MethodRefAndOut
{
    public class myObj
    {
        private int m_i;
        private int m_j;

        public myObj(int i, int j)
        {
            m_i = i;
            m_j = j;
        }

        public void Iam()
        {
            System.Console.Write(    "m_i(" + m_i + ")"
                                  +  "m_j(" + m_j + ")" );
        }
    }
    public class RefSwapper
    {
        public static void swap<T>(ref T ob1, ref T ob2)
        {
            T    tmp;
            tmp = ob1;
            ob1 = ob2;
            ob2 = tmp;
        }
        public static void setTo7(out int i1)
        {
            i1 = 7;
        }
    }
    class MethodRefAndOut
    {
        static void Main(string[] args)
        {
            myObj ob1 = new myObj(1,2);
            myObj ob2 = new myObj(3,4);

            // ref parameter demo.. with Generics! :D
            System.Console.Write( "ob1[" );
            ob1.Iam();
            System.Console.WriteLine("]");

            System.Console.Write("ob2[");
            ob2.Iam();
            System.Console.WriteLine("]");

            RefSwapper.swap(ref ob1, ref ob2);

            System.Console.Write("ob1[");
            ob1.Iam();
            System.Console.WriteLine("]");

            System.Console.Write("ob2[");
            ob2.Iam();
            System.Console.WriteLine("]");

            // out parameter demo.
            int i = 0;
            System.Console.WriteLine("before: i[" + i + "]");
            RefSwapper.setTo7(out i);
            System.Console.WriteLine("after: i[" + i + "]");

        }
    }
}
