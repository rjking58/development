using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace String64ToString
{
    class Program
    {
        static void Main(string[] args)
        {
            byte [] converted = Convert.FromBase64String("/wEPDwULLTE3NDI1ODI3NjEPZBYCAgMPZBYEAgMPDxYEHgRUZXh0BQV4eHh4eR4LcGFsaW5kcm9tZXMygAIAAQAAAP////8BAAAAAAAAAAQBAAAAf1N5c3RlbS5Db2xsZWN0aW9ucy5HZW5lcmljLkxpc3RgMVtbU3lzdGVtLlN0cmluZywgbXNjb3JsaWIsIFZlcnNpb249Mi4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj1iNzdhNWM1NjE5MzRlMDg5XV0DAAAABl9pdGVtcwVfc2l6ZQhfdmVyc2lvbgYAAAgICQIAAAAFAAAABQAAABECAAAACAAAAAYDAAAABHh4eHgGBAAAAAR4eHh4BgUAAAAEeHh4eAYGAAAABHh4eHgGBwAAAAR4eHh4DQMLZGQCDQ8PFgQfAAUFeXl5eXofATL0AQABAAAA/////wEAAAAAAAAABAEAAAB/U3lzdGVtLkNvbGxlY3Rpb25zLkdlbmVyaWMuTGlzdGAxW1tTeXN0ZW0uU3RyaW5nLCBtc2NvcmxpYiwgVmVyc2lvbj0yLjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPWI3N2E1YzU2MTkzNGUwODldXQMAAAAGX2l0ZW1zBV9zaXplCF92ZXJzaW9uBgAACAgJAgAAAAQAAAAEAAAAEQIAAAAEAAAABgMAAAAEeXl5eQYEAAAABHl5eXkGBQAAAAR5eXl5BgYAAAAEeXl5eQtkZGQ3dp558qNvdYAlQIJ6fKWktt6CNQ==");
  
  
            
            ASCIIEncoding a_encoding = new ASCIIEncoding();
            string asAString = "";
            
            asAString = a_encoding.GetString( converted,
                                              0,
                                              converted.Length);
            
            Console.WriteLine(asAString);
        }
    }
}
