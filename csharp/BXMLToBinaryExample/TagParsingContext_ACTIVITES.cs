using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_ACTIVITIES        : TagParsingContext
    {
        private bool    m_emitted = false;
        private bool    val_parsed = false;
        private string  m_val = "";
        
        public TagParsingContext_ACTIVITIES(BinaryFileContext FileContext,int linenumber) : base(FileContext,linenumber)
        {
            string[] taglist = {TagNames.ACTIVITY};
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
            return tag.ToLower().Equals(TagNames.ACTIVITIES);
        }
        public override string tagName()
        {
            return TagNames.ACTIVITIES;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.ACTIVITIES.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1}]",TagNames.ACTIVITIES.ToUpper(),m_val));
#endif                
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.ACTIVITIES]);
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.ACTIVITIES.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.ACTIVITIES.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.ACTIVITIES] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
            director.SetActivitiesName(m_val);
        }
    }
}
