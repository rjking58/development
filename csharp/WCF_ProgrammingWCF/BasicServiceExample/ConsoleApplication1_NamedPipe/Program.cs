using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BasicServiceClient_NamedPipe
{
    class Program
    {
        static void Main(string[] args)
        {
            // client config..

            ServiceReference1.Service1Client myClient = new ServiceReference1.Service1Client();

            myClient.Open();

            Console.WriteLine(myClient.GetData(44));

            myClient.Close();


        }
    }
}
