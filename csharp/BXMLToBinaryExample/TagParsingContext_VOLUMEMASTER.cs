using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_VOLUMEMASTER      : TagParsingContext
    {
        private bool m_emitted = false;
        
        public TagParsingContext_VOLUMEMASTER(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
        }
        public override void parseValue(string val)
        {
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.VOLUMEMASTER);
        }
        public override string tagName()
        {
            return TagNames.VOLUMEMASTER;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::{0}::",TagNames.VOLUMEMASTER.ToUpper()));
#endif
                FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.VOLUMEMASTER]);
                // no data, so length 0..
                FileContext.Bw.Write((byte) 0);
                m_emitted = true;
            }
        }
        public override bool closeElementAction()
        {
            emit();
        
#if TRACE_EMIT            
            Console.WriteLine(String.Format("::/{0}::",TagNames.VOLUMEMASTER.ToUpper()));
#endif
            FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.VOLUMEMASTER] | END_TAG_FLAG));
            return true;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
