using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArySplitTest
{
    class Program
    {
        static void Main(string[] args)
        {
            const int MAX_BINARY_IMAGE = 255;

            List<byte []> split_up_ary = new List<byte[]>();

            byte [] aryToAdd = new byte [511];
            for(int currByte = 0;
                currByte < aryToAdd.Length;
                currByte++)
            {
                aryToAdd[currByte] = (byte) currByte;
            }

            int ary_len = aryToAdd.Length;
            int ary_offset = 0;
            while(ary_len > 0)
            {
                byte [] sub_image = null;
                if(ary_len > MAX_BINARY_IMAGE)
                {
                    sub_image = new byte [MAX_BINARY_IMAGE];
                }
                else
                {
                    sub_image = new byte [ary_len];
                }
                Array.ConstrainedCopy(aryToAdd ,    ary_offset,
                                      sub_image,    0,
                                      sub_image.Length);
#if false
                TreeMultiNode<TagParsingContext> aryNode =
                    new TreeMultiNode<TagParsingContext>(
                        m_director.GetParsingContext(ElementTypes.PREFIX,
                                                 0) );
                aryNode.Val.ByteAryVal = sub_image;
                parentNode.AddNode(aryNode);
#else
                split_up_ary.Add(sub_image);
#endif
                ary_len      -= MAX_BINARY_IMAGE;
                ary_offset   += MAX_BINARY_IMAGE;
            }
            foreach(byte [] img in split_up_ary)
            {
                Console.WriteLine(DumpAry(img));
            }
        }
        public static string DumpAry(byte [] ary)
        {
            StringBuilder mainImg = new StringBuilder();
            StringBuilder sb_hex = new StringBuilder();
            StringBuilder sb_char = new StringBuilder();
            uint line_byte_cnt = 0;
            uint line_addr = 0;
            const int LINE_BYTE_CNT = 32;

            // leadin byte.

            for (int curr_byte = 0; curr_byte < ary.Length; curr_byte++)
            {
                sb_hex.AppendFormat("{0:X2} ",ary[curr_byte]);

                if (   Char.IsLetter(     (char)(ary[curr_byte]))
                    || Char.IsNumber(     (char)(ary[curr_byte]))
                    || Char.IsPunctuation((char)(ary[curr_byte]))   )
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
