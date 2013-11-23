using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExportedTypes
{
    public class TypeOfInterest
    {
        public int x;
        public int y;
        public void IAm()
        {
            Console.WriteLine("V2");
            Console.WriteLine(s);
        }

        bool b;
        string s = "woohoo";
    }

    public class TypeNotOfInterest
    {
        public string s = "woohoo";
    }
}
