using System;

namespace Literals
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class LiteralTest
	{
		static double m_dbl = 12.334455f;
		static decimal m_deci = 12.43m;
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			System.Console.WriteLine("m_dbl(" + m_dbl + ")");
			System.Console.WriteLine("m_deci(" + m_deci + ")");
			//
			// TODO: Add code to start application here
			//
		}
	}
}
