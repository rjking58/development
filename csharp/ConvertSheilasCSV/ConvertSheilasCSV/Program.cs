using System;
using System.Collections.Generic;
using System.Text;
using System.IO;


namespace ConvertSheilasCSV
{
    class Program
    {
        static void Main(string[] args)
        {
            TextReader tr = new StreamReader(new FileStream(@"C:\Documents and Settings\rking\Desktop\SheilaPalmContacts.csv",FileMode.Open,FileAccess.Read));
            TextWriter tw = new StreamWriter(new FileStream(@"C:\Documents and Settings\rking\Desktop\SheilaPalmContactsCONVERTED.csv",FileMode.Create,FileAccess.Write));
            bool firstLine = true;
            string currLine = tr.ReadLine();
            string currentConstruction = "";
            while (currLine != null)
            {
                //Console.WriteLine(currLine);
                if ( ! firstLine)
                {
                    // last character a quote?
                    currentConstruction = currentConstruction + currLine;
                }
                else
                {
                    //tw.WriteLine(currLine);
                    currentConstruction = currLine;
                    firstLine = false;
                }
                if (currentConstruction.Length > 1)
                {
                    int lastChar = currentConstruction.Length - 2;
                    if (currentConstruction.Substring(lastChar, 2).Equals(@""""""))
                    {
                        //Console.WriteLine("found quote at end");
                        currentConstruction = currentConstruction.TrimStart();
                        tw.WriteLine(currentConstruction);
                        currentConstruction = "";
                    }
                }
                currLine = tr.ReadLine();
            }
            tw.Close();
            tr.Close();
        }
    }
}
