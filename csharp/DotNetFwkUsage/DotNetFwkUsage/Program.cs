using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using directUseDLL;

namespace DotNetFwkUsage
{
    class Program
    {
        static void Main(string[] args)
        {
            // Get Current version of fwk we are using..
            Console.WriteLine("console exe:: environment reports {0}",Environment.Version.ToString());
            DirectUse.PrintVersion();
        }
    }
}
