using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_EXECUTOR          : TagParsingContext
    {
        private bool    m_emitted = false;
        private ushort  m_val = 0;
        private bool    val_parsed = false;
        
        public TagParsingContext_EXECUTOR(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.OBJCODE};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);

            if(trimmedOriginal.Length == USHORT_STRLEN)
            {
                const int FIRST_BYTE_OFFSET = 0;
                const int SECOND_BYTE_OFFSET = 2;
                int high_order = 0;
                int low_order = 0;
                
                val_parsed = true;
                // assume its high order first (readable)
                high_order = parseByte(trimmedOriginal.Substring(FIRST_BYTE_OFFSET,BYTE_STRLEN));
                low_order =  parseByte(trimmedOriginal.Substring(SECOND_BYTE_OFFSET,BYTE_STRLEN));
                m_val = (ushort)((high_order << BYTESIZE_IN_BITS) | low_order);
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
            return tag.ToLower().Equals(TagNames.EXECUTOR);
        }
        public override string tagName()
        {
            return TagNames.EXECUTOR;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.EXECUTOR.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1:X4}]",TagNames.EXECUTOR.ToUpper(),m_val));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.EXECUTOR]);
                    emitUSHORT(FileContext.Bw,m_val);
                    
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.EXECUTOR.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.EXECUTOR.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.EXECUTOR] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
