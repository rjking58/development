using System;
using System.Collections.Generic;
using System.Text;
using System.Configuration;
using System.IO;
using System.Runtime.InteropServices;

namespace SMManagerMock
{
	public class TestXMLs
	{

		public static byte [] GetNetworkDeviceState()
		{
			string data = null;

			using (StringReader reader = new StringReader(XMLs.NetworkDeviceState))
			{
				data = reader.ReadToEnd();
			}

			System.Text.ASCIIEncoding  encoding=new System.Text.ASCIIEncoding();
			return encoding.GetBytes(data);
		}
	}
}
