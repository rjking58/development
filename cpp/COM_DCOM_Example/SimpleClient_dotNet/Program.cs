using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using COM_DCOM_Example_Simple_Interop;
using System.Runtime.InteropServices;

namespace SimpleClient_dotNet
{
    class Program
    {
        static void Main(string[] args)
        {
            ISimpleChatServer scs = null;
            try
            {
                scs = new SimpleChatServer();
            }
            catch (Exception e)
            {
                Console.WriteLine("===============================");
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                Console.WriteLine("===============================");
            }

            string retval = "one";
            string outputBStr = "";


            // Create a location for our string pointer..


            //IntPtr ourBstrPtr = Marshal.AllocHGlobal(Marshal.SizeOf(ourBstr));

            string name = "bozo";
            int val = 1;
            // space for one pointer..
            try
            {
                scs.CallMe(name
                , out val
                , out outputBStr
                );

            //String converted = Marshal.PtrToStringBSTR

            }
            catch(Exception e)
            {
                Console.WriteLine("==============================");
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                Console.WriteLine("==============================");
            }


            Console.WriteLine("FROM C#");

            Console.WriteLine(val + " " + outputBStr);

        }
    }
}
