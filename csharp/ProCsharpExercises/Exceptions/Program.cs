using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics;

namespace Exceptions
{
    class MyException : ApplicationException
    {
        public MyException(string msg) : base(msg)
        {
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                CauseAnException();
            }
            catch(Exception e)
            {
                Console.WriteLine("TargetSite==================================");
                Console.WriteLine(e.TargetSite);

                Console.WriteLine("Message==================================");
                Console.WriteLine(e.Message);

                Console.WriteLine("StackTrace==================================");
                Console.WriteLine(e.StackTrace);
            }
        }

        static void CauseAnException()
        {
            StackTrace st = new StackTrace(true);

            StackFrame[] frames = st.GetFrames();
            Console.WriteLine("Just before throw..");
            foreach(StackFrame sf in frames)
            {
                Console.WriteLine("=====>{0}", sf.ToString());
            }

            throw new MyException("a seriously stupid exception");
        }
    }
}
