using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace StreamWriterDemo
{
    class Program
    {
        private const int LINE_BYTE_CNT = 16;
        
        static void Main(string[] args)
        {
            string str;
            FileStream fout;

            try
            {
                fout = new FileStream("test.txt",FileMode.Create);
            }
            catch (IOException exc)
            {
                Console.WriteLine(exc.Message + "Cannot Open File!");
                return;
            }
            StreamWriter fstr_out = new StreamWriter(fout);
            Console.WriteLine("Enter text ('stop' to quit).");
            do
            {
                Console.Write(":");
                str = Console.ReadLine();
                if (str.ToLower() != "stop")
                {
                    str = str + "\r\n";
                    try
                    {
                        fstr_out.Write(str);
                    }
                    catch(IOException exc)
                    {
                        Console.WriteLine(exc.Message + "File Error!");
                    }
                }
            }
            while (str.ToLower() != "stop");
            fstr_out.Close();
            
            // now do a memory stream..
            MemoryStream ms = new MemoryStream();
            StreamWriter sw = new StreamWriter(ms);
            Console.WriteLine("Enter text ('stop' to quit).");
            do
            {
                Console.Write(":");
                str = Console.ReadLine();
                if (str.ToLower() != "stop")
                {
                    str = str + "\r\n";
                    try
                    {
                        sw.Write(str);
                    }
                    catch(IOException exc)
                    {
                        Console.WriteLine(exc.Message + "File Error!");
                    }
                }
            }
            while (str.ToLower() != "stop");
            sw.Close();
            byte [] buff = ms.GetBuffer();
            Console.WriteLine(DumpAry(buff));
        }
        
        public static string DumpAry(byte [] ary)
        {
            StringBuilder mainImg = new StringBuilder();
            StringBuilder sb_hex = new StringBuilder();
            StringBuilder sb_char = new StringBuilder();
            uint line_byte_cnt = 0;
            uint line_addr = 0;

            // leadin byte.

            for (int curr_byte = 0; curr_byte < ary.Length; curr_byte++)
            {
                sb_hex.AppendFormat("{0:X2} ",ary[curr_byte]);

                if (   Char.IsLetter(     (char)(ary[curr_byte]))
                    || Char.IsNumber(     (char)(ary[curr_byte]))
                    || Char.IsPunctuation((char)(ary[curr_byte])) )
                {
                    sb_char.AppendFormat(" {0} ", (char)(ary[curr_byte]));
                }
                else
                {
                    sb_char.Append("   ");
                }
                line_byte_cnt++;
                if(line_byte_cnt >= LINE_BYTE_CNT)
                {
                    mainImg.Append(String.Format("{0:X4}:{1}\n", line_addr,sb_hex.ToString()));
                    mainImg.Append(String.Format("    :{1}\n", line_addr,sb_char.ToString()));
                    sb_hex.Remove(0,sb_hex.Length);
                    sb_char.Remove(0,sb_char.Length);
                    line_byte_cnt = 0;
                    line_addr += LINE_BYTE_CNT;
                }


            }
            if(line_byte_cnt>0)
            {
                mainImg.Append(String.Format("{0:X4}:{1}\n", line_addr,sb_hex.ToString()));
                mainImg.Append(String.Format("    :{1}\n", line_addr,sb_char.ToString()));
            }
            sb_hex = null;
            sb_char = null;



            return mainImg.ToString();
        }
        
        
    }
}
