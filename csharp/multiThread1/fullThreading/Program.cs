using System.Threading;
using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Text;

namespace fullThreading
{
    class Printer
    {
		public void PrintNumbers()
		{
			// Display Thread Info.
			Console.WriteLine("-> {0} is executing PrintNumbers",
								Thread.CurrentThread.Name);

			//print em
			Console.Write("Your numbers: ");
			for (int i = 0; i < 10; i++)
			{
				Console.Write(i + ", ");
				Thread.Sleep(2000);
			}
			Console.WriteLine();
		}

    }
    class Program
    {
        static void Main(string[] args)
        {
			Console.WriteLine("**thread app**");
			Console.Write("Do you want [1] or [2] threads? ");
			string threadCount = Console.ReadLine();

			Thread primaryThread = Thread.CurrentThread;
			primaryThread.Name = "Primary";

			Console.WriteLine("-> {0} is executing in Main()",
							  Thread.CurrentThread.Name);

			Printer p = new Printer();

			switch (threadCount)
			{
			case "2" :
				Thread backgroundThread = 
					new Thread(new ThreadStart(p.PrintNumbers));
				backgroundThread.Name = "Secondary";
				backgroundThread.Start();
				break;
			case "1" :
				p.PrintNumbers();
				break;
			default :
				Console.WriteLine("oops.. not valid input for # of threads.. assume 1");
				goto case "1";

			}
			// additional work for fun.
			MessageBox.Show("I'm busy!", "Work on main thread...");
			Console.ReadLine();

//            Console.WriteLine("***Primary Thread Stats ****\n");
//            
//            //Obtain and name current thread..
//            Thread primaryThread = Thread.CurrentThread;
//            primaryThread.Name = "ThePrimaryThread";
//
//            Console.WriteLine("Name of  current AppDomain: {0}",
//                                Thread.GetDomain().FriendlyName);
//            Console.WriteLine("ID of current Context: {0}",
//                                Thread.CurrentContext.ContextID);
//
//            Console.WriteLine("Thread Name: {0}",
//                                primaryThread.Name);
//            Console.WriteLine("Has thread started?: {0}",
//                                primaryThread.IsAlive);
//            Console.WriteLine("Priority Level: {0}",
//                                primaryThread.Priority);
//            Console.WriteLine("Thread state: {0}",
//                                primaryThread.ThreadState);
//            Console.ReadLine();            
//                                
        }
    }
}
