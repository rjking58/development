using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using COM_DCOM_Example_Simple_Interop;
using System.Runtime.InteropServices;

using System.Threading;

namespace SimpleClient_dotNet
{
    class Program
    {
        // this does the trick for COM.. otherwise it defaults to MTA, and
        // manual marshalling is in effect.
        [STAThread]
        //[MTAThread]
        static void Main(string[] args)
        {
#if false
            // this is the overcomplicated way.. the [STAThread] is the simple way :) 

            // required for interop to work with apartment STA declared COM
            // objects.. this is because if there is a mismatch, for this to 
            // work all marshalling must be handled manually... 'Easy' Interop seems
            // to be for matched apartment models only.
            Thread STA_Thread = new Thread(new ThreadStart(runComSTA));
            STA_Thread.ApartmentState = ApartmentState.STA;
            //STA_Thread.ApartmentState = ApartmentState.Unknown;
            STA_Thread.Start();
#else
            runComSTA();
#endif

            // idiot level thread synchronization, since this is only a test..
            Thread.Sleep(2000);
        }

        static void runComSTA()
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
            catch (Exception e)
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
