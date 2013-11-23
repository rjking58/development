using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ServiceModel;
using System.ServiceModel.Description;

namespace HostWcfSvcLib1
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ServiceHost host = new ServiceHost(typeof(WcfServiceLibrary1.Service1)))
            {
                host.Open();

                PrintDescription(host);

                Console.WriteLine("The Trading Service is available.  Press any key to exit.");
                Console.ReadKey();

                host.Close();
            }

        }

        private static void PrintDescription(ServiceHost sh)
        {
            // Print endpoint descriptions of the service.
            Console.WriteLine("Endpoints:");
            foreach (ServiceEndpoint servEP in sh.Description.Endpoints)
            {
                // Print endpoint information.
                Console.WriteLine(
                          "\tName:\t{0}\nAddress:\t{1}\nBinding:\t{2}\nContract:\t{3}\n",
                                   servEP.Name, servEP.Address,
                                   servEP.Binding.Name, servEP.Contract.Name);
            }
            Console.WriteLine("");
        }
    }
}
