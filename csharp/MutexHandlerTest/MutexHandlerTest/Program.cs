using System;
using System.Collections.Generic;
using System.Text;

using Manifest.Lib;
using System.Threading;

namespace MutexHandlerTest
{
    class Program
    {
        static MutexHandler mh1 = new MutexHandler(false,"abcd");        
        static void Main(string[] args)
        {
           if( mh1.Check() )
           {
                Thread.Sleep(20000);
           }
        }
    }
}
