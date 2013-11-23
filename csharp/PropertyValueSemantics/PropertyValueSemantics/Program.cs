using System;
using System.Collections.Generic;
using System.Text;

namespace PropertyValueSemantics
{
    class myClass
    {
        private string my_str = "";
        public string MyStr
        {
            set
            {
                value = my_str;
            }
            get
            {
                return my_str;
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            myClass m = new myClass();
            
            m.MyStr = "woof";
            Console.WriteLine(m.MyStr);
        }
    }
}
