using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Management;

namespace NetworkConfigExample
{
    class Program
    {
        static void Main(string[] args)
        {
//            ManagementObjectSearcher query = new ManagementObjectSearcher("SELECT * FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = 'TRUE'") ;
            ManagementObjectSearcher query = new ManagementObjectSearcher("SELECT * FROM Win32_NetworkAdapterConfiguration") ;
            ManagementObjectCollection queryCollection = query.Get();

            foreach( ManagementObject mo in queryCollection )
            {
                Console.WriteLine("Network Card: {0}", mo["Description"]);
                Console.WriteLine("============================================================");
//                Console.WriteLine("IP Address       : {0}", mo["IPAddress"]);
                Console.WriteLine("IP Address:");
                string [] addresses = (string []) mo["IPAddress"];
                if(addresses != null)
                {
                    foreach( string ipaddress in addresses)
                    {
                        Console.WriteLine("    {0} ", ipaddress);
                    }
                }
                Console.WriteLine("IP Enabled       : {0}", mo["IPEnabled"]);
                Console.WriteLine("MAC Address      : {0}", mo["MACAddress"]);
//                Console.WriteLine("DNS Servers      : {0}", mo["DNSServerSearchOrder"]);
                Console.WriteLine("DNS Servers");
                string [] DNSServers = (string []) mo["DNSServerSearchOrder"];
                if(DNSServers != null)
                {
                    foreach( string DNSEntry in DNSServers)
                    {
                        Console.WriteLine("    {0} ", DNSEntry);
                    }
                }
                //Console.WriteLine("Default Gateway  : {0}", mo["DefaultIPGateway"]);
                Console.WriteLine("Gateways");
                string [] Gateways = (string []) mo["DefaultIPGateway"];
                if(Gateways != null)
                {
                    foreach( string Gateway in Gateways)
                    {
                        Console.WriteLine("    {0} ", Gateway);
                    }
                }
                Console.WriteLine();
            }
            
        }
    }
}
