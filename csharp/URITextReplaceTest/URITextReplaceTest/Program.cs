using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace URITextReplaceTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Uri simpleURI = new Uri("http://x/ASBService/ASBServicey/ASBServicez/v");

            string URIinAstring = simpleURI.ToString();

            string replaceString = URIinAstring.Replace("/ASBService/", "/ASBServiceV2/");

            Uri simpleURI2 = new Uri(replaceString);

            Console.WriteLine(simpleURI2.ToString());

        }
    }
}
