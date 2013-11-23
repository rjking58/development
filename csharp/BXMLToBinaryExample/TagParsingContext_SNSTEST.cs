using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_SNSTEST           : TagParsingContext
    {
        private bool    m_emitted = false;
        private bool    val_parsed = false;
        private string  m_val = "";

        public TagParsingContext_SNSTEST(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.MOREDEVICES_TOTEST,
                                TagNames.NEWDEVICE,
                                TagNames.DEVICE};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);
            if(trimmedOriginal.Length != 0)
            {
                val_parsed = true;
                m_val = trimmedOriginal;
            }
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.SNSTEST);
        }
        public override string tagName()
        {
            return TagNames.SNSTEST;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.SNSTEST.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {

#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1}]",TagNames.SNSTEST.ToUpper(),m_val));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.SNSTEST]);
                    // no data, so length 0..
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.ACTIVITY.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.SNSTEST.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.SNSTEST] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
            director.SetSNSName(m_val);
        }
    }
}
