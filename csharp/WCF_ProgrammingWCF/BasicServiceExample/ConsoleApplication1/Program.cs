using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace BasicServiceClient_TCP
{
    class Program
    {
        static void Main(string[] args)
        {
            // client config..

            ServiceReference1.Service1Client myClient = new ServiceReference1.Service1Client();
            try
            {

                myClient.Open();

                for (int x = 2; x < 12; x++)
                {
                    Console.WriteLine(myClient.GetData(x));
                    Thread.Sleep(1000);
                }
            }
            catch(Exception e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine("Stack Trace======================");
                Console.WriteLine(e.StackTrace);
            }


            myClient.Close();


        }
    }
}
