using System;
using System.Collections.Generic;
using System.Text;

namespace SnippetTest1
{
	class Program
	{
		static void Main(string[] args)
		{
			byte[] ba = new byte[20];
			ba[0] = 65;
			ba[1] = 66;
			ba[2] = 67;
			ba[3] = 0;
			


			System.Text.ASCIIEncoding enc = new System.Text.ASCIIEncoding();
			string str = enc.GetString(ba);
			Console.WriteLine(str);



		}
	}
}
