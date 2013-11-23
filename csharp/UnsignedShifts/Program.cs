using System;
using System.Collections.Generic;
using System.Text;

namespace UnsignedShifts
{
	class Program
	{
		static void Main(string[] args)
		{
			uint i = 0x40;
			i = i >> 1;
			Console.WriteLine(i);
		}
	}
}
