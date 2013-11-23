using System;
using System.Collections.Generic;
using System.Text;

namespace SimpleDisassemblyTest
{
    class Program
    {
        static void Main(string[] args)
        {
            uint ui = 128;
            uint x = 33+44;
            ui = ui << 1;
            ui = ui*2;
            ui = ui + x;
        }
    }
}
