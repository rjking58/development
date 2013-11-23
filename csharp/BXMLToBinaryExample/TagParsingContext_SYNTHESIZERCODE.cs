using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_SYNTHESIZERCODE   : TagParsingContext
    {
        private bool    m_emitted = false;
        private uint    m_val = 0;
        private bool    val_parsed = false;
        
        public TagParsingContext_SYNTHESIZERCODE(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);

            if(trimmedOriginal.Length == (BYTE_STRLEN + BYTE_STRLEN + BYTE_STRLEN + BYTE_STRLEN))
            {
                const int FIRST_BYTE_OFFSET     = 0;
                const int SECOND_BYTE_OFFSET    = 2;
                const int THIRD_BYTE_OFFSET     = 4;
                const int FOURTH_BYTE_OFFSET    = 6;
                
                int first_byte  = 0;
                int second_byte = 0;
                int third_byte  = 0;
                int fourth_byte = 0;
                val_parsed = true;
                // assume its high order first (readable)
                first_byte  = parseByte(trimmedOriginal.Substring(FIRST_BYTE_OFFSET ,BYTE_STRLEN));
                second_byte = parseByte(trimmedOriginal.Substring(SECOND_BYTE_OFFSET,BYTE_STRLEN));
                third_byte  = parseByte(trimmedOriginal.Substring(THIRD_BYTE_OFFSET ,BYTE_STRLEN));
                fourth_byte = parseByte(trimmedOriginal.Substring(FOURTH_BYTE_OFFSET,BYTE_STRLEN));
                
                m_val = (uint)  (       (first_byte     << (BYTESIZE_IN_BITS * 3)   )
                                    |   (second_byte    << (BYTESIZE_IN_BITS * 2)   )
                                    |   (third_byte     << BYTESIZE_IN_BITS         )
                                    |   fourth_byte                                     )     ;
            }
            else
            {
                Console.Write("ERROR:  Line[");
                OnLinenumber();
                Console.WriteLine("]");
                Console.WriteLine(String.Format("expected length: [4] actual length: [{0}] parsed value: [{1}]",
                                                trimmedOriginal.Length,
                                                trimmedOriginal));
            }
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.SYNTHESIZERCODE);
        }
        public override string tagName()
        {
            return TagNames.SYNTHESIZERCODE;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
                if(! val_parsed)
                {
                    Console.Write("Line:"); 
                    base.OnLinenumber();
                    Console.WriteLine();
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.SYNTHESIZERCODE.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1:X8}]",TagNames.SYNTHESIZERCODE.ToUpper(),m_val));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.SYNTHESIZERCODE]);
                    emitUINT(FileContext.Bw,m_val);
                    
                    m_emitted = true;
                }
            }
        }
        public override bool closeElementAction()
        {
            if(! val_parsed)
            {
                Console.Write("Line:"); 
                base.OnLinenumber();
                Console.WriteLine();
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.SYNTHESIZERCODE.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.SYNTHESIZERCODE.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.SYNTHESIZERCODE] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
