using System;
using System.Collections.Generic;
using System.Text;

using System.Collections;
using System.IO;

namespace LineCount
{

    public class DBLineCount
    {
        private int m_TotalLines;
        public class FileLCStats
        {
            public string   filename;
            public int      line_count;
            /// <summary>
            ///  constructor
            /// </summary>
            /// <param name="fname"> file name</param>
            /// <param name="lc"> line count</param>
            public FileLCStats(string fname,int lc)
            {
                filename = fname;
                line_count = lc;
            }
        }
        //FileNames holds the names of files in the project directories
        private List<FileLCStats> FileStats = new List<FileLCStats>();
        
        public DBLineCount()
        {
            m_TotalLines = GetLineCount();
        }
        /// it returns filenames in the project
        /// </summary>
        public List<FileLCStats> FilesInProject
        {
            get
            {
                return FileStats;
            }
        }
        public int TotalLines
        {
            get
            {
                return m_TotalLines;
            }
        }
        
        /// <summary>
        /// this function returns the count of code lines
        /// </summary>
        /// <returns></returns>
        public int GetLineCount()
        {
            int LineCount = 0;
            // this array holds file types, you can add more file types if you want
            //String[] myFileArray = new String[7] { "*.cs","*.aspx","*.ascx","*.xml","*.asax","*.config","*.js" };

            //String[] myFileArray      =  { "*.cs" };            // this array holds directories where your project files resides
            //String[] myDirectoryArray =  { @"C:\src\Products\EzWebApp\Libraries\EzDvcEditCore",
            //                               @"C:\src\Products\EzWebApp\Libraries\EzDvcEditCore\UnitTests"      };
            //String[] myFileArray      =  { "*.c","*.h" };            // this array holds directories where your project files resides
            //String[] myDirectoryArray =  { @"C:\src\Products\Crystalis\DenonRemote\Source\AppBrdSupport",
            //                               @"C:\src\Products\Crystalis\DenonRemote\Source\Application",
            //                               @"C:\src\Products\Crystalis\DenonRemote\Source\Bootloader"      };
            //this loops directories
            String[] myFileArray      =  { "*.cpp", "*.h" };            // this array holds directories where your project files resides
            String[] myDirectoryArray =  { @"U:\SysObjectDev\src\FsEngine" };
            foreach (String sd in myDirectoryArray)
            {
                int DirLineCount = 0;
                DirectoryInfo dir = new DirectoryInfo(sd);
                // this loops file types
                foreach (String sFileType in myFileArray)
                {

                    // this loops files
                    foreach (FileInfo file in dir.GetFiles(sFileType))
                    {
                        int FileLineCount = 0;
                        // add the file name to FileNames ArrayList
                        // open files for streamreader
                        StreamReader sr = File.OpenText(file.FullName);
                        //loop until the end
                        while (sr.ReadLine() != null)
                        {
                            LineCount++;
                            FileLineCount++;
                            DirLineCount++;
                        }
                        //close the streamreader
                        sr.Close();
                        FileStats.Add(new FileLCStats(file.Name,FileLineCount));
                    }
                }

                FileStats.Add(new FileLCStats(" ",0));
                FileStats.Add(new FileLCStats(":::SUBTOTAL:::",DirLineCount));
                FileStats.Add(new FileLCStats(" ",0));                

                DirLineCount = 0;
            }
            return LineCount;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            DBLineCount db_lc = new DBLineCount();
            foreach (DBLineCount.FileLCStats stat in db_lc.FilesInProject)
            {
                if (stat.line_count > 0)
                {
                    Console.WriteLine(stat.filename + "  :" + stat.line_count);                
                }
                else
                {
                    Console.WriteLine();
                }
            }

            Console.WriteLine();
            Console.WriteLine("Total::::" + db_lc.TotalLines);
            
        }
    }
}
