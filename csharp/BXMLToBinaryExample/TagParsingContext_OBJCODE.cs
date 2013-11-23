using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_OBJCODE           : TagParsingContext
    {
        private bool    m_emitted = false;
        private byte[]  m_val = null;
        private bool    val_parsed = false;
        
        public TagParsingContext_OBJCODE(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
        }
        public override void parseValue(string val)
        {
        
            m_val = parseByteStream(val,TagNames.OBJCODE.ToUpper());
            if(m_val != null)
            {
                val_parsed = true;
            }
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.OBJCODE);
        }
        public override string tagName()
        {
            return TagNames.OBJCODE;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.OBJCODE.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::",TagNames.OBJCODE.ToUpper()));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.OBJCODE]);
                    emitByteStream(m_val,FileContext.Bw);
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.OBJCODE.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.OBJCODE.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.OBJCODE] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
