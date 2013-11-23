using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace SVNFilteredStatus
{
	class Program
	{
		static void Main(string[] args)
		{
			Process myProcess = new Process();

			Directory.SetCurrentDirectory(@"C:\Core");
			myProcess.StartInfo.UseShellExecute = false;
			myProcess.StartInfo.RedirectStandardOutput = true;
			myProcess.StartInfo.RedirectStandardError = true;
			myProcess.StartInfo.FileName = @"C:\Program Files\SlikSvn\bin\svn.exe";
			myProcess.StartInfo.Arguments = "status";
			myProcess.Start();

			while( ! myProcess.StandardOutput.EndOfStream)
			{
				string inputLine = myProcess.StandardOutput.ReadLine();
				if( ! Regex.IsMatch(inputLine, ".rking.user|.lib|.dll|.pdb|.obj|.ncb|.exe|([dD]ebug$)|(Obj$)"))
				{
					Console.WriteLine(inputLine);
				}

			}
		}
	}
}
