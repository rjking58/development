using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TypeCheckingConstructs
{
    class an_X 
    {
        public override string ToString()
        {
            return "X";
        }
    }

    class a_Y
    {
        public override string ToString()
        {
            return "Y";
        }
    }
    class a_sub_Y : a_Y
    {
        public override string ToString()
        {
            return "sub_Y";
        }
    }

    class Program
    {

        static void Main(string[] args)
        {
            // ========================================
            // 'as' keyword
            // ========================================
            object y = new a_sub_Y();
            object sub_y = new a_sub_Y();
            an_X x = y as an_X;
            if(x == null)
            {
                Console.WriteLine("bad assign! (yup..)");
            }

            a_Y a_y = sub_y as a_Y;
            if(a_y != null)
            {
                Console.WriteLine(a_y.ToString());
            }

            // ========================================
            // is keyword
            // ========================================
            if (y is a_sub_Y)
            {
                Console.WriteLine("yup, a_sub_y");
            }
            if (y is a_Y)
            {
                Console.WriteLine("yup, its also a_Y");
            }

        }
    }
}
