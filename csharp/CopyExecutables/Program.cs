using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CopyExecutables
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

            if (args.Length >= 2)
            {
                // get the source list from the source directory
                DirectoryInfo source_dir = new DirectoryInfo(args[0]);
                DirectoryInfo target_dir = new DirectoryInfo(args[1]);
                if (source_dir.Exists)
                {
                    if (target_dir.Exists)
                    {
                        List<FileInfo> source_files = new List<FileInfo>(source_dir.GetFiles("*.exe"));
                        source_files.AddRange(source_dir.GetFiles("*.dll"));
                        foreach (FileInfo source_file in source_files)
                        {
                            // check if it exists in target, and report if its readonly or not..
                            String full_target_name = args[1] + @"\\" + source_file.Name;
                            FileInfo target_file = new FileInfo(full_target_name);
                            if (target_file.Exists)
                            {
                                if (target_file.IsReadOnly)
                                {
                                    Console.WriteLine(String.Format("{0} is read only", target_file.FullName));
                                }
                                else
                                {
                                    Console.WriteLine(String.Format("copy to.. {0}", target_file.FullName));
//                                    source_file.CopyTo(target_file.FullName, true); 
                                }
                            }
                        }
                    }
                    else
                    {
                        Console.WriteLine(String.Format("target directory[{0}] doesn't exist!", args[1]));
                    }
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
