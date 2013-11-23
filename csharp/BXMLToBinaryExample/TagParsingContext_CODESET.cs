using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_CODESET           : TagParsingContext
    {
        private bool    m_emitted = false;
        private bool    val_parsed = false;
        private string  m_val = "";
        
        public TagParsingContext_CODESET(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.EXECUTOR,
                                TagNames.PREFIX,
                                TagNames.KEYMAP};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);
            if(trimmedOriginal.Length == CODESETNAME_STRLEN)
            {
                val_parsed = true;
                m_val = trimmedOriginal;
            }
            else
            {
                Console.Write("ERROR:  Line[");
                OnLinenumber();
                Console.WriteLine("]");
                Console.WriteLine(String.Format("expected length: [5] actual length: [{0}] parsed value: [{1}]",
                                                trimmedOriginal.Length,
                                                trimmedOriginal));
            }
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.CODESET);
        }
        public override string tagName()
        {
            return TagNames.CODESET;
        }
        public override void emit()
        {
            if(!m_emitted)
            {
                if(! val_parsed)
                {
                    Console.Write("Line:"); 
                    base.OnLinenumber();
                    Console.WriteLine();
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.CODESET.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1}]",TagNames.CODESET.ToUpper(),m_val));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.CODESET]);
                    emitASCIIString(FileContext.Bw,m_val);
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.CODESET.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.CODESET.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.CODESET] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
