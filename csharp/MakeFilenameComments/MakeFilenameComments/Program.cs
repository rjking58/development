using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MakeFilenameComments
{
    class Program
    {
        static void Main(string[] args)
        {
            // Get all filenames in the target folder..
            DirectoryInfo source_code_dir = new DirectoryInfo(@"c:\testing");

            List<FileInfo> source_files = new List<FileInfo>(source_code_dir.GetFiles("*.cpp"));
            source_files.AddRange(source_code_dir.GetFiles("*.h"));

            foreach(FileInfo fi in source_files)
            {
                if( ! fi.IsReadOnly)
                {
                    string fullName = fi.FullName;
                    StreamReader inp_file = new StreamReader(File.Open(fullName, FileMode.Open));
                    StreamWriter outp_file = new StreamWriter(File.Open(fullName + ".tmp", FileMode.Create));
                    string curr_line;
                    while ((curr_line = inp_file.ReadLine()) != null) 
                    {
                        int firstChar = curr_line.IndexOf(@"<this>");
                        if(firstChar >= 0)
                        {
                            curr_line = curr_line.Replace(@"<this>", fi.Name);
                        }
                        outp_file.WriteLine(curr_line);
                    }
                    inp_file.Close();
                    outp_file.Close();
                   
                    File.Delete(fullName);
                    File.Move(fullName + ".tmp", fullName);
                }
                Console.WriteLine(fi.FullName," complete..");
            }


            // for each, read all lines and replace the line found with the actual filename..


        }
    }
}
