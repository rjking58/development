using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_HOME         : TagParsingContext
    {
        bool m_emitted = false;
        public TagParsingContext_HOME(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.DEVICES,
                                TagNames.ACTIVITIES,
                                TagNames.PROFILES,
                                TagNames.FAVORITES};
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
            return tag.ToLower().Equals(TagNames.HOME);
        }
        public override string tagName()
        {
            return TagNames.HOME;
        }
        public override void emit()
        {
            if( ! m_emitted)
            {
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::{0}::",TagNames.HOME.ToUpper()));
#endif
                FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.HOME]);
                // no data, so length 0..
                FileContext.Bw.Write((byte) 0);
                m_emitted = true;
            }
        }
        public override bool closeElementAction()
        {
            emit();
#if TRACE_EMIT            
            Console.WriteLine(String.Format("::/{0}::",TagNames.HOME.ToUpper()));
#endif
            FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.HOME] | END_TAG_FLAG));
            return true;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
