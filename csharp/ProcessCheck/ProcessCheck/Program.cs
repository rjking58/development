using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace ProcessCheck
{
    class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("{0}({1})",Process.GetCurrentProcess().ProcessName, Process.GetCurrentProcess().Id);
            if (Process.GetProcessesByName(Process.GetCurrentProcess().ProcessName).Length > 1)
            {
                Console.WriteLine("Already Running");
            }
            else
            {
                Console.WriteLine("First Copy");
            }
            Console.ReadLine();
        }
    }
}


//Function PrevInstance() As Boolean
//   If Ubound(Diagnostics.Process.GetProcessesByName(Diagnostics.Process.GetCurrentProcess.ProcessName)) > 0 Then
//      Return True
//   Else
//      Return False
//   End If
//End Function
