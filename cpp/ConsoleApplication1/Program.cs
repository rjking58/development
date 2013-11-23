using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;


namespace ConsoleApplication1
{
	// required, since the function pointer being passed 
	// will be used by unmanaged C++ code.. :)
	[UnmanagedFunctionPointerAttribute(CallingConvention.Cdecl)]
	delegate void myCB_delegate(int original,int result);

	// class to contain our external methods..
	// this is a straight up import class declaration of all exported
	// APIs in our imported class (also included in this solution
	static class ManagedCallbacks
	{
		// declaration of our extern methods..
		[DllImport(@"C:\GCS\Source\cpp\ManagedCallbacks\Debug\ManagedCallbacks.dll",
			       CallingConvention = CallingConvention.Cdecl)]
			public static extern void setCallback(myCB_delegate cb);
		[DllImport(@"C:\GCS\Source\cpp\ManagedCallbacks\Debug\ManagedCallbacks.dll",
			       CallingConvention = CallingConvention.Cdecl)]
			public static extern void AddTwo(int val);
	}


	// now the use of the DLL in managed context..
	class Program
	{
		// our delegate instance variable..
		static myCB_delegate m_myCB;

		static void Main(string[] args)
		{
			// initialize the delegate instance variable
			m_myCB = new myCB_delegate(Program.concreteCallback);

			// set it in the DLL for proper call backs..
			ManagedCallbacks.setCallback(m_myCB);

			// demonstrate that it works.
			for (int x = 0;
				x < 30;
				x++)
			{
				ManagedCallbacks.AddTwo(x);
			}
		}

		// our callback simply writes out the results and the original value..
		static void concreteCallback(int original,int result)
		{
			System.Console.WriteLine(original + "," + result);
		}

	}
}
