using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_PUNCHTHRUSPEC     : TagParsingContext
    {
        private bool    m_emitted = false;
        private ushort  m_val_deviceid = 0;
        private ushort  m_val_devscancode = 0;
        private ushort  m_val_newscancode = 0;
        
        private bool    val_parsed = false;
        public TagParsingContext_PUNCHTHRUSPEC(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.NAME8,
                                TagNames.ICONREF};
            foreach (string tag in taglist)
            {
                Legaltags.Add(tag,tag);
            }
        }
        public override void parseValue(string val)
        {
            string trimmedOriginal = val.TrimStart(null).TrimEnd(null);
            const int FIRST_BYTE_OFFSET     = 0;
            const int SECOND_BYTE_OFFSET    = 2;
            const int THIRD_BYTE_OFFSET     = 4;
            

            if(trimmedOriginal.Length == (BYTE_STRLEN + BYTE_STRLEN + BYTE_STRLEN))
            {
                val_parsed = true;
                m_val_deviceid      = parseByte(trimmedOriginal.Substring(FIRST_BYTE_OFFSET ,BYTE_STRLEN));
                m_val_devscancode   = parseByte(trimmedOriginal.Substring(SECOND_BYTE_OFFSET,BYTE_STRLEN));
                m_val_newscancode   = parseByte(trimmedOriginal.Substring(THIRD_BYTE_OFFSET ,BYTE_STRLEN));
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
            return tag.ToLower().Equals(TagNames.PUNCHTHRUSPEC);
        }
        public override string tagName()
        {
            return TagNames.PUNCHTHRUSPEC;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.PUNCHTHRUSPEC.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::[{1:X2}][{2:X2}][{3:X2}]",
                                                    TagNames.PUNCHTHRUSPEC.ToUpper(),
                                                    m_val_deviceid,
                                                    m_val_devscancode,
                                                    m_val_newscancode));
#endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.PUNCHTHRUSPEC]);
                    FileContext.Bw.Write((byte) 3); // length of contained data in bytes.
                    FileContext.Bw.Write((byte)m_val_deviceid);
                    FileContext.Bw.Write((byte)m_val_devscancode);
                    FileContext.Bw.Write((byte)m_val_newscancode);
                
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
                Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.PUNCHTHRUSPEC.ToUpper()));
            }
            else
            {
                emit();
#if TRACE_EMIT            
                Console.WriteLine(String.Format("::/{0}::",TagNames.PUNCHTHRUSPEC.ToUpper()));
#endif
                FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.PUNCHTHRUSPEC] | END_TAG_FLAG));
            }
            return val_parsed;
        }

        public override void setOutputName(TagParsingDirector director)
        {
        }
    }
}
