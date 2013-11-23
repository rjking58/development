using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_ROOT         : TagParsingContext
    {
        bool m_emitted = false;
        public TagParsingContext_ROOT(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.HOME,
                                TagNames.SNSTEST,
                                TagNames.PROFILES};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.ROOT);
        }
        public override string tagName()
        {
            return TagNames.ROOT;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::{0}::",TagNames.ROOT.ToUpper()));
#endif
                FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.ROOT]);
                // no data, so length 0..
                FileContext.Bw.Write((byte) 0);
                m_emitted = true;
            }
        }
        public override bool closeElementAction()
        {
            emit();
#if TRACE_EMIT            
            Console.WriteLine(String.Format("::/{0}::",TagNames.ROOT.ToUpper()));
#endif
            FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.ROOT] | END_TAG_FLAG));
            return true;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
