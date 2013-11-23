#define BIN_SERIALIZE_TEST

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using CallTestService.ServiceReference1;

using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;




namespace CallTestService
{
    class Program
    {
        private const int TEST_COUNT = 20;
        private static int aggregateMilliseconds = 0;

        static void Main(string[] args)
        {
            ServiceReference1.Service1Client SvcProxy = new ServiceReference1.Service1Client("tcpWcfSvcLib1EP");
            SvcProxy.Open();

            //2,147,483,647
            byte[] valuesBytes;
            for (int x = 0; x < TEST_COUNT; x++)
            {
                DateTime startTime = DateTime.Now;
                valuesBytes = SvcProxy.GetData();
                DateTime endTime = DateTime.Now;
                TimeSpan ts = new TimeSpan(endTime.Ticks - startTime.Ticks);
                aggregateMilliseconds += ts.Milliseconds;

                Console.WriteLine("time for call:[" + ts.Milliseconds + "]");
                Console.WriteLine("size of data passed [" + valuesBytes.Length + "]");
            }
            Console.WriteLine("avg time per call [" + aggregateMilliseconds/TEST_COUNT + "]");

            SvcProxy.Close();
        }
    }
}
