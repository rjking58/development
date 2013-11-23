using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace rmdirIfExists
{
	class Program
	{
		static void Main(string[] args)
		{
            for (int args_ofst = 0;
                args_ofst < args.Length;
                args_ofst++)
            {
                Console.WriteLine(String.Format("args[{0}][{1}]", args_ofst,args[args_ofst]));
            }

            if (args.Length >= 1)
            {
                // get the source list from the source directory
                DirectoryInfo source_dir = new DirectoryInfo(args[0]);
                if (source_dir.Exists)
                {
					source_dir.Delete(true);
                }
                else
                {
                    Console.WriteLine(String.Format("source directory[{0}] doesn't exist!", args[0]));
                }
            }
            else
            {
                Console.WriteLine("not enough arguments!!");
            }
		}
	}
}
