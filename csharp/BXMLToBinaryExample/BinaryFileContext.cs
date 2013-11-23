using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace BXMLToBinaryExample
{
    class BinaryFileContext
    {
        // tags in this file.. I keep a dict for easy searching, and a list 
        // so that we have an ordered list of tags that have appeared in this file.
        private Dictionary<string, byte>    m_TagDict = new Dictionary<string, byte>();
        private List<string>                m_TagList = new List<string>();

        private MemoryStream                m_ms_binary_image = null;
        private BinaryWriter                m_bw = null;
        private string                      m_outputname = "";
        private int                         m_currTagNumber = 0;

        public string Outputname
        {
            get 
            { 
                return m_outputname; 
            }
            set 
            { 
                m_outputname = value; 
            }
        } 

        public BinaryWriter Bw
        {
            get 
            { 
                return m_bw; 
            }
        }

        public BinaryFileContext()
        {
            m_ms_binary_image = new MemoryStream();
            m_bw = new BinaryWriter(m_ms_binary_image);
        }

        public Dictionary<string, byte> TagDict
        {
            get 
            { 
                return m_TagDict; 
            }
        }

        public List<string> TagList
        {
            get 
            { 
                return m_TagList; 
            }
        }

        public void AddTag(string tagname)
        {
            if( ! m_TagDict.ContainsKey(tagname))
            {
                m_TagDict.Add(tagname,
                              (byte) m_currTagNumber);
                m_TagList.Add(tagname);
                m_currTagNumber++;
            }
        }

        public void outputToBinary()
        {
            ASCIIEncoding a_encoding = new ASCIIEncoding();
            m_bw.Close();
 
            // image of bxml.
            byte [] bxml_img = m_ms_binary_image.ToArray();

            // dictionary generation.                
            MemoryStream dictionary_mem = new MemoryStream();
            BinaryWriter dictionary_bw = new BinaryWriter(dictionary_mem);

            foreach(string tagname in m_TagList)
            {
                byte [] tagname_bytes = a_encoding.GetBytes(tagname);
            
                dictionary_bw.Write(tagname_bytes);
                dictionary_bw.Write((byte) 0);
            }

            dictionary_bw.Close();
            byte [] dictionary_img = dictionary_mem.ToArray();
            
            
            BinaryWriter bin_file = new BinaryWriter(new FileStream(m_outputname,FileMode.Create));
            //write out header
            byte [] headername_bytes = a_encoding.GetBytes("bxml10");
            
            bin_file.Write(headername_bytes);
            bin_file.Write((ushort) dictionary_img.Length);

            bin_file.Write((byte) m_TagList.Count);

            //write out dictionary
            bin_file.Write(dictionary_img);
            //write out image..
            bin_file.Write(bxml_img);
            bin_file.Close();
        }
    }
}
