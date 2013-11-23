using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_MACROPAIR         : TagParsingContext
    {
        private bool    m_emitted = false;
        private byte    m_val_deviceid = 0;
        private byte    m_val_scancode = 0;
        private bool    val_parsed = false;
        
        public TagParsingContext_MACROPAIR(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);

            if(trimmedOriginal.Length == (BYTE_STRLEN + BYTE_STRLEN))
            {
                val_parsed = true;
                // assume its high order first (readable)
                m_val_deviceid = parseByte(trimmedOriginal.Substring(0,2));
                m_val_scancode =  parseByte(trimmedOriginal.Substring(2,2));
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
            return tag.ToLower().Equals(TagNames.MACROPAIR);
        }
        public override string tagName()
        {
            return TagNames.MACROPAIR;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.MACROPAIR.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1:X2}][{2:X2}]",
                                                    TagNames.MACROPAIR.ToUpper(),
                                                    m_val_deviceid,
                                                    m_val_scancode));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.MACROPAIR]);
                    FileContext.Bw.Write((byte) 2); // size of contained data.
                    FileContext.Bw.Write((byte) m_val_deviceid);
                    FileContext.Bw.Write((byte) m_val_scancode);
                    
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.MACROPAIR.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.MACROPAIR.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.MACROPAIR] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
