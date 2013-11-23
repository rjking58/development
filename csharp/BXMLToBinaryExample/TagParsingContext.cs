using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Globalization;

namespace BXMLToBinaryExample
{
    abstract class TagParsingContext
    {
        private int                         m_linenumber = 0;
        private Dictionary<string, string>  m_Legaltags = new Dictionary<string, string>();
        private BinaryFileContext           m_FileContext = null;


        protected const int                 MAX_OBJCODE_BYTES       = 255 ;
        protected const int                 MAX_OBJCODE_CHARACTERS  = MAX_OBJCODE_BYTES * 2 ;
        protected const byte                END_TAG_FLAG            = 0x80;
        protected const int                 CODESETNAME_STRLEN      = 5;
        protected const int                 UINT_SIZE               = 4;
        protected const int                 USHORT_SIZE             = 2;
        protected const int                 USHORT_STRLEN           = 4;
        protected const int                 BYTE_STRLEN             = 2;
        protected const int                 BYTESIZE_IN_BITS        = 8;
        protected const int                 BYTE_MASK               = 0xFF;
        
        protected BinaryFileContext FileContext
        {
            get 
            { 
                return m_FileContext; 
            }
        }

        protected Dictionary<string, string> Legaltags
        {
            get 
            { 
                return m_Legaltags; 
            }
        }
        public void AddTagNameToFileContext()
        {
            m_FileContext.AddTag(this.tagName());
        }

        public TagParsingContext(BinaryFileContext FileContext, int linenumber)
        {
            m_FileContext = FileContext;
            m_linenumber = linenumber;
        }

        public bool IsLegal(string tag)
        {
            string lowcaseTag = tag.ToLower();

            return m_Legaltags.ContainsKey(lowcaseTag);
        }

        protected IDAndName parseIDAndName(string original)
        {
            string trimmedOriginal = original.TrimStart(null).TrimEnd(null);
            string namePortion = "";
            string IDPortion = "";
            byte   ID;
            if(trimmedOriginal.Length < (BYTE_STRLEN + 1))
            {
                // not a byte specification..
                Console.WriteLine("entry is not the proper length for an IDAndName structure");
                Console.WriteLine("this entry [{0}] has length [{1}]",trimmedOriginal,trimmedOriginal.Length);
                throw new GeneralParsingException();
            }
            // ok, we got this far, separate into the byte and the string, and parse accordingly.
            IDPortion = trimmedOriginal.Substring(0,2);
            namePortion = trimmedOriginal.Substring(2,trimmedOriginal.Length - 2);

            ID = parseByte(IDPortion);
            return new IDAndName(ID,namePortion);
        }

        protected byte parseByte(string original)
        {
            //BadByteException();
            byte retVal = 0;
            string trimmedOriginal = original.TrimStart(null).TrimEnd(null);
            if(trimmedOriginal.Length != BYTE_STRLEN)
            {
                // not a byte specification..
                Console.WriteLine("entry is not the proper length for a byte (2)");
                Console.WriteLine("this entry [{0}] has length [{1}]",trimmedOriginal,trimmedOriginal.Length);
                throw new GeneralParsingException();
            }
            try
            {
                retVal = Byte.Parse( trimmedOriginal,NumberStyles.HexNumber);
            }
            catch(ArgumentNullException)
            {
                Console.WriteLine("Argument was null!!");
                throw new GeneralParsingException();
            }
            catch(FormatException)
            {
                Console.WriteLine(String.Format("hexadecimal byte expected: [{0}]",trimmedOriginal));
                throw new GeneralParsingException();
            }
            catch(OverflowException)
            {
                Console.WriteLine(String.Format("hexadecimal byte expected: [{0}]",trimmedOriginal));
                throw new GeneralParsingException();
            }
            catch(ArgumentException)
            {
                Console.WriteLine(String.Format("hexadecimal byte expected: [{0}]",trimmedOriginal));
                throw new GeneralParsingException();
            }
            return retVal;
        }
        
