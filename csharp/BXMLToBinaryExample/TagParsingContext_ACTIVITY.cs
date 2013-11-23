using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_ACTIVITY          : TagParsingContext
    {
        private bool    m_emitted = false;
        private bool    val_parsed = false;
        private IDAndName   m_id_and_name = null;

        public TagParsingContext_ACTIVITY(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.ICONREF,
                                TagNames.MACRO,
                                TagNames.PUNCHTHRUMAP};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            m_id_and_name = parseIDAndName(val);
            val_parsed = true;
        }
        public override bool isTag(string tag)
        {
            return tag.ToLower().Equals(TagNames.ACTIVITY);
        }
        public override string tagName()
        {
            return TagNames.ACTIVITY;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.ACTIVITY.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                
                    Console.WriteLine(String.Format("::{0}::[{1},{2}]",
                                                    TagNames.ACTIVITY.ToUpper(),
                                                    m_id_and_name.ID,
                                                    m_id_and_name.Name));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.ACTIVITY]);
                    emitIDAndName(FileContext.Bw,m_id_and_name);

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
                Console.WriteLine(String.Format("::/{0}::",TagNames.ACTIVITY.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.ACTIVITY] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
