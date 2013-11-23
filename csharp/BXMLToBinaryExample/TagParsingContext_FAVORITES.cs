﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingContext_FAVORITES         : TagParsingContext
    {
        private bool m_emitted = false;
        private bool    val_parsed = false;
        private string  m_val = "";
        
        public TagParsingContext_FAVORITES(BinaryFileContext FileContext,int linenumber) : base (FileContext,linenumber)
        {
            string[] taglist = {TagNames.FAVORITE};
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
            return tag.ToLower().Equals(TagNames.FAVORITES);
        }
        public override string tagName()
        {
            return TagNames.FAVORITES;
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
                    Console.WriteLine(String.Format("no value parsed for {0}!",TagNames.FAVORITES.ToUpper()));
                    throw new MissingParameter();
                }
                else
                {
#if TRACE_EMIT            
                    Console.WriteLine(String.Format("::{0}::",TagNames.FAVORITES.ToUpper()));
    #endif
                    FileContext.Bw.Write((byte) FileContext.TagDict[TagNames.FAVORITES]);
                    emitASCIIString(FileContext.Bw,m_val);
                    m_emitted = true;
                }
            }
        }
        public override bool closeElementAction()
        {
            emit();
        
#if TRACE_EMIT            
            Console.WriteLine(String.Format("::/{0}::",TagNames.FAVORITES.ToUpper()));
#endif
            FileContext.Bw.Write((byte) (FileContext.TagDict[TagNames.FAVORITES] | END_TAG_FLAG));
            return true;
        }

        public override void setOutputName(TagParsingDirector director)
        {
            director.SetFavoritesName(m_val);
        }
    }
}