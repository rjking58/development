using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinqTest
{
    class Program
    {
        static void Main(string[] args)
        {

            CodeRefDataContext db = new CodeRefDataContext();

            var CodeCrossRefs = from z in db.CodeCrossRefs
                                select z;

            foreach (var r in CodeCrossRefs)
            {
                Console.WriteLine(r.CodeExample + " " + r.Description + " " + r.CodeExampleName);
            }
            
            int i = 1;
        }
    }
}
