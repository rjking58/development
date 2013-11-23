using System;
using System.Collections.Generic;
using System.Text;

namespace StringToByteEccentricities
{
    class Program
    {
        static void Main(string[] args)
        {
            string x = "abcd";
            string y = "1234";
            string z = "XyZ@";
            
            ASCIIEncoding a_encoding = new ASCIIEncoding();
            byte [] encoded = a_encoding.GetBytes(x.Substring(0,1).ToUpper().ToCharArray());
            Console.WriteLine(String.Format("{0} {1}",x,encoded[0]));
            encoded = a_encoding.GetBytes(y.Substring(0,1).ToUpper().ToCharArray());
            Console.WriteLine(String.Format("{0} {1}",y,encoded[0]));
            encoded = a_encoding.GetBytes(z.Substring(0,1).ToUpper().ToCharArray());
            Console.WriteLine(String.Format("{0} {1}",z,encoded[0]));
        }
    }
}
