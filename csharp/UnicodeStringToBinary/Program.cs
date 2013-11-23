using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace UnicodeStringToBinary
{
    class Program
    {
        static void Main(string[] args)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);
        
            string mystr = "xxyyzz";
            UnicodeEncoding uc_encoding = new UnicodeEncoding();
            byte [] uc_encoded_mystr = uc_encoding.GetBytes(mystr);
            
            bw.Write(uc_encoded_mystr);
            bw.Close();
            
            byte [] tst_output = ms.ToArray();
            
            
        }
    }
}
