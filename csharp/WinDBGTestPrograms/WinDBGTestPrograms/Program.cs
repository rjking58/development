using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WinDBGTestPrograms
{
    class MethodWithLocals
    {
        int m_x;
        string m_z;

        public void method1()
        {
            int method1_int1 = 10;

            method2(method1_int1);
        }

        public void method2(int int1)
        {
            int method2_int1 = 11;
            int method2_int2 = int1 + method2_int1;
            
            m_x = 44;
            m_z = "woof";

            int i;
            i = Console.Read();
            Console.WriteLine(method2_int2);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int i;
            //i = Console.Read();
            MethodWithLocals mwl = new MethodWithLocals();
            mwl.method1();
        }
    }
}
