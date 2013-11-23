using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace fullThreadingParameterized
{
	class AddParams
	{
		public int a;
		public int b;

		public AddParams(int numb1, int numb2)
		{
			a = numb1;
			b = numb2;
		}
	}
    class Program
    {
        static void PrintNums()
		{
			Console.WriteLine("ID of thread in PrintNums(): {0}",
							  Thread.CurrentThread.GetHashCode());
			for (int i = 1; i < 11; i++)
			{
				Console.WriteLine("{0}, ",
								  i);
                Thread.Sleep(500);
			}
		}
       
		static void Add(object data)
		{
			if (data is AddParams)
			{
				Console.WriteLine("ID of thread in Add(): {0}",
								  Thread.CurrentThread.GetHashCode());

				AddParams ap = (AddParams)data;
				Console.WriteLine("{0} + {1} is {2}",
								  ap.a,
								  ap.b,
								  ap.a + ap.b);
			}
		}
        static void Main(string[] args)
        {
			Console.WriteLine("*** Adding with Thread Objs.***");
			Console.WriteLine("ID of thread in Main(): {0}",
							  Thread.CurrentThread.GetHashCode());
			AddParams ap = new AddParams(10,20);
			Thread t1 = new Thread(new ThreadStart(PrintNums));
			t1.Start();
			Thread t2 = new Thread(new ParameterizedThreadStart(Add));
			t2.Start(ap);

			Console.WriteLine("stuff after thread start...");
			Console.WriteLine("more stuff after thread start...");
			Console.WriteLine("more more stuff after thread start...");
        }
    }
}
