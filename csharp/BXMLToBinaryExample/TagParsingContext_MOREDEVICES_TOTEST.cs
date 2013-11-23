using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_MOREDEVICES_TOTEST : TagParsingContext
    {
        bool m_emitted = false;
        
        public TagParsingContext_MOREDEVICES_TOTEST(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
        }
        public override void parseValue(string val)
        {
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.MOREDEVICES_TOTEST);
        }
        public override string tagName()
        {
            return TagNames.MOREDEVICES_TOTEST;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::{0}::",TagNames.MOREDEVICES_TOTEST.ToUpper()));
#endif
                FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.MOREDEVICES_TOTEST]);
                // no data, so length 0..
                FileContext.Bw.Write((byte) 0);
                m_emitted = true;
            }
        }
        public override bool closeElementAction()
        {
            emit();
#if TRACE_EMIT            
            Console.WriteLine(String.Format("::/{0}::",TagNames.MOREDEVICES_TOTEST.ToUpper()));
#endif
            FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.MOREDEVICES_TOTEST] | END_TAG_FLAG));
            return true;
        }
        
        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
