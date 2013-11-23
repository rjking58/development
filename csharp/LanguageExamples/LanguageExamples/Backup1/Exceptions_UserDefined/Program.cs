using System;
using System.Collections.Generic;
using System.Text;

namespace Exceptions_UserDefined
{

    public class MySimpleException : ApplicationException
    {
        public MySimpleException() 
        {
        }
        public MySimpleException(string message) 
        : base (message)
        {
        }
    }
    class Program
    {
        
    
        static void Main(string[] args)
        {
            // simple test
            try
            {
                f1();
            }
            catch(MySimpleException ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
        }
        static void f1()
        {
            f2();
        }
        static void f2()
        {
            throw new MySimpleException("weee!");
        }
    }
}
