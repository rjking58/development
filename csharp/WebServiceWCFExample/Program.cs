using System;
using System.Configuration;
using System.ServiceModel;
using System.ServiceModel.Activation;
using System.ServiceModel.Description;
using System.Diagnostics;


namespace Microsoft.ServiceModel.Samples
{
	public class MyServiceHost: ServiceHostBase
	{

		protected override void InitializeRuntime()
		{
			VirtualPathExtension extension = this.Extensions.Find<VirtualPathExtension>();
			EventLog.WriteEntry("ASP.NET",
					    "Service virtual path is : " + extension.VirtualPath,
					    EventLogEntryType.Information);
			base.InitializeRuntime();

		}
		
		protected override
				ServiceDescription
				CreateDescription (out System.Collections.Generic.IDictionary<String, ContractDescription> id )
		{
			id = null;
			return new ServiceDescription();
		}
		

	}

	
  // Define a service contract.
  [ServiceContract(Namespace = "http://Microsoft.ServiceModel.Samples")]
  public interface ICalculator
  {
    [OperationContract]
    double Add(double n1, double n2);
    [OperationContract]
    double Subtract(double n1, double n2);
    [OperationContract]
    double Multiply(double n1, double n2);
    [OperationContract]
    double Divide(double n1, double n2);
  }
  // Service class which implements the service contract.
  // Added code to write output to the console window
  public class CalculatorService : ICalculator
  {
    public double Add(double n1, double n2)
    {
      double result = n1 + n2;
      Console.WriteLine("Received Add({0},{1})", n1, n2);
      Console.WriteLine("Return: {0}", result);
      return result;
    }

    public double Subtract(double n1, double n2)
    {
      double result = n1 - n2;
      Console.WriteLine("Received Subtract({0},{1})", n1, n2);
      Console.WriteLine("Return: {0}", result);
      return result;
    }

    public double Multiply(double n1, double n2)
    {
      double result = n1 * n2;
      Console.WriteLine("Received Multiply({0},{1})", n1, n2);
      Console.WriteLine("Return: {0}", result);
      return result;
    }

    public double Divide(double n1, double n2)
    {
      double result = n1 / n2;
      Console.WriteLine("Received Divide({0},{1})", n1, n2);
      Console.WriteLine("Return: {0}", result);
      return result;
    }
  }


  
  public class Host
  {

    // Host the service within this EXE console application.
    public static void Main()
    {
      // Create a ServiceHost for the CalculatorService type and use
      // the base address from config.
      ServiceHost hostDefault = new 
       ServiceHost(typeof(CalculatorService));
      
      TimeSpan closeTimeout = hostDefault.CloseTimeout;
      
      TimeSpan openTimeout = hostDefault.OpenTimeout;


      ServiceAuthorizationBehavior authorization =
	      hostDefault.Authorization;

      ServiceCredentials credentials =
				      hostDefault.Credentials;

      ServiceDescription description = 
			  hostDefault.Description;


      int manualFlowControlLimit = 
			  hostDefault.ManualFlowControlLimit;


      NetTcpBinding portsharingBinding = new NetTcpBinding();
      hostDefault.AddServiceEndpoint(
	typeof( CalculatorService ),
	portsharingBinding,
	"net.tcp://localhost/MyService" );


      int newLimit = hostDefault.IncrementManualFlowControlLimit(100);
      
      using (ServiceHost serviceHost = new ServiceHost(typeof(CalculatorService)))
      {
        try
        {
          // Open the ServiceHost to start listening for messages.
          serviceHost.Open();
          // The service can now be accessed.
          Console.WriteLine("The service is ready.");
          Console.WriteLine("Press <ENTER> to terminate service.");
          Console.ReadLine();

          // Close the ServiceHost.
          serviceHost.Close();
        }
        catch (TimeoutException timeProblem)
        {
          Console.WriteLine(timeProblem.Message);
          Console.ReadLine();
        }
        catch (CommunicationException commProblem)
        {
          Console.WriteLine(commProblem.Message);
          Console.ReadLine();
        }
      }
    }

  }
}