using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ParserTest
{
    class Program
    {
        static void Main(string[] args)
        {
            string s1 = "/uri1/uri2/uri3,param1.f:val2.f:val3,param2.a:val4,param5,param3,f:zzz";
            string s2 = "/uri1/uri2/uri3,f:val2.f:val3.a:val4";
            string s3 = "/uri1/uri2/uri3";
            string s4 = "/uri1/uri2/uri3,param1";
            string s5 = "/uri1/uri2/uri3,f:xx";

            ParseCompoundSODAURI(s1);
            ParseCompoundSODAURI(s2);
            ParseCompoundSODAURI(s3);
            ParseCompoundSODAURI(s4);
            ParseCompoundSODAURI(s5);



        }

        static void ParseCompoundSODAURI(string compounduri)
        {
            Console.WriteLine("======================================================");
            Console.WriteLine("starting string[" + compounduri + "]");
            string [] uri_by_params = compounduri.Split(',');

            int currVal = 0;
            foreach(string part in uri_by_params)
            {
                if(currVal == 0)
                {
                    Console.WriteLine("uri[" + part + "]");
                    Console.WriteLine(" ");
                }
                else
                {
                    string [] parameters;
                    Console.WriteLine("......................................................");

                    parameters = part.Split('.');
                    foreach(string parameter in parameters)
                    {
                        string [] param_tokens = parameter.Split(':');
                        if(param_tokens.Length > 0)
                        {
                            if(param_tokens.Length == 1)
                            {
                                Console.WriteLine("parameter[" + param_tokens[0] + "]");
                            }
                            else if (param_tokens.Length == 2)
                            {
                                Console.WriteLine("type[" + param_tokens[0]  + "]" + " name[" + param_tokens[1] + "]");
                            }
                            else
                            {
                                Console.WriteLine("oops, bad parse for:" + parameter);
                            }
                        }
                    }
                }
                currVal++;
            }
        }
    }
}
