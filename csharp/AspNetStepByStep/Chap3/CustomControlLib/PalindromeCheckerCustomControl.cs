using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CustomControlLib
{
    [DefaultProperty("Text")]
    [ToolboxData("<{0}:PalindromeCheckerCustomControl runat=server></{0}:PalindromeCheckerCustomControl>")]
    public class PalindromeCheckerCustomControl : WebControl
    {
        public event EventHandler PalindromeFound;
        private List<string> m_Palindromes = new List<string>();

        [Bindable(true)]
        [Category("Appearance")]
        [DefaultValue("")]
        [Localizable(true)]
        public string Text
        {
            get
            {
                String s = (String)ViewState["Text"];
                return ((s == null) ? String.Empty : s);
            }

            set
            {
                ViewState["Text"] = value;

                // get the palindromes.. 
                this.m_Palindromes = (List<string>)this.ViewState["palindromes"];
                if(this.m_Palindromes == null)
                {
                    // or properly initialize if not..
                    this.m_Palindromes = new List<string>();
                }

                if(this.CheckForPalindrome())
                {
                    if(PalindromeFound != null)
                    {
                        PalindromeFound(this, EventArgs.Empty);
                    }
                    m_Palindromes.Add(Text);
                }
                // save off state for roundtrip
                this.ViewState.Add("palindromes", m_Palindromes);
            }
        }

        protected override void RenderContents(HtmlTextWriter output)
        {
//            output.Write(Text);
            if(this.CheckForPalindrome())
            {
                // the stupid way..
#if false
                output.Write("this is a palindrome: <br>");
                output.Write("<FONT size=5 color=Blue>");
                output.Write("<B>");
                output.Write(Text);
                output.Write("</B>");
                output.Write("</FONT>");
#endif
                // the smart way
                output.Write("this is a palindrome: <br>");
                output.RenderBeginTag(HtmlTextWriterTag.Font);
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "blue");
                output.RenderBeginTag(HtmlTextWriterTag.B);
                output.Write(Text);
                output.RenderEndTag(); // bold
                output.RenderEndTag(); // font
            }
            else
            {
                // the smart way
                output.Write("this is a palindrome: <br>");
                output.RenderBeginTag(HtmlTextWriterTag.Font);
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "red");
                output.RenderBeginTag(HtmlTextWriterTag.B);
                output.Write(Text);
                output.RenderEndTag(); // bold
                output.RenderEndTag(); // font
            }
            output.Write("<br>");
            RenderPalindromesInTable(output);
        }
        protected string StripNonAlphaNumerics(string str)
        {
            string strStripped = (string)str.Clone();

            if(str != null)
            {
                char[] rgc = strStripped.ToCharArray();
                int i = 0;
                foreach(char c in rgc)
                {
                    if (char.IsLetterOrDigit(c))
                    {
                        i++;
                    }
                    else
                    {
                        strStripped = strStripped.Remove(i,1);
                    }
                }
            }
            return strStripped;
        }
        protected bool CheckForPalindrome()
        {
            bool retVal = false;
            if(this.Text != null)
            {
                string strControlText = this.Text;
                string strTextToUpper = null;
                strTextToUpper = Text.ToUpper();

                strControlText =
                    this.StripNonAlphaNumerics(strTextToUpper);

                char[] rgcReverse = strControlText.ToCharArray();
                Array.Reverse(rgcReverse);
                string strReverse = new string(rgcReverse);

                if(strControlText == strReverse)
                {
                    retVal = true;
                }
            }
            return retVal;
        }

        protected void RenderPalindromesInTable(HtmlTextWriter output)
        {
            output.AddAttribute(HtmlTextWriterAttribute.Width, "50%");
            output.AddAttribute(HtmlTextWriterAttribute.Border, "1");
            output.RenderBeginTag(HtmlTextWriterTag.Table);

            foreach(string s in this.m_Palindromes)
            {
                output.RenderBeginTag(HtmlTextWriterTag.Tr);
                output.AddAttribute(HtmlTextWriterAttribute.Align, "left");
                output.AddStyleAttribute(HtmlTextWriterStyle.FontSize, "medium");
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "blue");
                output.RenderBeginTag(HtmlTextWriterTag.Td);
                output.Write(s);
                output.RenderEndTag();
                output.RenderEndTag();
            }
            output.RenderEndTag();
        }
    }
}
