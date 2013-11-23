using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EncodingUsage
{
    class Program
    {
        static void Main(string[] args)
        {
            String mystr = "1234";

            Encoding unicode = Encoding.Unicode;

            byte [] asBytes = unicode.GetBytes(mystr);

            byte[] nullTermedAsBytes = new byte[asBytes.Length + 2];
            nullTermedAsBytes.Initialize();
            asBytes.CopyTo(nullTermedAsBytes, 0);
        }
    }
}
