using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.IO;


namespace SimpleWebRequestor
{
    class Program
    {
        static void Main(string[] args)
        {
            //WebRequest req = WebRequest.Create("http://www.microsoft.com");
            WebRequest req = WebRequest.Create("http://192.168.0.100/lounge.html");

            WebResponse resp = req.GetResponse();
            StreamReader reader = new StreamReader(resp.GetResponseStream(), Encoding.ASCII);
            Console.WriteLine(reader.ReadToEnd());
        }
    }
}
