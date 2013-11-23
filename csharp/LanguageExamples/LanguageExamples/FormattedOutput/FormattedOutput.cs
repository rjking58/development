using System;

namespace FormattedOutput
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class FormattedDemo
	{
       
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
            Console.WriteLine("February has {0} or {1} days.", 28,29);
            Console.WriteLine("February has |{0,10}| or |{1,5}| days.", 28,29);    

            // tab formatted...
            Console.WriteLine("Value\t\tSquared\t\tCubed");
            for(long i = 1; i < 20; i++)
            {
                Console.WriteLine(  "{0}\t\t{1}\t\t{2}",
                                    i,
                                    i*i,
                                    i*i*i);
            }
            Console.WriteLine(  "number is:{0:###,###,###.##}",12345678.90);
            // 'C' in this line is explained in the 'NumberFormatInfo class'
            Console.WriteLine(  "number is:{0:C}",12345678.90);
            // hex output..
            Console.WriteLine(  "number is decimal: {0:D} or hexadecimal:{0:X}",255);
            Console.WriteLine(  "number is decimal: {0:D} or hexadecimal:{0:X}",0xFEFD);
        
		}
	}
}
