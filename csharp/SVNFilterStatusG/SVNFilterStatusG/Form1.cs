using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace SVNFilterStatusG
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Process myProcess = new Process();

			Directory.SetCurrentDirectory(@"C:\Core");
			myProcess.StartInfo.UseShellExecute = false;
			myProcess.StartInfo.RedirectStandardOutput = true;
			myProcess.StartInfo.RedirectStandardError = true;
			myProcess.StartInfo.CreateNoWindow = true;
			myProcess.StartInfo.FileName = @"C:\Program Files\SlikSvn\bin\svn.exe";
			myProcess.StartInfo.Arguments = "status";
			myProcess.Start();

			txt_Output.Clear();
			StringBuilder sb = new StringBuilder();
			while( ! myProcess.StandardOutput.EndOfStream)
			{
				string inputLine = myProcess.StandardOutput.ReadLine();
				if( ! Regex.IsMatch(inputLine, ".rking.user|.lib|.dll|.pdb|.obj|.ncb|.exe|([dD]ebug$)|(Obj$)"))
				{
					sb.Append(inputLine + "\r\n");
					//Console.WriteLine(inputLine);
				}
			}
			txt_Output.Text = sb.ToString();
		}
	}
}