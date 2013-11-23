using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

namespace FileIO
{
    class Program
    {
        static void Main(string[] args)
        {
            DirectoryInfo tmpxdir = new DirectoryInfo(@"C:\tempx");
            if (!tmpxdir.Exists)
            {
                tmpxdir.Create();
            }
            FileStream fs = new FileStream(@"c:\tempx\testoutput.txt", FileMode.Append);
            StreamWriter sw = new StreamWriter(fs);

            sw.WriteLine("weeee");
            sw.WriteLine("weee again!!!");
            sw.Flush();
            sw.Close();

        }
    }
}
