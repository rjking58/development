using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Microsoft.VisualBasic;

namespace fileio
{
    class Program
    {
        static void openErrDemo()
        {
            FileStream fin;

            try
            {
                fin = new FileStream("test.dat", FileMode.Open);
            }
            catch (FileNotFoundException exc)
            {
                Console.WriteLine(exc.Message);
                return;
            }
            catch
            {
                Console.WriteLine("Cannot open file!");
                return;
            }
        }

        static void fileDisplayDemo(string[] args)
        {
            int i;
            FileStream fin;

            try
            {
                fin = new FileStream(args[0], FileMode.Open, FileAccess.Read);
            }
            catch (FileNotFoundException exc)
            {
                Console.WriteLine(exc.Message);
                return;
            }
            catch (IndexOutOfRangeException exc)
            {
                Console.WriteLine(exc.Message + "\nUsage: fileio <file>");
                return;
            }
            do
            {
                try
                {
                    i = fin.ReadByte();
                }
                catch (Exception exc)
                {
                    Console.WriteLine(exc.Message);
                    return;
                }
                if (i != -1)
                {
                    Console.Write((char)i);
                }
            } while (i != -1);
            fin.Close();

        }

        // just for demo purposes.. this can be much more efficiently done using redirection
        // on the command line..
        static void fileReadAndWrite(string[] args)
        {
            int i;
            FileStream fin;
            FileStream fout;

            try
            {
                fin = new FileStream(args[0], FileMode.Open, FileAccess.Read);
            }
            catch (FileNotFoundException exc)
            {
                Console.WriteLine(exc.Message);
                return;
            }
            catch (IndexOutOfRangeException exc)
            {
                Console.WriteLine(exc.Message + "\nUsage: fileio <file>");
                return;
            }

            fout = new FileStream("output.dat", FileMode.Create, FileAccess.Write);
         
            // incredibly stupid way to do this.. but demonstrates...
            // 1. use of visual basic code in C#
            // 2. use of character enumerators based on strings

            // note that for this to work correctly 'Microsoft.VisualBasic' must be added to the references
            //   listed in the project.  If it isn't, it doesn't work at all.
            string now_str = Microsoft.VisualBasic.DateAndTime.Now.ToLongDateString();
            CharEnumerator now_str_enum = now_str.GetEnumerator();
            while(now_str_enum.MoveNext())
            {
                fout.WriteByte((byte) now_str_enum.Current);                
            }
            fout.WriteByte((byte)'\n');
            //fout.Write(
            do
            {
                try
                {
                    i = fin.ReadByte();
                }
                catch (Exception exc)
                {
                    Console.WriteLine(exc.Message);
                    return;
                }
                if (i != -1)
                {
                    fout.WriteByte((byte) i);
                }
            } while (i != -1);
            fin.Close();
            fout.Close();

        }


        static void Main(string[] args)
        {
            //openErrDemo();
            //fileDisplayDemo(args);
            fileReadAndWrite(args);

        }
    }
}
