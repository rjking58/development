using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace directUseDLL
{
    public class DirectUse
    {
        public static void PrintVersion()
        {
            Console.WriteLine("directUse dll:: environment reports {0}", Environment.Version.ToString());
        }
    }
}
