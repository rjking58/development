using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace DirsFilesPathsFileInfo
{
    class Program
    {
        static void Main(string[] args)
        {
            string fileName = @"C:\mydir.old\myfile.ext";
            string path = @"C:\mydir.old\";
            string extension;

            extension = Path.GetExtension(fileName);
            Console.WriteLine("GetExtension('{0}') returns '{1}'",
                fileName,extension);

            extension = Path.GetExtension(path);
            Console.WriteLine("GetExtension('{0}') returns '{1}'",
                path,extension);

        }
    }
}