        protected byte [] parseByteStream(string val,
                                          string tagname)
        {
            byte [] byteStream = null;
            
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);
            if((trimmedOriginal.Length & 1) == 1)
            {
                // odd number of characters.. BAD (each byte must be two characters).
                Console.Write("ERROR:  Line[");
                OnLinenumber();
                Console.WriteLine("]");
                Console.WriteLine(String.Format("An odd number of characters detected for {0}.. each byte is two characters long, so length of value should be even!"),
                                                tagname);
                
            }
            else if (trimmedOriginal.Length > MAX_OBJCODE_CHARACTERS)
            {
                // bad.. we are above the max allowable in one stream
                Console.Write("ERROR:  Line[");
                OnLinenumber();
                Console.WriteLine("]");
                Console.WriteLine(String.Format("Greater than max allowable byte detected for {0}! Max[{1}]  Detected[{2}]",
                                                tagname,
                                                MAX_OBJCODE_CHARACTERS,
                                                trimmedOriginal.Length));
            }
            else
            {
                // assume its high order first (readable)
                byteStream = new byte[trimmedOriginal.Length/BYTE_STRLEN];

                for(int currByte = 0;
                    currByte < trimmedOriginal.Length;
                    currByte += BYTE_STRLEN)
                {
                    byteStream[currByte/BYTE_STRLEN] = parseByte(trimmedOriginal.Substring(currByte,BYTE_STRLEN));
                }
            }
            return byteStream;
        }        
        protected void emitByteStream(byte []                   m_val,
                                      BinaryWriter              bw)
        {

            if(m_val != null)
            {
                int maxOnLine = 16;
                int currCharOut = 0;

                // length of array portion..
                bw.Write((byte) m_val.Length);

                for(int currByte = 0;
                    currByte < m_val.Length;
                    currByte++)
                {
#if TRACE_EMIT            
                    Console.Write(String.Format("{0:X2} ",m_val[currByte]));
#endif
                    bw.Write((byte) m_val[currByte]);
                    currCharOut++;
                    if(currCharOut >= maxOnLine)
                    {
#if TRACE_EMIT            
                        Console.WriteLine();
#endif
                        currCharOut = 0;
                    }
                }
                // if its 0, we just did a writeline, so don't do another! :)
                if(currCharOut != 0)
                {
#if TRACE_EMIT            
                    Console.WriteLine();
#endif
                }
            }
        }
        
        public void emitIDAndName(BinaryWriter bw,IDAndName val)
        {
            UnicodeEncoding uc_encoding = new UnicodeEncoding();
            byte [] uc_encoded_val = uc_encoding.GetBytes(val.Name);

            // the length of the string + the byte for the ID
            bw.Write((byte) (uc_encoded_val.Length + 1));
            // the ID
            bw.Write(val.ID);
            // the string.
            bw.Write(uc_encoded_val);
        }

        public void emitUnicodeString(BinaryWriter bw,string val)
        {

            UnicodeEncoding uc_encoding = new UnicodeEncoding();
            byte [] uc_encoded_val = uc_encoding.GetBytes(val);

            // the length.
            bw.Write((byte) uc_encoded_val.Length);
            // the string.
            bw.Write(uc_encoded_val);
        }
        
        public void emitASCIIString(BinaryWriter bw,string val)
        {

            ASCIIEncoding a_encoding = new ASCIIEncoding();
            byte [] a_encoded_val = a_encoding.GetBytes(val);

            // the length.
            bw.Write((byte) a_encoded_val.Length);
            // the string.
            bw.Write(a_encoded_val);
        }

        public void emitUSHORT(BinaryWriter bw,ushort val)
        {
            bw.Write((byte) USHORT_SIZE); 

            // store our word Little Endian.
            bw.Write(val);
        }

        public void emitUINT(BinaryWriter bw,uint val)
        {
            bw.Write((byte) UINT_SIZE); 

            // store our word Little Endian.
            bw.Write(val);
        }
        
        public void OnLinenumber()
        {
            Console.Write(m_linenumber);
        }
        abstract public void        parseValue(string val);
        abstract public bool        isTag(string tag);
        abstract public string      tagName();
        abstract public void        emit();
        abstract public bool        closeElementAction();
        abstract public void        setOutputName(TagParsingDirector director);
    }
}
