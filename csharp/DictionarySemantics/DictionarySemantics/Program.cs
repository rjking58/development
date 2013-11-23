using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DictionarySemantics
{
    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, int> my_d = new Dictionary<string, int>() ;

            my_d.Add("first", 1);
            my_d.Add("second", 2);
            my_d.Add("third", 3);

            my_d["first"] = 555;
            
            foreach(KeyValuePair<string,int> kvp in my_d)
            {
                Console.WriteLine("key[" + kvp.Key + "] value[" + kvp.Value + "]");
            }
        }
    }
}
