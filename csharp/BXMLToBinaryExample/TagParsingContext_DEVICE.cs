using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_DEVICE            : TagParsingContext
    {
        private bool    m_emitted = false;
        private bool    val_parsed = false;
        private IDAndName   m_id_and_name = null;

        public TagParsingContext_DEVICE(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.VOLUMEMASTER,
                                TagNames.VOLUMELOCK,
                                TagNames.USERLOCK,
                                TagNames.OEMLOCK,
                                TagNames.DEVICEID,
                                TagNames.BRAND,
                                TagNames.MODEL,
                                TagNames.ICONREF,
                                TagNames.CODESET,
                                TagNames.FAVORITES,
                                TagNames.FAVORITEWIDTH,
                                TagNames.ENTERKEY,
                                TagNames.LEARNEDKEY,
                                TagNames.SYNTHESIZERKEY};
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
            return tag.ToLower().Equals(TagNames.DEVICE);
        }
        public override string tagName()
        {
            return TagNames.DEVICE;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.DEVICE.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1},{2}]",
                                                    TagNames.DEVICE.ToUpper(),
                                                    m_id_and_name.ID,
                                                    m_id_and_name.Name));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.DEVICE]);
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.DEVICE.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.DEVICE.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.DEVICE] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
