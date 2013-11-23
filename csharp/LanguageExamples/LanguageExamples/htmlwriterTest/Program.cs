using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Web.UI;


namespace htmlwriterTest
{
    class Program
    {
        static void Main(string[] args)
        {
            MemoryStream ms = new MemoryStream();
            StreamWriter sw = new StreamWriter(ms);
            HtmlTextWriter htw = new HtmlTextWriter(sw);

            htw.RenderBeginTag(HtmlTextWriterTag.H1);
            htw.RenderEndTag();
            htw.Flush();
            long ms_len = ms.Length;
            Console.WriteLine("ms.Length(" + ms_len + ")");
            byte[] buff = ms.GetBuffer();
            
            for (long i = 0; i < ms_len; i++)
            {
                Console.Write((char)(buff[i]));
            }
        }
    }
}
