using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BasicService;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace BasicService_HOSTING_TCP
{
    class Program
    {
        static void Main(string[] args)
        {
            // the URL that will host this service..
            // now in the APP config file..
            // >>>>>>>> this is NOW provided by the App.config <<<<<<<<<<<<<
            //Uri baseAddress = new Uri("http://localhost:8080/hello");
            // >>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

            // the name of the CONCRETE class implementing the service, and the address where it will be hosted.
            ServiceHost<BasicService.Service1> host = new ServiceHost<BasicService.Service1>();

            //ServiceHost host = new ServiceHost(typeof(BasicService.Service1));

            // allow meta data fetch.
            // >>>>>>>> this is NOW provided by the App.config <<<<<<<<<<<<<
            //ServiceMetadataBehavior smb = new ServiceMetadataBehavior();
            //smb.HttpGetEnabled = true;
            //smb.MetadataExporter.PolicyVersion = PolicyVersion.Policy15;
            //host.Description.Behaviors.Add(smb);
            // >>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

            // Open the ServiceHost to start listening for messages. Since
            // no endpoints are explicitly configured, the runtime will create
            // one endpoint per base address for each service contract implemented
            // by the service.
            
            Console.WriteLine("starting service on:");
            foreach (Uri theURI in host.BaseAddresses)
            {
                Console.WriteLine(theURI.AbsoluteUri);
            }
            host.Open();
            Console.WriteLine("The service is ready");
            Console.WriteLine("Press <Enter> to stop the service.");
            Console.ReadLine();

            // Close the ServiceHost.
            host.Close();
        }
    }
}
