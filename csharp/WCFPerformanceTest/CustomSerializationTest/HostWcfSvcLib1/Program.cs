using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ServiceModel;
using System.ServiceModel.Description;

using WcfServiceLibrary1;
using System.Runtime.Serialization;

namespace HostWcfSvcLib1
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ServiceHost host = new ServiceHost(typeof(WcfServiceLibrary1.Service1)))
            {
                // surrogate definition..
                foreach (ServiceEndpoint ep in host.Description.Endpoints)
                {
                    foreach (OperationDescription op in ep.Contract.Operations)
                    {
                        DataContractSerializerOperationBehavior dataContractBehavior =
                            op.Behaviors.Find<DataContractSerializerOperationBehavior>()
                            as DataContractSerializerOperationBehavior;
                        if (dataContractBehavior != null)
                        {
                            dataContractBehavior.DataContractSurrogate = new valToTransferAsBytes();
                        }
                        else
                        {
                            dataContractBehavior = new DataContractSerializerOperationBehavior(op);
                            dataContractBehavior.DataContractSurrogate = new valToTransferAsBytes();
                            op.Behaviors.Add(dataContractBehavior);
                        }
                    }
                }

                // set up exporter with surrogate definition..
                WsdlExporter exporter = new WsdlExporter();
                object dataContractExporter;
                XsdDataContractExporter xsdInventoryExporter;
                if (!exporter.State.TryGetValue(typeof(XsdDataContractExporter),
                    out dataContractExporter))
                {
                    xsdInventoryExporter = new XsdDataContractExporter(exporter.GeneratedXmlSchemas);
                }
                else
                    xsdInventoryExporter = (XsdDataContractExporter)dataContractExporter;
                exporter.State.Add(typeof(XsdDataContractExporter), xsdInventoryExporter);


                if (xsdInventoryExporter.Options == null)
                    xsdInventoryExporter.Options = new ExportOptions();
                xsdInventoryExporter.Options.DataContractSurrogate = new valToTransferAsBytes();

                // export the endpoints..

                

                ServiceEndpointCollection sec = host.Description.Endpoints;
                foreach (ServiceEndpoint se in sec)
                {
                    Console.WriteLine(se.Name);
                    exporter.ExportEndpoint(se);
                }

                MetadataSet docs = null;
                docs = exporter.GetGeneratedMetadata();

                host.Description.


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
