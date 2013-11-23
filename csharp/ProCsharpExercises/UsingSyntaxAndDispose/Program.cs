using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UsingSyntaxAndDispose
{
    // this class implements the MS certified dispose/cleanup pattern.
    class X : IDisposable
    {
        public string name {get;set;}

        private bool disposed = false;

        public override string ToString()
        {
            return "X";
        }
        public X(string s_name)
        {
            name = s_name;
        }

        private void Cleanup(bool disposing)
        {
            if(! this.disposed)
            {
                if(disposing)
                {
                    // disposed managed (since we were called by Dispose.. its false in the Finalizer case..)
                    Console.WriteLine(name + "==>X::Cleanup of managed resources");
                }
                // Clean up UNmanaged here.. we ALWAYS do this..
                Console.WriteLine(name + "==>X::Cleanup of UNmanaged resources");
            }
            disposed = true;
        }
        ~X()
        {
            Console.WriteLine(name + "==>finalized..");
            Cleanup(false);
        }

        public void Dispose()
        {
            Console.WriteLine(name + "==>X::Dispose called..");

            Cleanup(true);
            // suppress calling of finalize since we used 'Dispose'
            GC.SuppressFinalize(this);
        }

    }
    class Program
    {
        static void Main(string[] args)
        {

            // shorthand to guarantee calling 'Dispose'
            using(X an_x = new X("inside_using"))
            {
                Console.WriteLine(an_x.ToString());
            }
            Console.WriteLine("outside 'using'");

            Console.WriteLine("NOT calling Dispose..");
            X another_X = new X("uncalled_dispose");
            another_X = null;

            Console.WriteLine("calling Dispose..");
            another_X = new X("called_dispose");
            another_X.Dispose();
            another_X = null;

            GC.Collect();

            Console.ReadLine();
        }
    }
}
